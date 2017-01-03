#include "Controler.h"

using namespace std;

	// add your methods here

	Controler *Controler::s_instance = 0;//setting s_instance because it is a static attribut. 

	// this function replace the construtor of the object
	Controler *Controler::instance(){
		if(!Controler::s_instance)
			Controler::s_instance = new Controler;
			Controler::s_instance->m_mediator = Mediator::instance();
		return Controler::s_instance;
	}
	Controler::Controler(){}
