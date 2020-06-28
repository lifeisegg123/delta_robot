#include "empy.h"
#include <iostream>
namespace delta
{
    int EmPy::connectBoard()
    {
        if(pModule) 
        {
            PyObject* connectBoard = PyObject_GetAttrString(pModule, "connectBoard");

            if(connectBoard) 
            {
                PyObject *r = PyObject_CallFunction(connectBoard, NULL);

                if (r == Py_None)
                {
                    printf("None is returned.\n");
                    Py_XDECREF(r);
                }

                Py_XDECREF(connectBoard);
            }
        }
    }
    int EmPy::epMoveMotor()
    {
        if(pModule) 
        {
            PyObject* moveServo = PyObject_GetAttrString(pModule, "moveServo");

            if(moveServo)
            {
                PyObject *r = PyObject_CallFunction(moveServo, "dddd", angles[0], angles[1], angles[2], splitor);

                if(r) 
                {
                    Py_XDECREF(r);
                }
                Py_XDECREF(moveServo);
            }
        }
    }
    int EmPy::epset2Zero()
    {
        if(pModule) 
        {
            PyObject* moveServo = PyObject_GetAttrString(pModule, "set0");

            if(moveServo)
            {
                PyObject *r = PyObject_CallFunction(moveServo, NULL);
                if(r) 
                {
                    Py_XDECREF(r);
                }
                Py_XDECREF(moveServo);
            }
        }
    }
    EmPy::EmPy()
    {
        Py_Initialize();
        PyRun_SimpleString("import sys");
        PyRun_SimpleString("sys.path.append(\"../py\")");
    }

    void EmPy::getPy()
    {
        pName = PyUnicode_DecodeFSDefault("servo");
        pModule = PyImport_Import(pName);
        Py_DECREF(pName);
    }

    void EmPy::setAngles(const std::array<double, 3> angles, int splitor)
    {
        this -> angles = angles;
        this -> splitor = splitor;
    }

    EmPy::~EmPy()
    {
        Py_XDECREF(pModule);
        Py_Finalize();
    }

}
