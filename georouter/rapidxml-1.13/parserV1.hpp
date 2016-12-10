#ifndef PARSERV1_H
#define PARSERV1_H

#include <string>
#include <vector>


double ToRadians(double degrees);
double DirectDistance(double lat1, double lng1, double lat2, double lng2);
int GetDisplayX(double lon);
int GetDisplayY(double lat);
int GetCloseDisplayX(double lon);
int GetCloseDisplayY(double lat);

class Node{

private:
    std::string Name;
    int user = 0;
    double id;
    float latitude;
    float longitude;

public:
    void ToString();
    Node();

    Node(double Node_Id, float lon, float lat);

    void SetName(std::string NAME);

    void Display(int close);

    float GetLatitude();
    float GetLongitude();
    double GetId();
};

class Road{

private:
    double id;
    Node begin;
    Node end;
    float a;
    float b;
    int width;
    std::vector<Node> Road_Nodes;

    void Compute_Coefs();

public:
    void ToString();

    Road(double Road_Id, std::vector<Node> VEC);

    Road(double Road_Id, Node b, Node e);

    void SetEndNode(Node e);

    double DistanceToCenter(double lon, double lat);

    void Display(int close);

    float GetA();
    float GetB();
    double GetId();
    Node GetBegin();
    Node GetEnd();
};

class Building{

private:
    double id;
    std::string Name;
    std::vector<Node> Building_Corner_Vec;

public:
    Building(int ID, std::string NAME, std::vector<Node> VEC);

    //	Enable the building to have more than 4 walls.
    void Display(int close);

    std::string GetName();

    double GetId();
};

/********************************/
/*								*/
/*			FUNCTIONS			*/
/*								*/
/********************************/

//	Display every roads and the one we are on with a different color
void DisplayAllRoads(std::vector<Road *> v, int close);

//	Display every buildings
void DisplayAllBuildings(std::vector<Building *> v, int close);

void DisplayAllUserNodes(std::vector<Node *> v, int close);

void WhichRoad(double lon, double lat, std::vector<Road *> v);

// Set the alpha factor that convert longitude/latitude in pixels
void SetAlpha();

void SetBeta();

float ComputeCoefA(Node begin, Node end);

/********************************/
/*								*/
/*		GLOBAL VARIABLES		*/
/*								*/
/********************************/



void BuildAllRoads(int id_road, std::vector<Node> VEC);

// Returns the Node with the specified ID
Node * GetNodeById(long double id);

int init();

double WhichRoadWithLatLon();

int CreateAll(int close);

int DisplayImage(int close);

int SetPosition(double lon, double lat);

int DisplayMyPosition();

int DisplayCloseMyPosition();

int DisplayCloseToLocation();

#endif
