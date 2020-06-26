#include "deltaServo.h"
#include <iostream>
namespace delta{
    DeltaMotor::DeltaMotor()
    {
       py.getPy();
       py.connectBoard();
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
    void DeltaMotor::set2Zero()
    {
        py.epset2Zero();
    }
    
    void DeltaMotor::moveMotor()
    {
        
        std::array<double,3> angles = inverse(coordinates.x,coordinates.y,coordinates.z);
        //std::cout << "new" << std::endl;
        for (auto i : angles)
        {
            std::cout << i << std::endl;
        }

        py.setAngles(angles, splitor);
        py.epMoveMotor();
    }
    void DeltaMotor::setMotorXYZ(const float x, const float y, const float z)
    {
        if(coordinates.z != z)
        {
            splitor = 1;
        }
        else
        {
            splitor = 0;
        }
        
        coordinates.x = x;
        coordinates.y = y;
        coordinates.z = z;
        std::cout << "x = " << x << "y = " << y << "z = " << z << std::endl;
    }
    
    DeltaMotor::~DeltaMotor()
    {}
}
