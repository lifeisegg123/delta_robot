#ifndef empy
#define empy

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <iostream>
#include <array>

namespace delta
{
    class EmPy
    {
        public:
            EmPy();
            void getPy();
            int epMoveMotor();
            int epReference();
            void setAngles(const std::array<double, 3> angles);
            ~EmPy();
            

        private:
            std::array<double, 3> angles;
            PyObject *pName, *pModule, *pFunc;
            PyObject *pArgs, *pValue;
    };
}
#endif