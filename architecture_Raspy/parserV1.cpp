//
//  parserV1.cpp
//

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


// RapidXML is the library we used to parse the map. (xml document)
#include "rapidxml_utils.hpp"

#include "router.hpp"
#include "parserV1.hpp"

using namespace rapidxml;
using namespace std;

double Map::Min_lon = 50;
double Map::Max_lon = 0;
double Map::Min_lat = 50;
double Map::Max_lat = 0;
double Map::Alpha = 0;
double Map::Beta = 0;
double Map::Delta_Lon = 0;
double Map::Delta_Lat = 0;
int Map::CurrentRoad = 0;
cv::Mat Map::image;
cv::Mat Map::imageClose;

/**
    Decompose a Road in different smaller roads
	for display purposes.

    @param id of the initial road
	@param vector of nodes that represent 1 road
    @return
*/
void Map::BuildAllRoads(int id_road, vector<Node> VEC){
	//Create the first road
	int indexFirst = 0;
	int index = 1;
	Node begin = VEC[0];
	Node end = VEC[1];
	Road * myRoad = new Road(id_road, begin, end);
	//Check if we have more than 2 nodes
	while (index<VEC.size()-1){
		//And loop through them
		index++;
		Node TempEndNode = VEC[index];
		if (abs(ComputeCoefA(begin, TempEndNode) - myRoad->GetA()) < 0.0001){
			// Points on the same straight line
			myRoad->SetEndNode(TempEndNode);
			end = TempEndNode;
		} else {
			// Add the current road to the list and start a new one;
			vector<Node>::const_iterator first = VEC.begin() + indexFirst;
			vector<Node>::const_iterator last = VEC.begin() + index;
			vector<Node> VecRoadNodes_Local(first, last);
			indexFirst = index-1;
			myRoad->SetVecRoadNodes(VecRoadNodes_Local);
			Road_Vec.push_back(myRoad);
			begin = end;
			end = TempEndNode;
			myRoad = new Road(BaseIndexToCount++, begin, end);
		}
	}
	vector<Node>::const_iterator first = VEC.begin() + indexFirst;
	vector<Node>::const_iterator last = VEC.begin() + index;
	vector<Node> VecRoadNodes_Local(first, last);
	indexFirst = index -1;
	myRoad->SetVecRoadNodes(VecRoadNodes_Local);
	Road_Vec.push_back(myRoad);
}

// Returns the coefficient of a straight line out of 2 points.
float Map::ComputeCoefA(Node begin, Node end){
	return (end.GetLatitude() - begin.GetLatitude())/(end.GetLongitude() - begin.GetLongitude());
}

//	Display everything updated on the OpenCV Mat images.
int Map::CreateAll(int close){
	if (close){
		DisplayAllRoads(Road_Vec, close, imageClose);
		DisplayAllBuildings(Building_Vec, close, imageClose);
		DisplayAllUserNodes(User_Node, close, imageClose);
	} else {
		DisplayAllRoads(Road_Vec, close, image);
		DisplayAllBuildings(Building_Vec, close, image);
		DisplayAllUserNodes(User_Node, close, image);
	}
	return 1;
}

