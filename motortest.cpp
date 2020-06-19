#include "deltaServo.h"
#include <unistd.h>

int main()
{
    delta::DeltaMotor dm;
    for (;;)
    {
        dm.setMotorXYZ(30,30, -315);
        dm.moveMotor();
        usleep(1000000);

        dm.setMotorXYZ(30,30, -345);
        dm.moveMotor();
        
        dm.setMotorXYZ(30,30, -315);
        dm.moveMotor();

        dm.setMotorXYZ(-30,-30, -315);
        dm.moveMotor();
        usleep(1000000);

        dm.setMotorXYZ(-30,-30, -345);
        dm.moveMotor();
        
        dm.setMotorXYZ(-30,-30, -315);
        dm.moveMotor();
    }
}