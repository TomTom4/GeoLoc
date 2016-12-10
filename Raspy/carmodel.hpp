#ifndef PARSERV1_H
#define PARSERV1_H

#include <string>
#include <vector>



float ComputeCoefA(Node begin, Node end){
	return (end.GetLatitude() - begin.GetLatitude())/(end.GetLongitude() - begin.GetLongitude());
}

float CapAlgorithm();

// Distance between two points (longitude, latitude)
double DirectDistance(double lat1, double lng1, double lat2, double lng2);

int SetPosition(double lon, double lat);

void SetDestination(double lon, double lat);

double ToRadians(double degrees);

#endif