/*
	Model of our car.
	Computes the corrective angle to follow in order to keep
	a correct heading

	@param Distance driven between the Current Position and the Previous position
*/
float Map::GetCorrectiveHeading(float DrivenDistance){
	// Need to have called SetPosition() right before and 5 meters before
	// Our CurrentPosition_Lon and CurrentPosition_Lat are the GPS position.
	// Our PreviousPosition_Lon and PreviousPosition_Lat are the origins.
	// distance in [meters]
	float Corrective_Cap = 0.0;

	if (PathSet){
		double distance = DirectDistance(CurrentPosition_Lat, CurrentPosition_Lon, PreviousPosition_Lat, PreviousPosition_Lon);
		std::cout << "Distance brute avant correction de position: " << distance << '\n';

		// We assume an uncertainty of 2.5 meters on the GPS measure.
		float Cap_Actuel = 0;
		float Cap_Destination = 0;

		Cap_Actuel = ComputeCoefA(Node(1, CurrentPosition_Lon, CurrentPosition_Lat), Node(2, PreviousPosition_Lon, PreviousPosition_Lat));

		//Correction de position
		//float rapport = DISTANCE_BETWEEN_ACQUISITIONS / distance;
		float rapport = DrivenDistance / distance;

		CurrentPosition_Lon = PreviousPosition_Lon + rapport * (CurrentPosition_Lon - PreviousPosition_Lon);
		CurrentPosition_Lat = PreviousPosition_Lat + rapport * (CurrentPosition_Lat - PreviousPosition_Lat);
		double Local_DestinationPosition_Lat;
		double Local_DestinationPosition_Lon;
		std::cout << "Distance normalement égale à 5 après Correction de position: " << DirectDistance(CurrentPosition_Lon, CurrentPosition_Lat, PreviousPosition_Lon, PreviousPosition_Lat) << '\n';
		if (PathToDestination.size() != 0 || ManualDestinationSet == 1){
			if (ManualDestinationSet == 0){
				if (CurrentIntermediateDestinationNode != -1){
					Local_DestinationPosition_Lon = PathToDestination[CurrentIntermediateDestinationNode]->GetLongitude();
					Local_DestinationPosition_Lat = PathToDestination[CurrentIntermediateDestinationNode]->GetLatitude();
				} else {
					Local_DestinationPosition_Lon = DestinationPosition_Lon;
					Local_DestinationPosition_Lat = DestinationPosition_Lat;
				}
			} else if (ManualDestinationSet = 1){
				std::cout << "Manual Destination Set." << '\n';
				Local_DestinationPosition_Lon = DestinationPosition_Lon;
				Local_DestinationPosition_Lat = DestinationPosition_Lat;
			}

			double RemainingDistance = DirectDistance(CurrentPosition_Lon, CurrentPosition_Lat, Local_DestinationPosition_Lon, Local_DestinationPosition_Lat);
			// We enter here if we are closer than 3 meters from the intermediate Node
			while(RemainingDistance < 3){
				//	Test if we were heading to the final destination
				if (CurrentIntermediateDestinationNode == -1){
					std::cout << "\n\n\t ARRIVED !\n\n";
					PathToDestination.clear();
				}
				// Test if we were heading to the last intermediate Node before final destination
				if (CurrentIntermediateDestinationNode == PathToDestination.size() - 1){
					// If so, we are now heading to the final destination ( user defined point)
					Local_DestinationPosition_Lon = DestinationPosition_Lon;
					Local_DestinationPosition_Lat = DestinationPosition_Lat;
					CurrentIntermediateDestinationNode = -1;
					//	We were heading to an intermediate node
				} else {
					// else, we are now heading to the next intermediate node
					CurrentIntermediateDestinationNode++;
					if (CurrentIntermediateDestinationNode >= PathToDestination.size()){
						std::cout << "PROBLEME" << '\n';
					} else {
						Local_DestinationPosition_Lon = PathToDestination[CurrentIntermediateDestinationNode]->GetLongitude();
						Local_DestinationPosition_Lat = PathToDestination[CurrentIntermediateDestinationNode]->GetLatitude();
					}
					RemainingDistance = DirectDistance(CurrentPosition_Lon, CurrentPosition_Lat, Local_DestinationPosition_Lon, Local_DestinationPosition_Lat);
				}
			}
			//std::cout << "C" << '\n';
			Cap_Destination = ComputeCoefA(Node(1, Local_DestinationPosition_Lon, Local_DestinationPosition_Lat), Node(1, PreviousPosition_Lon, PreviousPosition_Lat));
			Cap_Actuel = atan(Cap_Actuel) * 180 / LOCAL_PI;
			Cap_Destination = atan(Cap_Destination) * 180 / LOCAL_PI;

			float Cap_Derive = (Cap_Destination - Cap_Actuel);
			float OppositeAngle = asin(sin(Cap_Derive) * DrivenDistance / RemainingDistance);
			Corrective_Cap = OppositeAngle + Cap_Derive;
		} else {
			std::cout << "Can't compute corrective cap since size of PathToDestination vector is 0 and no destination has been set manually." << '\n';
		}
	} else {
		//Path not set
		std::cout << "Path NOT SET ! Error" << '\n';
	}
	return Corrective_Cap;
}

// Highest level function to display everything (Roads, Buildings, Locations, Path to destination).
void Map::Display(int close){
	switch (close){
		case 0:
		image = cv::Mat::zeros(cv::Size(LARGEUR_FENETRE, HAUTEUR_FENETRE), CV_8UC3);
		break;
		case 1:
		imageClose = cv::Mat::zeros(cv::Size(LARGEUR_FENETRE, HAUTEUR_FENETRE), CV_8UC3);
		break;
		default:
		cout << "Error, Provide either 0 for full map, 1 for a zoomed map\n";
		break;
	}
	CreateAll(close);
	DisplayMyPosition(close);
	DisplayPath(close);
	DisplayImage(close);
	//imshow("Image",imageLocale);
}

