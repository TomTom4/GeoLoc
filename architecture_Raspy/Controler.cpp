#include "Controler.h"

using namespace std;
// add your methods here
	Controler *Controler::s_instance = 0;
	Controler *Controler::instance(){
		if(!Controler::s_instance)
			Controler::s_instance = new Controler;
		return Controler::s_instance;
	}
	Controler::Controler(){}
