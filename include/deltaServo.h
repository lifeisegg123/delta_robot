#ifndef Delta_motor
#define Delta_motor
#include <math.h>
#include <array>
#include <empy.h>

namespace delta
{
    #define MOTOR1 17
    #define MOTOR2 22
    #define MOTOR3 25

    struct Points
    {
        float x, y, z;
    };
    enum zStatus{
        Z_DOWN = -300,
        Z_UP = -255,
    };
    class DeltaMotor
    {
    public:
        DeltaMotor();
        std::array<double, 2> angle_yz(const double x0, double y0, const double z0, double theta = 0) const;
        std::array<double, 3> inverse(const double x0, const double y0, const double z0) const;
        void moveMotor();
        void setMotorXYZ(const float x, const float y, const float z);
        void set2Zero();
        ~DeltaMotor();
    private:
        

        const double pi = 3.141592653;
        const double sin120 = sqrt(3) / 2.0;
        const double sin30  = 0.5;
        const double tan30  = 1.0 / sqrt(3);
        const double hodo =  pi / 180;
        const double cos120 = -0.5;
        const double tan60  = sqrt(3);

        const int e  =  24;
        const int f  =  75;
        const float re = 314.6;
        const int rf = 100;

        EmPy py;
        int splitor;
        Points coordinates;
    };
}
#endif