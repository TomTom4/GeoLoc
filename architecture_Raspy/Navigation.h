#ifndef DEF_NAVIGATION
#define DEF_NAVIGATION

#include "CapModel.h"

class Navigation{

	public:
		//methodes
		static Navigation *instance();
	private:
		//Constructeur
		Navigation();
		//attributs
		static Navigation *s_instance;
		CapModel m_cap_model;
	
};

#endif
