#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <string.h>
#include "rapidxml_utils.hpp"
#include <math.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace rapidxml;
using namespace cv;
using namespace std;

/********************************/
/*								*/
/*		GLOBAL VARIABLES		*/
/*								*/
/********************************/

#define LOCAL_PI 3.1415926535897932385
#define LARGEUR_FENETRE 600
#define HAUTEUR_FENETRE 600
Mat image = Mat::zeros(Size(LARGEUR_FENETRE, HAUTEUR_FENETRE), CV_8UC3);
double Min_lon = 50;
double Max_lon = 0;
double Min_lat = 50;
double Max_lat = 0;
double Alpha = 0;
int CurrentRoad = 0;

/********************************/
/*								*/
/*			FUNCTIONS			*/
/*								*/
/********************************/

double ToRadians(double degrees)
{
	double radians = degrees * LOCAL_PI / 180;
	return radians;
}

// Distance between two points (longitude, latitude)
double DirectDistance(double lat1, double lng1, double lat2, double lng2)
{
	double earthRadius = 6371000; //meters
	double dLat = ToRadians(lat2-lat1);
	double dLng = ToRadians(lng2-lng1);
	double a = sin(dLat/2) * sin(dLat/2) +
	cos(ToRadians(lat1)) * cos(ToRadians(lat2)) *
	sin(dLng/2) * sin(dLng/2);
	double c = 2 * atan2(sqrt(a), sqrt(1-a));
	float dist = (float) (earthRadius * c);
	return dist;
}

int GetDisplayX(double lon){
	double temp = ((lon - Min_lon)*Alpha) + 10;
	return temp;
}

int GetDisplayY(double lat){
	double temp = ((Max_lat - lat)*Alpha) + 10;
	return temp;
}

/********************************/
/*								*/
/*			CLASSES				*/
/*								*/
/********************************/

class Node{

private:
	string Name;
	int user = 0;
	int id;
	float latitude;
	float longitude;

public:
	void ToString(){
		if (user){
			cout << "Node called : " << Name << "with id : " << id << " longitude : " << longitude << " and latitude : " << latitude << "\n";
		} else {
			cout << "My node with id : " << id << " longitude : " << longitude << " and latitude : " << latitude << "\n";
		}
	}
	Node(){
		id = 0;
	}

	Node(int Node_Id, float lon, float lat){
		id = Node_Id;
		longitude = lon;
		latitude = lat;
	}

	void SetName(string NAME){
		Name = NAME;
		user = 1;
	}

	void Display(){
		if (user){
			circle(image, Point(GetDisplayX(longitude), GetDisplayY(latitude)),  5, Scalar(0, 20, 170, 255), 1, 8, 0);
		}
	}

	float GetLatitude(){
		return latitude;
	}
	float GetLongitude(){
		return longitude;
	}
	int GetId(){
		return id;
	}

};

class Road{

public:
	int id;
	Node begin;
	Node end;
	float a;
	float b;
	int width;

	void ToString(){
		cout.precision(12);
		cout << "My road with id : " << id << " has an equation : " << a << " x + " << b << "\n";
	}

	Road(int Road_Id, Node b, Node e){
		id = Road_Id;
		begin = b;
		end = e;
		Compute();
	}

	double DistanceToCenter(double lon, double lat){
		double Proj_Lat = (a*lon + a*a*lat + b)/(1 + a*a);
		double Proj_Lon = (lon + a*lat - a*b)/(1 + a*a);
		return DirectDistance(lat, lon, Proj_Lat, Proj_Lon);
	}

	void Display(){
		if (Alpha){		// Alpha needs to be defined to get (x,y) coordinates
			int y1 = GetDisplayY(begin.GetLatitude());
			int x1 = GetDisplayX(begin.GetLongitude());
			int y2 = GetDisplayY(end.GetLatitude());
			int x2 = GetDisplayX(end.GetLongitude());
			if (id == CurrentRoad){
				line(image, Point(x1,y1), Point(x2, y2), Scalar( 255, 0, 0, 255),  1, 0 );
			} else {
				line(image, Point(x1,y1), Point(x2, y2), Scalar( 110, 220, 100),  1, 0 );
			}
		}
	}

private:
	void Compute(){
		a = (end.GetLatitude() - begin.GetLatitude())/(end.GetLongitude() - begin.GetLongitude());
		b = begin.GetLatitude() - begin.GetLongitude() * a;
	}
};

class Building{
public:
	int id;
	string Name;
	vector<Node> Building_Corner_Vec;

