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
            //Py_XDECREF(pModule);
        }
    }
    int EmPy::epMoveMotor()
    {
        if(pModule) 
        {
            PyObject* moveServo = PyObject_GetAttrString(pModule, "moveServo");

            if(moveServo) 
            {
            PyObject *r = PyObject_CallFunction(moveServo, "iii", 0, 0, 0);

            if(r) 
            {
                Py_XDECREF(r);
            }
            Py_XDECREF(moveServo);
            }
            //Py_XDECREF(mydef);
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
/*
    int EmPy::connectBoard()
    {
        if (pModule != NULL)
        {
            pFunc = PyObject_GetAttrString(pModule, "connectBoard");

            if (pFunc && PyCallable_Check(pFunc))
            {
                pValue = PyObject_CallObject(pFunc, pArgs);
                if (PyLong_AsLong(pValue) == 1) 
                {
                    printf("Board Connected\n");
                    Py_DECREF(pValue);
                }
                
                else 
                {
                    Py_DECREF(pFunc);
                    Py_DECREF(pModule);

                    PyErr_Print();
                    fprintf(stderr,"Fail to connect\n");
                    return -1;
                }
            }
            else {
                if (PyErr_Occurred())
                    PyErr_Print();
            }

        
            Py_XDECREF(pFunc);
            //Py_DECREF(pModule);
        }
        else 
        {
            PyErr_Print();
            return -1;
        }

    }


    int EmPy::epMoveValues()
    {
        pArgs = PyTuple_New(3);
        std::cout << "ttttt" << std::endl;
        for(int i = 0; i < 3; i++)
        {
            pValue = PyFloat_FromDouble(angles[i]);
            
            if(!pValue) 
            {
                Py_DECREF(pArgs);
                Py_DECREF(pModule);
                fprintf(stderr, "Cannot convert argument\n");
                return -1;
            }

            PyTuple_SetItem(pArgs, i, pValue);
        }
        if(splitor)
        {
            pValue = PyFloat_FromDouble(0);
        }
        else
        {
            pValue = PyFloat_FromDouble(1);
        }
        PyTuple_SetItem(pArgs, 3, pValue);
        pValue = PyObject_CallObject(pFunc, pArgs);
        Py_DECREF(pArgs);
        if (pValue)
        {
            Py_DECREF(pValue);
        }
        
        else 
        {
            Py_DECREF(pFunc);
            //Py_DECREF(pModule);

            PyErr_Print();
            fprintf(stderr,"Move Call failed\n");
            return 1;
        }
    }

    int EmPy::epMoveMotor()
    {
        if (pModule != NULL) 
        {
            pFunc = PyObject_GetAttrString(pModule, "moveServo");

            if (pFunc && PyCallable_Check(pFunc))
            {
                epMoveValues();
            }
            else {
                if (PyErr_Occurred())
                    PyErr_Print();
            }

        
            Py_XDECREF(pFunc);
            //Py_DECREF(pModule);
        }
        else 
        {
            PyErr_Print();
            return -1;
        }

    }*/

    void EmPy::setAngles(const std::array<double, 3> angles, bool splitor)
    {
        this -> angles = angles;
        this -> splitor = splitor;
    }

    EmPy::~EmPy()
    {
        Py_Finalize();
    }

}