// Display effectively the Mat image with the OpenCV library.
int Map::DisplayImage(int close){
	if (close){
		cv::imshow("Image",imageClose);
	} else {
		cv::imshow("Image",image);
	}
	cv::waitKey(0);
	cout << "end" << '\n';
	return 1;
}

// Draw our position on the specified OpenCV image.
int Map::DisplayMyPosition(int close){
	if (close){
		cv::circle(imageClose, cv::Point(GetCloseDisplayX(CurrentPosition_Lon), GetCloseDisplayY(CurrentPosition_Lat)),  5, cv::Scalar(0, 0, 255, 255), -1, 8, 0);
	} else {
		cv::circle(image, cv::Point(GetDisplayX(CurrentPosition_Lon), GetDisplayY(CurrentPosition_Lat)),  5, cv::Scalar(0, 0, 255, 255), -1, 8, 0);
	}
	return 1;
}

// Returns Distance in meters between two points (longitude, latitude)
double Map::DirectDistance(double lat1, double lng1, double lat2, double lng2)
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

//Draw the buildings on the specified OpenCV image
void Map::DisplayAllBuildings(vector<Building *> v, int close, cv::Mat imageToWriteOn){
	for(vector<Building *>::iterator it = v.begin(); it != v.end(); ++it) {
		(*it)->Display(close, imageToWriteOn);
	}
}

//	Draw the possible destinations on the specified OpenCV image
void Map::DisplayAllUserNodes(vector<Node *> v, int close, cv::Mat imageToWriteOn){
	for(vector<Node *>::iterator it = v.begin(); it != v.end(); ++it) {
		(*it)->Display(close, imageToWriteOn);
	}
}

//	Draw every roads and the one we are on with a different color on the specified OpenCV image.
void Map::DisplayAllRoads(vector<Road *> v, int close, cv::Mat imageToWriteOn){
	int i = 0;
	for(vector<Road *>::iterator it = v.begin(); it != v.end(); ++it) {
		(*it)->Display(close, imageToWriteOn);
		i++;
	}
	cout << "roads displayed : " << i << '\n';
}

//	Draw every intermediate Nodes from our position to the destination on the specified OpenCV image
void Map::DisplayPath(int close){
	if (close){
		if (PathToDestination.size() != 0){
			for (int i=0 ; i<PathToDestination.size() ; i++){
				GetNodeById(PathToDestination[i]->GetId())->DisplayAsPathNode(close, imageClose);
			}
		} else {
			std::cout << "Can't display a path without nodes" << '\n';
		}
	} else {
		if (PathToDestination.size() != 0){
			for (int i=0 ; i<PathToDestination.size() ; i++){
				GetNodeById(PathToDestination[i]->GetId())->DisplayAsPathNode(close, image);
			}
		} else {
			std::cout << "Can't display a path without nodes" << '\n';
		}
	}
}

// 	@Getter : Steering Wheel position to be set to turn properly.
int Map::GetFront(){
	return Front;
}

//	Display set up calculation to change coordinates from longitude to x in pixels on the close display.
int Map::GetCloseDisplayX(double lon){
	double temp = ((lon - Min_lon)*Beta) - Delta_Lon;
	return temp;
}

//	Display set up calculation to change coordinates from latitude to y in pixels on the close display.
int Map::GetCloseDisplayY(double lat){
	double temp = ((Max_lat - lat)*Beta) - Delta_Lat;
	return temp;
}

//	Display set up calculation to change coordinates from longitude to x in pixels on the normal display.
int Map::GetDisplayX(double lon){
	double temp = ((lon - Min_lon)*Alpha) + 10;
	return temp;
}

//	Display set up calculation to change coordinates from latitude to y in pixels on the normal display.
int Map::GetDisplayY(double lat){
	double temp = ((Max_lat - lat)*Alpha) + 10;
	return temp;
}

// @Getter : Node(lat, long) closest to our current position.
Node * Map::GetClosestNode(){
	Node * CurrentClosestNodeLocal = NULL;
	double Distance_Min = 5000;
	std::cout << "A" << '\n';
	Road * CurrentRoad = GetRoadById(WhichRoad());
	if (CurrentRoad != NULL){
		vector<Node> MyRoadNodes = CurrentRoad->GetRoadNodes();
		std::cout << "size " << MyRoadNodes.size() << '\n';
		if (MyRoadNodes.size() != 0){
			for(vector<Node>::iterator it = MyRoadNodes.begin(); it != MyRoadNodes.end(); ++it) {
				std::cout << "B" << '\n';
				double distanceLocal = DirectDistance((*it).GetLatitude(), (*it).GetLongitude(), CurrentPosition_Lat, CurrentPosition_Lon);
				if(distanceLocal < Distance_Min){
					Distance_Min = distanceLocal;
					CurrentClosestNodeLocal = &(*it);
				}
			}
		}
	} else {
		std::cout << "No current road" << '\n';
	}
	return CurrentClosestNodeLocal;
}

