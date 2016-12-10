//
//  caller.cpp
//  OpenCVParser
//
//  Created by Guillaume GRANIE on 06/12/2016.
//

#include <stdio.h>
#include <iostream>

#include "parserV1.hpp"

int main(){
    init();

	double ExamplePointLat = 43.570779;
    double ExamplePointLon =  1.466925;

    double ExamplePointLat_2 = 43.570825;
    double ExamplePointLon_2 = 1.466964;

    double ExampleDestLat = 43.5708618;
    double ExampleDestLon = 1.4670463;
    SetPosition(ExamplePointLon,ExamplePointLat);
    SetDestination(ExampleDestLon, ExampleDestLat);
    WhichRoadWithLatLon();
    DisplayMyPosition();
    CreateAll(0);
    DisplayImage(0);
    CreateAll(1);
    DisplayCloseMyPosition();
    DisplayImage(1);
    SetPosition(ExamplePointLon_2, ExamplePointLat_2);
    std::cout << "The cap to follow : " << CapAlgorithm() << '\n';
    CreateAll(1);
    DisplayCloseMyPosition();
    DisplayImage(1);
    return 1;
}
