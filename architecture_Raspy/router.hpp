#ifndef ROUTER_H
#define ROUTER_H

#ifdef __APPLE__
   #include <Python/Python.h>
#else
    #include <Python.h>
#endif


#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <stdlib.h>


#define PY_router "routing"



/********************************/
/*								*/
/*		        ROUTER		    */
/*								*/
/********************************/

class Router{

public:
    std::vector<char*> getpath(char pointA[],char pointB[]);
};



#endif
