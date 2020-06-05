#include <iostream>
#include <array>
#include <math.h>

const double pi = 3.141592653;
const double sin120 = sqrt(3) / 2.0;
const double sin30  = 0.5;
const double tan30  = 1.0 / sqrt(3);
const double hodo =  pi / 180;
const double cos120 = -0.5;
const double tan60  = sqrt(3);

const int e  =  25;
const int f  =  75;
const int re = 300;
const int rf = 100;

std::array<double, 2>angle_yz(const double x0, double y0, const double z0, double theta = 0)
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


    std::array<double, 3> inverse(const double x0,const double y0, const double z0)
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

int main()
{
    


std::array<double,3> angles = inverse(-114, -92, -140);

for(auto i : angles)
{
    std::cout <<  i << std::endl;
}
}