#ifndef PARSERV1_H
#define PARSERV1_H

#include <string>
#include <vector>

float ComputeCoefA(double long_start, double lat_start, double long_end, double lat_end);

float CapAlgorithm();

// Distance between two points (longitude, latitude)
double DirectDistance(double lat1, double lng1, double lat2, double lng2);

int SetPosition(double lon, double lat);

void SetDestination(double lon, double lat);

double ToRadians(double degrees);

bool test_fin();

#endif
