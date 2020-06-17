#ifndef empy
#define empy


#define PY_SSIZE_T_CLEAN
#pragma push_macro("slots")
#undef slots
#include "Python.h"
#pragma pop_macro("slots")
#include <array>

namespace delta
{
    class EmPy
    {
        public:
            EmPy();
            void getPy();
            int connectBoard();
            int epMoveMotor();
            int epMoveValues();
            void setAngles(const std::array<double, 3> angles, bool splitor);
            ~EmPy();
            

        private:
            std::array<double, 3> angles = {0, 0, 0};
            bool splitor;

            PyObject *pName, *pModule, *pFunc;
            PyObject *pArgs, *pValue;
    };
}
#endif