// Returns the Node with the specified ID
Node * Map::GetUserNodeById(double id){
	Node * null = NULL;
	for(vector<Node *>::iterator it = User_Node.begin(); it != User_Node.end(); ++it) {
		if((*it)->GetId() == id){
			return *it;
		}
	}
	return null;
}

// Returns the Node with the specified ID
Node * Map::GetNodeById(double id){
	Node * null = NULL;
	for(vector<Node *>::iterator it = Node_Vec.begin(); it != Node_Vec.end(); ++it) {
		if((*it)->GetId() == id){
			return *it;
		}
	}
	return null;
}

// 	@Getter : Returns a Node specified by its ID.
Road * Map::GetRoadById(double id){
	std::cout << "id road " << id << '\n';
	Road * null = NULL;
	for(vector<Road *>::iterator it = Road_Vec.begin(); it != Road_Vec.end(); ++it) {
		if((*it)->GetId() == id){
			return *it;
		}
	}
	return null;
}

//	@Getter : Returns a vector of tuples made out of the Name of the destination and its according Node Id.
// 	TODO: Display this tuple to the user to give him the possibility to choose in which order he wants to visit them.
vector<tuple<string, double>> Map::GetTupleOfDestinations(){
	vector<tuple<string, double>> MyTupleOfDestinations;
	for (int i=0 ; i<User_Node.size() ; i++){
		MyTupleOfDestinations.push_back(std::make_tuple(User_Node[i]->GetName(), User_Node[i]->GetId()));
	}
	return MyTupleOfDestinations;
}

// Set the alpha factor that convert longitude/latitude in pixels
void Map::SetAlpha(){
	double Alpha_lon = (LARGEUR_FENETRE - 20)/(Max_lon - Min_lon);
	double Alpha_lat = (HAUTEUR_FENETRE - 20)/(Max_lat - Min_lat);
	if (Alpha_lon < Alpha_lat){
		Alpha = Alpha_lon;
	} else {
		Alpha = Alpha_lat;
	}
	cout << "Alpha = " << Alpha << '\n';
}

/*	Set the beta factor that convert longitude/latitude in pixels for the close display.
	TODO: the attribute given to the Display() function should be this coefficient to leave the
 	user the possibility to choose its zoom.
*/
void Map::SetBeta(){
	Beta = 5 * Alpha;
}

//	@Setter :	Once the path is calculated by the routing algorithm, it should be given to the map for guidance.
void Map::SetPath(vector<char *> path){
	for (int i=0 ; i<path.size() ; i++){
		Node * TempNode = GetNodeById(atof(path[i]));
		if (TempNode->IsNotRoutingNode() == 0){
			PathToDestination.push_back(TempNode);
			std::cout << TempNode->GetId() << '\n';
		} else {
			std::cout << "OKKK" << '\n';
		}
	}
	CurrentIntermediateDestinationNode = 0;
	PathSet = 1;
}

//	@Setter : 	Set the last available longitude and latitude of the car.
int Map::SetPosition(double lon, double lat){
	PreviousPosition_Lat = CurrentPosition_Lat;
	PreviousPosition_Lon = CurrentPosition_Lon;
	CurrentPosition_Lon = lon;
	CurrentPosition_Lat = lat;
	SetBeta();
	Delta_Lat = 0;
	Delta_Lon = 0;
	Delta_Lat = GetCloseDisplayY(CurrentPosition_Lat) - (HAUTEUR_FENETRE/2);
	Delta_Lon = GetCloseDisplayX(CurrentPosition_Lon) - (LARGEUR_FENETRE/2);
	WhichRoad();
	return 1;
}

//	Setter : Destination for debugging purposes.
void Map::SetDestinationManually(double lon, double lat){
	ManualDestinationSet = 1;
	PathSet = 1;
	DestinationPosition_Lon = lon;
	DestinationPosition_Lat = lat;
}

