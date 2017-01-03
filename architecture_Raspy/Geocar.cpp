#include "Geocar.h"

using namespace std;

	//Add your methodes over here 

int main(){
	Controler *controler;
	Mediator *mediator;
	Spi *spi;
	
	mediator = Mediator::instance();
	controler = Controler::instance();
	spi = Spi::instance();
	
	return 0;
}
