#ifndef ROUTER_H
#define ROUTER_H

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
