#include "Mediator.h"

using namespace std;

	// setting s_instance which is a static attribut that needs to be setted
	Mediator *Mediator::s_instance = 0;
	// implementing Mediator constructor
	Mediator::Mediator(): m_model(){}
	
	Mediator* Mediator::instance(){
		if(Mediator::s_instance)
			Mediator::s_instance = new Mediator;
		return Mediator::s_instance;
	}

	
