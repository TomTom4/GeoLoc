#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include <carmodel.hpp>

#define LOCAL_PI 3.1415926535897932385
#define LARGEUR_FENETRE 700
#define HAUTEUR_FENETRE 700
#define DISTANCE_BETWEEN_ACQUISITIONS 5
#define GPS_UNCERTAINTY 2.5

double CurrentPosition_Lon = 0;
double CurrentPosition_Lat = 0;
double PreviousPosition_Lon = 0;
double PreviousPosition_Lat = 0;
double DestinationPosition_Lon = 0;
double DestinationPosition_Lat = 0;


float ComputeCoefA(Node begin, Node end){
	return (end.GetLatitude() - begin.GetLatitude())/(end.GetLongitude() - begin.GetLongitude());
}


float CapAlgorithm(){
	// Need to have called SetPosition() right before and 5 meters before
	// Our CurrentPosition_Lon and CurrentPosition_Lat are the GPS position.
	// Our PreviousPosition_Lon and PreviousPosition_Lat are the origins.
	// distance in [meters]

	std::cout << "Distance brute avant correction de position: " << DirectDistance(CurrentPosition_Lon, CurrentPosition_Lat, PreviousPosition_Lon, PreviousPosition_Lat) << '\n';
	double distance = DirectDistance(CurrentPosition_Lat, CurrentPosition_Lon, PreviousPosition_Lat, PreviousPosition_Lon);
	// We assume an uncertainty of 2.5 meters on the GPS measure.
	float Cap_Actuel = 0;
	float Cap_Destination = 0;

	Cap_Actuel = ComputeCoefA(Node(1, CurrentPosition_Lon, CurrentPosition_Lat), Node(2, PreviousPosition_Lon, PreviousPosition_Lat));

	//Correction de position
	float rapport = DISTANCE_BETWEEN_ACQUISITIONS / distance;
	CurrentPosition_Lon = PreviousPosition_Lon + rapport * (CurrentPosition_Lon - PreviousPosition_Lon);
	CurrentPosition_Lat = PreviousPosition_Lat + rapport * (CurrentPosition_Lat - PreviousPosition_Lat);

	std::cout << "Distance normalement égale à 5 après Correction de position: " << DirectDistance(CurrentPosition_Lon, CurrentPosition_Lat, PreviousPosition_Lon, PreviousPosition_Lat) << '\n';

	double RemainingDistance = DirectDistance(CurrentPosition_Lon, CurrentPosition_Lat, DestinationPosition_Lon, DestinationPosition_Lat);

	Cap_Destination = ComputeCoefA(Node(1, DestinationPosition_Lon, DestinationPosition_Lat), Node(1, PreviousPosition_Lon, PreviousPosition_Lat));

	Cap_Actuel = atan(Cap_Actuel) * 180 / LOCAL_PI;
	Cap_Destination = atan(Cap_Destination) * 180 / LOCAL_PI;

	float Cap_Derive = (Cap_Destination - Cap_Actuel);

	float OppositeAngle = asin(sin(Cap_Derive)*5/RemainingDistance);

	float Corrective_Cap = OppositeAngle + Cap_Derive;

	return Corrective_Cap;
}

// Distance between two points (longitude, latitude)
double DirectDistance(double lat1, double lng1, double lat2, double lng2)
{
	double earthRadius = 6371000; //meters
	double dLat = ToRadians(lat2-lat1);
	double dLng = ToRadians(lng2-lng1);
	double a = sin(dLat/2) * sin(dLat/2) +
	cos(ToRadians(lat1)) * cos(ToRadians(lat2)) *
	sin(dLng/2) * sin(dLng/2);
	double c = 2 * atan2(sqrt(a), sqrt(1-a));
	float dist = (float) (earthRadius * c);
	return dist;
}


int SetPosition(double lon, double lat){
	PreviousPosition_Lat = CurrentPosition_Lat;
	PreviousPosition_Lon = CurrentPosition_Lon;
	CurrentPosition_Lon = lon;
	CurrentPosition_Lat = lat;
	SetBeta();
	Delta_Lat = 0;
	Delta_Lon = 0;
	Delta_Lat = GetCloseDisplayY(CurrentPosition_Lat) - (HAUTEUR_FENETRE/2);
	Delta_Lon = GetCloseDisplayX(CurrentPosition_Lon) - (LARGEUR_FENETRE/2);
	return 1;
}

void SetDestination(double lon, double lat){
	DestinationPosition_Lon = lon;
	DestinationPosition_Lat = lat;
}

double ToRadians(double degrees)
{
	double radians = degrees * LOCAL_PI / 180;
	return radians;
}
