#include "deltaServo.h"
#include <iostream>
namespace delta{
    DeltaMotor::DeltaMotor()
    {
        if (gpioInitialise() < 0)
        {
            fprintf(stderr, "pigpio initialisation failed\n");
        }

        gpioSetMode(MOTOR1, PI_OUTPUT);
        gpioSetMode(MOTOR2, PI_OUTPUT);
        gpioSetMode(MOTOR3, PI_OUTPUT);

       
    }

    std::array<double, 2> DeltaMotor::angle_yz(const double x0, double y0, const double z0, double theta) const
    {
        double y1 = -0.5 * 0.57735 * f;
        y0 -= 0.5 * 0.57735 * e;

        double a = (x0 * x0 + y0 * y0 + z0 * z0 + rf * rf - re * re - y1 * y1) / (2.0 * z0);
        double b = (y1 - y0) / z0;
        double d = -(a + b * y1) * (a + b * y1) + rf * (b * b * rf + rf);

        double yj = (y1 - a * b - sqrt(d)) / (b * b + 1);
        double zj = a + b * yj;
        theta = atan(-zj / (y1 - yj)) * 180.0 / pi + (yj > y1 ? 180 : 0.0);
        std::array<double, 2> res = {0, theta};
        return res;
    }


    std::array<double, 3> DeltaMotor::inverse(const double x0,const double y0, const double z0) const
    {
        double theta1 = 0;
        double theta2 = 0;
        double theta3 = 0;
        std::array<double, 2> state = angle_yz(x0, y0, z0);

        if (state[0] == 0)
        {
            theta1 = state[1];
            state = angle_yz(x0*cos120 + y0 * sin120, y0 * cos120 - x0 * sin120, z0, theta2);
            theta2 = state[1];
            state = angle_yz(x0*cos120 - y0 * sin120, y0 * cos120 + x0*sin120, z0, theta3);
            theta3 = state[1];
        }
        std::array<double, 3> res = {theta1, theta2, theta3};
        return res;
    }


    float DeltaMotor::map(const float x, const float in_min, const float in_max, const float out_min, const float out_max) const
    {
        return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    }
    
    void DeltaMotor::set2Zero()
    {
        setMotorXYZ(0, 0, Z_UP);
        gpioServo(MOTOR1, map(0));
        gpioServo(MOTOR2, map(0));
        gpioServo(MOTOR3, map(0));
        time_sleep(2);
    }
    
    void DeltaMotor::moveMotor()
    {
        
        std::array<double,3> pre;
        std::array<double,3> angles = inverse(coordinates.x,coordinates.y,coordinates.z);
        std::cout << "new" << std::endl;
        for (auto i : angles)
        {
            std::cout << i << std::endl;

        }
        pre[0] = map(gpioGetServoPulsewidth(MOTOR1), 600, 2400, -90, 90);
        pre[1] = map(gpioGetServoPulsewidth(MOTOR2), 600, 2400, -90, 90);
        pre[2] = map(gpioGetServoPulsewidth(MOTOR3), 600, 2400, -90, 90);
        std::cout << gpioGetServoPulsewidth(MOTOR1) << std::endl;
        std::array<double, 3> diff = {angles[0] - pre[0], angles[1] - pre[1], angles[2] - pre[2]};
        std::cout << "pre" << std::endl;

        for (auto i : pre)
        {
            std::cout << i << std::endl;
        }
        for (int i = 1; i < 101; i++)
        {
            gpioServo(MOTOR1, map(pre[0] + diff[0] * i / 100));
            gpioServo(MOTOR2, map(pre[1] + diff[1] * i / 100));
            gpioServo(MOTOR3, map(pre[2] + diff[2] * i / 100));
            time_sleep(speed);
        }
        std::cout<< "speed = " << speed << std::endl;
        std::cout << std::endl;
    }
    void DeltaMotor::setMotorXYZ(const float x, const float y, const float z)
    {
        if(coordinates.z != z)
        {
            speed = 0.005;
        }
        else
        {
            speed = 0.001;
        }
        coordinates.x = x;
        coordinates.y = y;
        coordinates.z = z;
        std::cout << "x = " << x << "y = " << y << "z = " << z << std::endl;
    }
    
    DeltaMotor::~DeltaMotor()
    {

    }
}
