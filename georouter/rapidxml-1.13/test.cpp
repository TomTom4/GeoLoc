#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <string.h>

#include "rapidxml_utils.hpp"

using namespace rapidxml;

class Node{

	public :
		int id;
		float lon;
		float lat;

		void ToString(){
			std::cout << "My node has ... id : " << id << " longitude : " << lon << "\n"; 
		}

		Node(int Node_Id, float longitude, float latitude){
			id = Node_Id;
			lon = longitude;
			lat = latitude;
		}
};

int main(){

	rapidxml::file<> xmlFile("test.xml");
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());
	std::cout << "First node : " << doc.first_node()->name() << "\n";
	xml_node<> * root = doc.first_node();
	//xml_node<> * node = root;
	
	std::cout << root->first_node()->name() << "\n"; 
		int id = 0;
		double lon = 0;
		double lat = 0;
		xml_attribute<> * attr = root->first_node()->first_attribute();
		while(attr)
		{
			if (strcmp(attr->name(), "id") == 0){
				id = atoi(attr->value());
				std::cout << attr->value() << "\n";
			} else if (strcmp(attr->name(),  "lat") ==0){
				lat = atof(attr->value());
				std::cout.precision(8);
				std::cout << std::fixed << attr->value()<< "\n";
			} else if (strcmp(attr->name(), "lon") ==0){
				lon = atof(attr->value());
				std::cout << attr->value() << "\n";
			}
			if (id != 0 && lon != 0 && lat != 0){
				Node node(id, lon, lat);
				node.ToString();
			}
			std::cout << attr->name() << "\n";
			attr = attr->next_attribute();
		}
		//Node node(root.first_node()
	
}

/*
	for (xml_node<> * current_node = root->first_node() ; current_node ; current_node = current_node->next_node())
	{
		
	}
*/
