#include "LocationInterface.h"

using namespace std;

	//Add your methodes over here

	LocationInterface *LocationInterface::s_instance = 0;//setting s_instance because it is a static attribut. 

	// this function replace the construtor of the object
	LocationInterface *LocationInterface::instance(){
		if(!LocationInterface::s_instance)
			LocationInterface::s_instance = new LocationInterface;
		return LocationInterface::s_instance;
	}
	LocationInterface::LocationInterface(){}
