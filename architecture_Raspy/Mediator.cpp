#include "Mediator.h"

using namespace std;

	// Add your methodes over here
	Mediator *Mediator::s_instance = 0;
	Mediator::Mediator(): m_model(){}
	
	Mediator* Mediator::instance(){
		if(Mediator::s_instance)
			Mediator::s_instance = new Mediator;
		return Mediator::s_instance;
	}
