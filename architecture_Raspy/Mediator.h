#ifndef DEF_MEDIATOR
#define DEF_MEDIATOR

#include "Model.h"

class Mediator{

	public:
		static Mediator *instance();
	private:
		Mediator();
		static Mediator *s_instance;
		Model m_model;
		

};

#endif