	Building(int ID, string NAME, vector<Node> VEC){
		id = ID;
		Name = NAME;
		Building_Corner_Vec = VEC;
	}

	void AddCorner(Node node){
		Building_Corner_Vec.push_back(node);
	}

	//	Enable the building to have more than 4 walls.
	void Display(){
		if (Alpha){
			int VecSize = Building_Corner_Vec.size();
			int NumberOfCoordinates = VecSize*2;
			int XAndYs [NumberOfCoordinates];						// EVEN numbers are the Xs and ODD numbers are Ys
			XAndYs[0] = GetDisplayX(Building_Corner_Vec[0].GetLongitude());
			XAndYs[1] = GetDisplayY(Building_Corner_Vec[0].GetLatitude());
			int index;
			for(index = 1; index < VecSize ; index++){
				XAndYs[index*2] = GetDisplayX(Building_Corner_Vec[index].GetLongitude());
				XAndYs[index*2+1] = GetDisplayY(Building_Corner_Vec[index].GetLatitude());
				line(image, Point(XAndYs[(index-1)*2],XAndYs[(index-1)*2+1]), Point(XAndYs[index*2], XAndYs[index*2+1]), Scalar( 0, 220, 100, 255),  1, 0 );
			}
			line(image, Point(XAndYs[(index-1)*2],XAndYs[(index-1)*2+1]), Point(XAndYs[0], XAndYs[1]), Scalar( 0, 220, 100, 255),  1, 0 );
		}
	}
};

/********************************/
/*								*/
/*			FUNCTIONS			*/
/*								*/
/********************************/

// Returns the Node with the specified ID
Node GetNodeById(int id, vector<Node> v){
	Node null;
	for(vector<Node>::iterator it = v.begin(); it != v.end(); ++it) {
		if(it->GetId() == id){
			return *it;
		}
	}
	return null;
}

//	Display every roads and the one we are on with a different color
void DisplayAllRoads(vector<Road> v){
	for(vector<Road>::iterator it = v.begin(); it != v.end(); ++it) {
		it->Display();
	}
}

//	Display every buildings
void DisplayAllBuildings(vector<Building> v){
	for(vector<Building>::iterator it = v.begin(); it != v.end(); ++it) {
		it->Display();
	}
}

void DisplayAllUserNodes(vector<Node> v){
	for(vector<Node>::iterator it = v.begin(); it != v.end(); ++it) {
		it->Display();
	}
}

void WhichRoad(double lon, double lat, vector<Road> v){
	int Road_Nb = 0;
	double Distance_Min = 5000;
	for(vector<Road>::iterator it = v.begin(); it != v.end(); ++it) {
		double Temp_Distance = it->DistanceToCenter(lon, lat);
		cout << "Distance to road " << it->id << " is " << Temp_Distance << '\n';
		if(Temp_Distance < Distance_Min){
			Road_Nb = it->id;
			Distance_Min = Temp_Distance;
		}
	}
	CurrentRoad = Road_Nb;
}

// Set the alpha factor that convert longitude/latitude in pixels
void SetAlpha(){
	double Alpha_lon = (LARGEUR_FENETRE - 20)/(Max_lon - Min_lon);
	double Alpha_lat = (HAUTEUR_FENETRE - 20)/(Max_lat - Min_lat);
	if (Alpha_lon < Alpha_lat){
		Alpha = Alpha_lon;
	} else {
		Alpha = Alpha_lat;
	}
	cout << "Alpha = " << Alpha << '\n';
}

/********************************/
/*								*/
/*				MAIN			*/
/*								*/
/********************************/

