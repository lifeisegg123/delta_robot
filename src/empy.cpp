#include "empy.h"
namespace delta
{
    EmPy::EmPy()
    {
        Py_Initialize();
        PyRun_SimpleString("import sys");
        PyRun_SimpleString("sys.path.append(\"../py\")");
    }

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
            Py_DECREF(pModule);
        }
        else 
        {
            PyErr_Print();
            return -1;
        }

    }

    void EmPy::getPy()
    {
        pName = PyUnicode_DecodeFSDefault("servo");
        pModule = PyImport_Import(pName);
        Py_DECREF(pName);
    }
    int EmPy::epMoveValues()
    {
        pArgs = PyTuple_New(3);
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

        pValue = PyObject_CallObject(pFunc, pArgs);
        Py_DECREF(pArgs);
        if (pValue) 
        {
            printf("motor moved\n");
            Py_DECREF(pValue);
        }
        
        else 
        {
            Py_DECREF(pFunc);
            Py_DECREF(pModule);

            PyErr_Print();
            fprintf(stderr,"Call failed\n");
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
            Py_DECREF(pModule);
        }
        else 
        {
            PyErr_Print();
            return -1;
        }

    }

    void EmPy::setAngles(const std::array<double, 3> angles)
    {
        this -> angles = angles;

    }

    EmPy::~EmPy()
    {
        Py_Finalize();
    }

}