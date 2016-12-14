//
//  caller.cpp
//  OpenCVParser
//
//  Created by Guillaume GRANIE on 06/12/2016.
//

#include <stdio.h>
#include <iostream>

#include "parserV1.hpp"
#include "rapidxml_utils.hpp"


int main(){

    rapidxml::file<> xmlFile("heavy.osm");
    Map MyMap(xmlFile);

	double ExamplePointLat = 43.570779;
    double ExamplePointLon =  1.466925;

    double ExamplePointLat_2 = 43.570825;
    double ExamplePointLon_2 = 1.466964;

    double ExampleDestLat = 43.5708618;
    double ExampleDestLon = 1.4670463;
    MyMap.SetPosition(ExamplePointLon,ExamplePointLat);
    MyMap.SetDestination(ExampleDestLon, ExampleDestLat);
    MyMap.WhichRoadWithLatLon();
    MyMap.DisplayMyPosition();
    MyMap.CreateAll(0, MyMap.image);
    MyMap.DisplayImage(0);
    MyMap.CreateAll(1, MyMap.imageClose);
    MyMap.DisplayCloseMyPosition();
    MyMap.DisplayImage(1);
    MyMap.SetPosition(ExamplePointLon_2, ExamplePointLat_2);
    std::cout << "The cap to follow : " << MyMap.CapAlgorithm() << '\n';
    MyMap.CreateAll(1, MyMap.imageClose);
    MyMap.DisplayCloseMyPosition();
    MyMap.DisplayImage(1);
    return 1;
}
