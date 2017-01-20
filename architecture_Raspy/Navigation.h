#ifndef DEF_NAVIGATION
#define DEF_NAVIGATION

#include "parserV1.hpp"

class Navigation{

	public:
		//methodes
		static Navigation *instance();
		Map* m_map;
	private:
		//Constructeur
		Navigation();
		//attributs
		static Navigation *s_instance;
		
	
};

#endif
