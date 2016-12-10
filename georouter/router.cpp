#include <Python.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
// Router.cpp is interface to routing/navigation python function.
// Parameters: startpoint ID of osm xml, destination ID of xml.
// Return : char array or vector of route
using namespace std;
typedef char Point[8];
vector<char> listTupleToVector_Int(PyObject* incoming); 
// TODO change 'main' to function name , parameters should be 
// startpoint ID of osm xml file and destination ID of osm xml file.
// save strItem to new data type ,it can be vector or just a array depends 
// on caller function.
int main(int argc,char *argv[])
{
    PyObject *pName, *pModule, *pDict, *pFunc, *pInstance, *pPath, *pListItem;
    char *strItem;
    std:: vector<char> path;
    // init variables for extract elements from list.
    int element_num,k;
    int i;
    Point *p;

    // Initialize the Python interpreter
    Py_Initialize();
    if(!Py_IsInitialized())
    {
        printf("init error\n");
    }
    PyRun_SimpleString("print '----import re,string,sys----'");
    PyRun_SimpleString("print '----import xml.sax as sax----'");
    PyRun_SimpleString("print '----from math import radians,cos,sin,asin,sqrt----'");
    PyRun_SimpleString("import re,string,sys");
    PyRun_SimpleString("import xml.sax as sax ");
    PyRun_SimpleString("from math import radians,cos,sin,asin,sqrt");
    
    // Build the name object
    pName = PyString_FromString(argv[1]);
    //p1 = PyString_FromString(argv[2]);
    //p2 = PyString_FromString(argv[3]);

    // Load the module object
    pModule = PyImport_Import(pName);
    if(!pModule)
    {
        PyErr_Print();
        printf("can't find routing.py\n");
        return 0;
    }

    // pDict is a borrowed reference
    pDict = PyModule_GetDict(pModule);
    if(!pDict)
    {
        return 0;
    }

    // Build the name of a callable class
    pFunc = PyDict_GetItemString(pDict, "cpp_call");
    
    pPath = PyObject_CallFunction(pFunc,NULL);
    //PyArg_ParseTuple(pPath,"-1",&element_num,*p1,*p2);
    element_num = PyObject_Length(pPath);
    k = PyObject_Size(pPath);
    printf("C++ ................pPath size or length:%d, %d\n",element_num,k);
    printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n"); 
    for (int i = 0; i < element_num; i++)
    {
        pListItem = PyList_GetItem(pPath, i);
        strItem = PyString_AsString(pListItem);
        printf("%s\n",strItem );
    }
        printf("IN CPP we got : %d elements from PYTHON\n",element_num);

    Py_Finalize();
}