// Setter : Traditional way to set the destination by the Id of the destination node the user wants to reach.
// 			Calls the routing algorithm to calculates the shortest path.
void Map::SetDestination(double idDestNode){
	DestinationPosition_Lon = GetUserNodeById(idDestNode)->GetLongitude();
	DestinationPosition_Lat = GetUserNodeById(idDestNode)->GetLatitude();
	double CurrentClosestNode = GetClosestNode()->GetId();
	Router MyRouter;
	std::vector<char*> ipath;
	char pointA [10];
	sprintf (pointA, "%.0f", CurrentClosestNode);
	std::cout << "Current closest node : " << pointA << '\n';
	char pointB[10]; //= "-1858";
	sprintf (pointB, "%.0f", idDestNode);
	std::cout << "From : " << pointA << " ... to : " << pointB << '\n';
	ipath = MyRouter.getpath(pointA,pointB);
	int len = ipath.size();
	std::cout << "ipath length : " << len << '\n';
	SetPath(ipath);
}

// Returns an angle in randians from an angle in degrees.
double Map::ToRadians(double degrees)
{
	double radians = degrees * LOCAL_PI / 180;
	return radians;
}

// From a set of coordinates(long, lat), return the closest road from it.
// NB: Distance from a segment is different from a distance to straight line
double Map::WhichRoadWithLatLon(double lon, double lat){
	int Road_Nb = 0;
	double Distance_Min = 5000;
	for(vector<Road *>::iterator it = Road_Vec.begin(); it != Road_Vec.end(); ++it) {
		double Temp_Distance = (*it)->DistanceToCenter(lon, lat);
		//cout << "Distance to road " << (*it)->id << " is " << Temp_Distance << '\n';
		if(Temp_Distance < Distance_Min){
			Road_Nb = (*it)->GetId();
			Distance_Min = Temp_Distance;
		}
	}
	return Road_Nb;
}

// 	Set and Return the Current Road the car is on;
double Map::WhichRoad(){
	CurrentRoad = WhichRoadWithLatLon(CurrentPosition_Lon,CurrentPosition_Lat);
	std::cout << "Currently on road : " << CurrentRoad << '\n';
	return CurrentRoad;
}

//	From a corrective angle computes the Steering Wheel position (Front) @glabalVar and
//	returns the distance to drive with this position set.
float Map::GetFrontAndTurnDistance(float angle){
    if (angle < 0){     // RIGHT TURN
        if (angle > -30){                 // angle btw -30 and 0
            Front = 16;
            return (-angle*2/30);
        } else if (angle > -65){          // angle btw -65 and -30
            Front = 20;
            return (-angle*2/65);
        } else {                          // angle above -65
            Front = 24;
            return ((-angle)-17)/37.4;
        }
    } else {            // LEFT TURN
        if (angle < 20){
            Front = 8;
            return (angle/11);
        } else if (angle < 40){
            Front = 2;
            return (angle/40);
        } else {
            Front = 0;
            return (angle-24.4)/31.35;
        }
    }
}

