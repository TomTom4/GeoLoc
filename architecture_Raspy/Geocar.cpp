#include "Geocar.h"

using namespace std;

	//Add your methodes over here 

void testSpi(Mediator *mediator, Spi *spi){

	mediator->printModel();
	//PARAMETRAGE BIB WIRINGPI
	wiringPiSetup ();

	//PARAMETRAGE SPI
	wiringPiSPISetup(0,1000000);
	//	fprintf("SPI Setup failed ");

	mediator->printModel();

	for(int i=0;i<100;i++)
	{
		mediator->addPwmMotorBack(30);
		spi->majCar();
		mediator->printEncoder();
		delay(100);
		cout << endl;
	}
	mediator->addPwmMotorBack(0);
	spi->majCar();
}

int testNavigation(){

	//rapidxml::file<> xmlFile("heavy.osm");
	Map MyMap("heavy.osm");

	std::vector<tuple<string, double>> MyVectorOfUserDestination = MyMap.GetTupleOfDestinations();

	double ExamplePointLat = 43.570358;
	double ExamplePointLon =  1.466047;

	//double ExampleDestLat = 43.5708618;
	//double ExampleDestLon = 1.4670463;
	MyMap.SetPosition(ExamplePointLon,ExamplePointLat);
	MyMap.SetDestination(-1858);
	//MyMap.WhichRoadWithLatLon();

	MyMap.Display(0);
	MyMap.Display(1);

	MyMap.SetPosition(1.466078, 43.570376);
	std::cout << "GetCorrectiveHeading(3) : " << MyMap.GetCorrectiveHeading(3.0) << '\n';

	MyMap.Display(1);

	MyMap.SetPosition(1.466117,43.570386);
	std::cout << "GetCorrectiveHeading(3) : " << MyMap.GetCorrectiveHeading(3.0) << '\n';

	MyMap.Display(1);

/*
	MyMap.CreateAll(0, MyMap.image);
	MyMap.DisplayMyPosition();
	MyMap.DisplayImage(0);

	MyMap.CreateAll(1, MyMap.imageClose);
	MyMap.DisplayCloseMyPosition();
	MyMap.DisplayImage(1);
*/
/*
	// new

	double CurrentClosestNode = MyMap.GetClosestNode()->GetId();

	// Zepeng Code

	Router MyRouter;

	std::vector<char*> ipath;

	//char pointA[7] = "-1630";
	char pointA [10];
	// Need to remove the decimals
	sprintf (pointA, "%.0f", CurrentClosestNode);
	std::cout << "Current closest node : " << pointA << '\n';
	char pointB[7] = "-1858";

	std::cout << "From : " << pointA << " ... to : " << pointB << '\n';
	ipath = MyRouter.getpath(pointA,pointB);
	int len = ipath.size();
	std::cout << "ipath length : " << len << '\n';

	// End Zepeng Code //

	MyMap.SetPath(ipath);
	std::cout << "The cap to follow : " << MyMap.CapAlgorithm() << '\n';
	MyMap.DisplayPath(0, MyMap.image);
	MyMap.DisplayImage(0);
*/
	return 1;
}


int main(){
	//Controler *controler;
	Mediator *mediator;
	Spi *spi;
	Navigation *navigator;
	
	mediator = Mediator::instance();
	//controler = Controler::instance();
	spi = Spi::instance();
	navigator = Navigation::instance();
	cout << "start thread " << endl;
	spi->startThread();

	//temporary :only to test of spi
	//testSpi(mediator, spi);
	while(1)
	{
		usleep(1000000);
		cout << " main "<< endl;
	}
	return 0;
}
