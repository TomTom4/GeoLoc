#include "Navigation.h"

using namespace std;

	//Add your methodes over here

	Navigation *Navigation::s_instance = 0;//setting s_instance because it is a static attribut.

	// this function replace the construtor of the object
	Navigation *Navigation::instance(){
		if(!Navigation::s_instance)
			Navigation::s_instance = new Navigation;
		return Navigation::s_instance;
	}
	Navigation::Navigation():m_map("heavy.osm"){}
