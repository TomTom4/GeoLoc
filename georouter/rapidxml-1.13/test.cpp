#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <string.h>
#include "rapidxml_utils.hpp"

#define LOCAL_PI 3.1415926535897932385 

using namespace rapidxml;

class Node{

	public :
		int id;
		float latitude;
		float longitude;

		void ToString(){
			std::cout << "My node has ... id : " << id << " longitude : " << longitude << " and latitude : " << latitude << "\n";
		}
		Node(){
			id = 0;
		}

		Node(int Node_Id, float lon, float lat){
			id = Node_Id;
			longitude = lon;
			latitude = lat;
		}
};

class Road{

	public :
		int id;
		Node begin;
		Node end;
		//The model is like : ax + b
		//longitude is x
		//latitude is y
		float a;
		float b;
		int width;

		void ToString(){
			std::cout.precision(12);
			std::cout << "My road with id : " << id << " has an equation : " << a << " x + " << b << "\n";
		}

		Road(int Road_Id, Node b, Node e){
			id = Road_Id;
			begin = b;
			end = e;
		}

		void Compute(){
			a = (end.latitude - begin.latitude)/(end.longitude - begin.longitude);
			b = begin.latitude - begin.longitude * a;
		}
};

Node GetNodeById(int id, std::vector<Node> v){
	Node null;
	for(std::vector<Node>::iterator it = v.begin(); it != v.end(); ++it) {
	    if(it->id == id){
			return *it;
		}
	}
	return null;
}

double ToRadians(double degrees)
{
  double radians = degrees * LOCAL_PI / 180;
  return radians;
}

double DirectDistance(double lat1, double lng1, double lat2, double lng2)
{
  double earthRadius = 3958.75;
  double dLat = ToRadians(lat2-lat1);
  double dLng = ToRadians(lng2-lng1);
  double a = sin(dLat/2) * sin(dLat/2) +
             cos(ToRadians(lat1)) * cos(ToRadians(lat2)) *
             sin(dLng/2) * sin(dLng/2);
  double c = 2 * atan2(sqrt(a), sqrt(1-a));
  double dist = earthRadius * c;
  double meterConversion = 1609.00;
  return dist * meterConversion;
}

int main(){

	rapidxml::file<> xmlFile("test.xml");
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());
	xml_node<> * root = doc.first_node();

	std::vector<Node> Node_Vec;
	int id = 0;
	double lon = 0;
	double lat = 0;
	std::cout.precision(12);
	int id_road = 0;
	//std::cout << root->first_node()->name() << "\n";

	xml_node<> * curr_node = root->first_node();
	while(curr_node){

		//Node
		if(strcmp(curr_node->name(), "node")==0){
			id = 0;
			lon = 0;
			lat = 0;
			xml_attribute<> * attr = curr_node->first_attribute();
			while(attr){
				if (strcmp(attr->name(), "id") == 0){
					id = atoi(attr->value());
					//std::cout << attr->value() << "\n";
				} else if (strcmp(attr->name(),  "lat") ==0){
					lat = atof(attr->value());
					//std::cout << std::fixed << attr->value()<< "\n";
				} else if (strcmp(attr->name(), "lon") ==0){
					lon = atof(attr->value());
					//std::cout << attr->value() << "\n";
				}
				attr = attr->next_attribute();
			}//while

			//Create node if we have all the needed values
			if (id != 0 && lon != 0 && lat != 0){
				Node node(id, lon, lat);
				node.ToString();
				Node_Vec.push_back(node);
			}
		} // Node

		//	Way
		if(strcmp(curr_node->name(), "way")==0){
			id_road = 0;
			std::vector<Node> Vec_Road_Node;
			if (strcmp(curr_node->first_attribute()->name(), "id") == 0){
				id_road = atoi(curr_node->first_attribute()->value());
				xml_node<> * curr_nd = curr_node->first_node();
				while(curr_nd){
					if (strcmp(curr_nd->name(), "nd") == 0){
						if(strcmp(curr_nd->first_attribute()->name(), "ref") == 0){
							int temp_id = atof(curr_nd->first_attribute()->value());
							Node Retrieved_Node = GetNodeById(temp_id, Node_Vec);
							if (Retrieved_Node.id != 0){
								Vec_Road_Node.push_back(Retrieved_Node);
							} else {
								std::cout << "Pb GetNodeById()" << '\n';
							}
						} else {
							std::cout << "Pb ref" << '\n';
						}
					} else {
						std::cout << "Pb nd" << '\n';
					}
					curr_nd = curr_nd->next_sibling();
				}
				Road myRoad(id_road, Vec_Road_Node[0], Vec_Road_Node[Vec_Road_Node.size()-1]);
				myRoad.Compute();
				myRoad.ToString();
			} else {
				std::cout << "Pb id" << '\n';
			}

		}

		//	Next sibling
		curr_node = curr_node->next_sibling();
	}
	std::cout << Node_Vec.size() << "\n";
}


/*
	for (xml_node<> * current_node = root->first_node() ; current_node ; current_node = current_node->next_node())
	{

	}
*/