/*
	Parse the xml file that contains the map. It is supposed to be entirely generic and should
	understand and work on any osm (OpenStreetMap) file.
	It create every usefull element to recreate the map (Nodes, Roads, Buildings).

*/
Map::Map(char * OsmFilePath){
	rapidxml::file<> xmlFile(OsmFilePath);
	image = cv::Mat::zeros(cv::Size(LARGEUR_FENETRE, HAUTEUR_FENETRE), CV_8UC3);
	imageClose = cv::Mat::zeros(cv::Size(LARGEUR_FENETRE, HAUTEUR_FENETRE), CV_8UC3);
	Min_lon = 50;
	Max_lon = 0;
	Min_lat = 50;
	Max_lat = 0;
	Alpha = 0;
	Beta = 0;
	Delta_Lon = 0;
	Delta_Lat = 0;
	static int CurrentRoad = 0;
	try {
		xml_document<> doc;
		doc.parse<0>(xmlFile.data());
		xml_node<> * root = doc.first_node();
		double id = 0;
		double lon = 0;
		double lat = 0;
		int NotARoutingNode = 0;
		cout.precision(12);
		double id_way = 0;
		xml_node<> * curr_node = root->first_node();
		while(curr_node){
			//Node
			if(strcmp(curr_node->name(), "node")==0){
				int user = 0;
				string name;
				id = 0;
				lon = 0;
				lat = 0;
				NotARoutingNode = 0;
				xml_attribute<> * attr = curr_node->first_attribute();
				while(attr){
					if (strcmp(attr->name(), "id") == 0){
						id = atof(attr->value());
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
							} else if (strcmp(tag->first_attribute()->value(), "barrier") == 0){
								NotARoutingNode = 1;
							}
						}
					}
					tag = tag->next_sibling();
				}
				//Create node if we have all the needed values
				if (id != 0 && lon != 0 && lat != 0){
					Node * myNode = new Node(id, lon, lat);
					if (NotARoutingNode){
						myNode->IsNotRoutingNode();
						std::cout << "NotARoutingNode() : " << myNode->GetId() << '\n';
					}
					if (user){
						myNode->SetName(name);
						User_Node.push_back(myNode);
						//myNode->ToString();
					} else {
						Node_Vec.push_back(myNode);
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
				int road = 0;
				string Name = "" ;
				vector<Node> Vec_Way_Node;
				if (strcmp(curr_node->first_attribute()->name(), "id") == 0){
					id_way = atoi(curr_node->first_attribute()->value());
					xml_node<> * curr_nd = curr_node->first_node();
					while(curr_nd){
						if (strcmp(curr_nd->name(), "nd") == 0){
							if(strcmp(curr_nd->first_attribute()->name(), "ref") == 0){
								double temp_id = (double)atof(curr_nd->first_attribute()->value());
								Node * Retrieved_Node = GetNodeById(temp_id);
								if (Retrieved_Node != NULL){
									if (Retrieved_Node->GetId() != 0){
										Vec_Way_Node.push_back(*Retrieved_Node);
									}
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
								} else if (strcmp(curr_nd->first_attribute()->value(), "highway") == 0){
									if ((strcmp(curr_nd->first_attribute()->next_attribute()->value(), "unclassified") == 0) ||
									(strcmp(curr_nd->first_attribute()->next_attribute()->value(), "service") == 0) ||
									(strcmp(curr_nd->first_attribute()->next_attribute()->value(), "footway") == 0) ||
									(strcmp(curr_nd->first_attribute()->next_attribute()->value(), "pedestrian") == 0) ||
									(strcmp(curr_nd->first_attribute()->next_attribute()->value(), "residential") == 0) ||
									(strcmp(curr_nd->first_attribute()->next_attribute()->value(), "living_street") == 0)){
										road = 1;
									}
								}
							}
						}
						curr_nd = curr_nd->next_sibling();
					}
					// Create the appropriate environment element if we have all the needed values
					if (Vec_Way_Node.size() >= 2){
						// Building ?
						if (building == 1){
							Building * myBuilding = new Building(id_way, Name, Vec_Way_Node);
							Building_Vec.push_back(myBuilding);
						}
						// Road ?
						else if (building == 0 && road == 1){
							BuildAllRoads(id_way, Vec_Way_Node);
							//Road myRoad(id_way, Vec_Way_Node[0], Vec_Way_Node[Vec_Way_Node.size()-1]);
							//Road_Vec.push_back(myRoad);
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
		SetAlpha();
		std::cout << "Number of Nodes : " << Node_Vec.size() << '\n';
		std::cout << "Number of Roads : " << Road_Vec.size() << '\n';
		std::cout << "Number of User Nodes : " << User_Node.size() << '\n';
	}
	catch (const runtime_error& error)
	{
		cout << "Problem when opening the map file : " << '\n';
	}
}

/********************************/
/*								*/
/*			NODE				*/
/*								*/
/********************************/

//	To string method to display a node used mainly for debugging purposes.
void Node::ToString(){
	if (user){
		cout << "Node called : " << Name << "    with id : " << id << " longitude : " << longitude << " and latitude : " << latitude << "\n";
	} else {
		cout << "My node with id : " << id << " longitude : " << longitude << " and latitude : " << latitude << "\n";
	}
}

//	Node constructor.
Node::Node(){
	id = 0;
}

// Node constructor with a specified id, and position.
Node::Node(double Node_Id, float lon, float lat){
	id = Node_Id;
	longitude = lon;
	latitude = lat;
}

// Not used.
bool Node::operator< (const Node &other) {
	return id < other.id;
}

// 	@Setter : in case the Node is a destination, it needs a Name to be identified by the user.
void Node::SetName(string NAME){
	Name = NAME;
	user = 1;
}

void Node::Display(int close, cv::Mat imageToWriteOn){
	if (close){
		cv::circle(imageToWriteOn, cv::Point(Map::GetCloseDisplayX(longitude), Map::GetCloseDisplayY(latitude)),  5, cv::Scalar(0, 20, 170, 255), 1, 8, 0);
		cv::putText(imageToWriteOn, Name, cv::Point(Map::GetCloseDisplayX(longitude)+5,Map::GetCloseDisplayY(latitude)+5),
		cv::FONT_HERSHEY_COMPLEX_SMALL, 0.5, cv::Scalar(200,200,250), 1, CV_AA);
	} else {
		if (user){
			cv::circle(imageToWriteOn, cv::Point(Map::GetDisplayX(longitude), Map::GetDisplayY(latitude)),  5, cv::Scalar(0, 20, 170, 255), 1, 8, 0);
			cv::putText(imageToWriteOn, Name, cv::Point(Map::GetDisplayX(longitude)+5,Map::GetDisplayY(latitude)+5),
			cv::FONT_HERSHEY_COMPLEX_SMALL, 0.5, cv::Scalar(200,200,250), 1, CV_AA);
		}
	}
}

void Node::DisplayAsPathNode(int close, cv::Mat imageToWriteOn){
	if (close){
		cv::circle(imageToWriteOn, cv::Point(Map::GetCloseDisplayX(longitude), Map::GetCloseDisplayY(latitude)),  5, cv::Scalar(252, 189, 47, 255), 1, 8, 0);
	} else {
		cv::circle(imageToWriteOn, cv::Point(Map::GetDisplayX(longitude), Map::GetDisplayY(latitude)),  5, cv::Scalar(252, 189, 47, 255), 1, 8, 0);
	}
}

float Node::GetLatitude(){
	return latitude;
}
float Node::GetLongitude(){
	return longitude;
}
double Node::GetId(){
	return id;
}

void Node::NotARoutingNode(){
	NotRoutingNode = 1;
}

int Node::IsNotRoutingNode(){
	return NotRoutingNode;
}

string Node::GetName(){
	return Name;
}

/********************************/
/*								*/
/*			ROAD				*/
/*								*/
/********************************/

void Road::Compute_Coefs(){
	a = (end.GetLatitude() - begin.GetLatitude())/(end.GetLongitude() - begin.GetLongitude());
	b = begin.GetLatitude() - begin.GetLongitude() * a;
}

void Road::ToString(){
	cout.precision(12);
	cout << "My road with id : " << id << " has an equation : " << a << " x + " << b << "\n";
}

Road::Road(double Road_Id, vector<Node> VEC){
	id = Road_Id;
	Road_Nodes = VEC;
	Compute_Coefs();
}

Road::Road(double Road_Id, Node b, Node e){
	id = Road_Id;
	begin = b;
	end = e;
	Compute_Coefs();
}

void Road::SetEndNode(Node e){
	end = e;
	Compute_Coefs();
}

void Road::SetVecRoadNodes(std::vector<Node> VEC){
	Road_Nodes = VEC;
	std::cout << "Size of Road nodes vec " << Road_Nodes.size() << '\n';
}

double Road::DistanceToCenter(double lon, double lat){
	double Proj_Lon = (lon + a*lat - a*b)/(1 + a*a);
	double Proj_Lat = (a*lon + a*a*lat + b)/(1 + a*a);
	if (Proj_Lat > begin.GetLatitude() && Proj_Lat > end.GetLatitude()){
		if (end.GetLatitude() > begin.GetLatitude()){
			return Map::DirectDistance(lat, lon, end.GetLatitude(), end.GetLongitude());
		} else {
			return Map::DirectDistance(lat, lon, begin.GetLatitude(), begin.GetLongitude());
		}
	} else if (Proj_Lat < begin.GetLatitude() && Proj_Lat < end.GetLatitude()){
		if (end.GetLatitude() < begin.GetLatitude()){
			return Map::DirectDistance(lat, lon, end.GetLatitude(), end.GetLongitude());
		} else {
			return Map::DirectDistance(lat, lon, begin.GetLatitude(), begin.GetLongitude());
		}
	} else {
		return Map::DirectDistance(lat, lon, Proj_Lat, Proj_Lon);
	}
}

void Road::Display(int close, cv::Mat imageToWriteOn){
	if (close){
		if (!Map::Beta){
			Map::SetBeta();
		}
		if (id == Map::CurrentRoad){
			cv::line(imageToWriteOn, cv::Point(Map::GetCloseDisplayX(begin.GetLongitude()),Map::GetCloseDisplayY(begin.GetLatitude())), cv::Point(Map::GetCloseDisplayX(end.GetLongitude()), Map::GetCloseDisplayY(end.GetLatitude())), cv::Scalar( 255, 0, 0, 255),  1, 0 );
		} else {
			cv::line(imageToWriteOn, cv::Point(Map::GetCloseDisplayX(begin.GetLongitude()),Map::GetCloseDisplayY(begin.GetLatitude())), cv::Point(Map::GetCloseDisplayX(end.GetLongitude()), Map::GetCloseDisplayY(end.GetLatitude())), cv::Scalar( 110, 220, 100),  1, 0 );
		}
	} else {
		if (Map::Alpha){		// Alpha needs to be defined to get (x,y) coordinates
			int y1 = Map::GetDisplayY(begin.GetLatitude());
			int x1 = Map::GetDisplayX(begin.GetLongitude());
			int y2 = Map::GetDisplayY(end.GetLatitude());
			int x2 = Map::GetDisplayX(end.GetLongitude());
			if (id == Map::CurrentRoad){
				cv::line(imageToWriteOn, cv::Point(x1,y1), cv::Point(x2, y2), cv::Scalar( 255, 0, 0, 255),  1, 0 );
			} else {
				cv::line(imageToWriteOn, cv::Point(x1,y1), cv::Point(x2, y2), cv::Scalar( 110, 220, 100),  1, 0 );
			}
		}
	}
}

vector<Node> Road::GetRoadNodes(){
	return Road_Nodes;
}

float Road::GetA(){
	return a;
}
float Road::GetB(){
	return b;
}
double Road::GetId(){
	return id;
}
Node Road::GetBegin(){
	return begin;
}
Node Road::GetEnd(){
	return end;
}


/********************************/
/*								*/
/*			BUILDING			*/
/*								*/
/********************************/

Building::Building(int ID, string NAME, vector<Node> VEC){
	id = ID;
	Name = NAME;
	Building_Corner_Vec = VEC;
}

//	Enable the building to have more than 4 walls.
void Building::Display(int close, cv::Mat imageToWriteOn){
	if (close){
		if (Map::Beta){
			long VecSize = Building_Corner_Vec.size();
			long NumberOfCoordinates = VecSize*2;
			int XAndYs [NumberOfCoordinates];						// EVEN numbers are the Xs and ODD numbers are Ys
			XAndYs[0] = Map::GetCloseDisplayX(Building_Corner_Vec[0].GetLongitude());
			XAndYs[1] = Map::GetCloseDisplayY(Building_Corner_Vec[0].GetLatitude());
			int index;
			for(index = 1; index < VecSize ; index++){
				XAndYs[index*2] = Map::GetCloseDisplayX(Building_Corner_Vec[index].GetLongitude());
				XAndYs[index*2+1] = Map::GetCloseDisplayY(Building_Corner_Vec[index].GetLatitude());
				cv::line(imageToWriteOn, cv::Point(XAndYs[(index-1)*2],XAndYs[(index-1)*2+1]), cv::Point(XAndYs[index*2], XAndYs[index*2+1]), cv::Scalar( 0, 220, 100, 255),  1, 0 );
			}
			cv::line(imageToWriteOn, cv::Point(XAndYs[(index-1)*2],XAndYs[(index-1)*2+1]), cv::Point(XAndYs[0], XAndYs[1]), cv::Scalar( 0, 220, 100, 255),  1, 0 );
		}
	} else {
		if (Map::Alpha){
			long VecSize = Building_Corner_Vec.size();
			long NumberOfCoordinates = VecSize*2;
			int XAndYs [NumberOfCoordinates];						// EVEN numbers are the Xs and ODD numbers are Ys
			XAndYs[0] = Map::GetDisplayX(Building_Corner_Vec[0].GetLongitude());
			XAndYs[1] = Map::GetDisplayY(Building_Corner_Vec[0].GetLatitude());
			int index;
			for(index = 1; index < VecSize ; index++){
				XAndYs[index*2] = Map::GetDisplayX(Building_Corner_Vec[index].GetLongitude());
				XAndYs[index*2+1] = Map::GetDisplayY(Building_Corner_Vec[index].GetLatitude());
				cv::line(imageToWriteOn, cv::Point(XAndYs[(index-1)*2],XAndYs[(index-1)*2+1]), cv::Point(XAndYs[index*2], XAndYs[index*2+1]), cv::Scalar( 0, 220, 100, 255),  1, 0 );
			}
			cv::line(imageToWriteOn, cv::Point(XAndYs[(index-1)*2],XAndYs[(index-1)*2+1]), cv::Point(XAndYs[0], XAndYs[1]), cv::Scalar( 0, 220, 100, 255),  1, 0 );
		}
	}
}

string Building::GetName(){
	return Name;
}

double Building::GetId(){
	return id;
}