int main(){
	try {
		// Draw a line
		//line( image, Point( 15, 20 ), Point( 70, 50), Scalar( 110, 220, 0 ),  2, 8 );

		//opencvtest.o :
		//	$(CC) $(CPPFLAGS) -c opencvtest.cpp

		file<> xmlFile("heavy.osm");
		xml_document<> doc;
		doc.parse<0>(xmlFile.data());
		xml_node<> * root = doc.first_node();

		vector<Node> Node_Vec;
		vector<Road> Road_Vec;
		vector<Building> Building_Vec;
		vector<Node> User_Node;
		Min_lon = 50;
		Max_lon = 0;
		Min_lat = 50;
		Max_lat = 0;

		int id = 0;
		double lon = 0;
		double lat = 0;
		cout.precision(12);
		int id_way = 0;
		xml_node<> * curr_node = root->first_node();

		while(curr_node){

			//Node
			if(strcmp(curr_node->name(), "node")==0){
				int user = 0;
				string name;
				id = 0;
				lon = 0;
				lat = 0;
				xml_attribute<> * attr = curr_node->first_attribute();
				while(attr){
					if (strcmp(attr->name(), "id") == 0){
						id = atoi(attr->value());
					} else if (strcmp(attr->name(),  "lat") ==0){
						lat = atof(attr->value());
					} else if (strcmp(attr->name(), "lon") ==0){
						lon = atof(attr->value());
					}
					attr = attr->next_attribute();
				}//while
				xml_node<> * tag = curr_node->first_node();
				while(tag){
					if (strcmp(tag->name(), "tag") == 0){
						if (strcmp(tag->first_attribute()->name(), "k") == 0){
							if (strcmp(tag->first_attribute()->value(), "user") == 0){
								user = 1;
								name = string(tag->first_attribute()->next_attribute()->value());
							}
						}
					}
					tag = tag->next_sibling();
				}

				//Create node if we have all the needed values
				if (id != 0 && lon != 0 && lat != 0){
					Node node(id, lon, lat);
					if (user){
						node.SetName(name);
						User_Node.push_back(node);
						node.ToString();
					} else {
						Node_Vec.push_back(node);
					}
					if (lon < Min_lon){
						Min_lon = lon;
					} else if (lon > Max_lon){
						Max_lon = lon;
					}
					if (lat < Min_lat){
						Min_lat = lat;
					} else if (lat > Max_lat){
						Max_lat = lat;
					}
				}
			} // Node

			//	Way
			if(strcmp(curr_node->name(), "way")==0){
				id_way = 0;
				int building = 0;
				string Name = "" ;
				vector<Node> Vec_Way_Node;

				if (strcmp(curr_node->first_attribute()->name(), "id") == 0){
					id_way = atoi(curr_node->first_attribute()->value());
					xml_node<> * curr_nd = curr_node->first_node();
					while(curr_nd){
						if (strcmp(curr_nd->name(), "nd") == 0){
							if(strcmp(curr_nd->first_attribute()->name(), "ref") == 0){
								double temp_id = (double)atof(curr_nd->first_attribute()->value());
								Node Retrieved_Node = GetNodeById(temp_id, Node_Vec);
								if (Retrieved_Node.GetId() != 0){
									Vec_Way_Node.push_back(Retrieved_Node);
								} else {
									//cout << "Pb GetNodeById()" << '\n';
								}
							} else {
								//cout << "Pb ref" << '\n';
							}
						} else if (strcmp(curr_nd->name(), "tag") == 0){
							if (strcmp(curr_nd->first_attribute()->name(), "k") == 0){
								if (strcmp(curr_nd->first_attribute()->value(), "building") == 0){
									building = 1;
								} else if (strcmp(curr_nd->first_attribute()->name(), "name") == 0){
									xml_attribute<> * attribute = curr_nd->first_attribute();
									attribute = attribute->next_attribute();
									Name = string(attribute->value());
								}
							}
						}
						curr_nd = curr_nd->next_sibling();
					}

					// Create the appropriate environment element if we have all the needed values
					if (Vec_Way_Node.size() >= 2){
						// building
						if (building == 1){
							Building myBuilding(id_way, Name, Vec_Way_Node);
							Building_Vec.push_back(myBuilding);
						}
						// Road
						else if (building == 0){
							Road myRoad(id_way, Vec_Way_Node[0], Vec_Way_Node[Vec_Way_Node.size()-1]);
							Road_Vec.push_back(myRoad);
						}
					} else {
						//cout << "Only one point for this element" << '\n';
					}
				} else {
					//cout << "Pb id" << '\n';
				}
			}
			//	Next sibling
			curr_node = curr_node->next_sibling();

		}

		std::cout << "Number of Nodes : " << Node_Vec.size() << '\n';
		std::cout << "Number of Roads : " << Road_Vec.size() << '\n';
		std::cout << "Number of User Nodes : " << User_Node.size() << '\n';

		cout << "Which Road ? Point is 1.467821,43.570077 : \n";
		WhichRoad(1.467821,43.570077, Road_Vec);
		std::cout << "Current Road = " << CurrentRoad << '\n';
		SetAlpha();

		DisplayAllRoads(Road_Vec);
		DisplayAllBuildings(Building_Vec);
		DisplayAllUserNodes(User_Node);
		// Position
		circle(image, Point(GetDisplayX(1.467821), GetDisplayY(43.570077)),  5, Scalar(0, 0, 255, 255), -1, 8, 0);
		imshow("Image",image);
		waitKey(0);

	}
	catch (const runtime_error& error)
	{
		cout << "Problem when opening the map file : " << '\n';
	}
}
