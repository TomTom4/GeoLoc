#ifndef DEF_NAVIGATION
#define DEF_NAVIGATION

#include "parserV1.hpp"

class Navigation{

	public:
		//methodes
		static Navigation *instance();
	private:
		//Constructeur
		Navigation();
		//attributs
		static Navigation *s_instance;
		Map m_map;
	
};

#endif
