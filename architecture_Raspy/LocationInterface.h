#ifndef DEF_LOCATION_INTERFACE
#define DEF_LOCATION_INTERFACE

class LocationInterface{


	public:
		//methodes
		static LocationInterface *instance();
	private:
		//Constructeur
		LocationInterface();
		//attributs
		static LocationInterface *s_instance;

};

#endif
