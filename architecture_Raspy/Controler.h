#ifndef DEF_CONTROLER
#define DEF_CONTROLER

#include "Mediator.h"

class Controler{
	public:
		//methodes
		static Controler *instance();
	private:
		//Constructeur
		Controler();
		//attributs
		static Controler *s_instance;
		Mediator *m_mediator;
};
#endif
