#include <iostream>
#include <array>
#include <numeric>

using namespace std;

double get_lcm(double a, double b)
{
    int z;
    int x = a;
    int y = b;

    while(true)
    {
        z = x % y;
        if(0 == z)
        {
            break;
        }
        x = y;
        y = z;
    }
    return a * b / y;
}
/*
double get_LCM(std::array<double,3> diff)
{
    return get_lcm(diff[0], get_lcm(diff[1], diff(2)));
}
*/
int main()
{
    /*std::array<double,3> pre;
    std::array<double, 3> ne;
    std::array<double, 3> result = {pre[0] - ne[0], pre[1] - ne[1], pre[2] - ne[2]};

    double lcm = get_LCM(result);

    result[0] /= lcm;
    result[1] /= lcm;
    result[2] /= lcm;

    for (int i = 1; i < lcm; i++)
    {
        gpioServo(MOTOR1, map(pre[0] * i));
        gpioServo(MOTOR2, map(pre[1] * i));
        gpioServo(MOTOR3, map(pre[2] * i));
    }*/
    cout << get_lcm(3,5);

}