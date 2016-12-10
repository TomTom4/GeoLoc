//
//  caller.cpp
//  OpenCVParser
//
//  Created by Guillaume GRANIE on 06/12/2016.
//

#include "parserV1.hpp"

int main(){
    init();

	double ExamplePointLat = 43.570216;
    double ExamplePointLon = 1.468254;
    SetPosition(ExamplePointLon,ExamplePointLat);
    WhichRoadWithLatLon();
    DisplayMyPosition();
    CreateAll(0);
    DisplayImage(0);
    CreateAll(1);
    DisplayCloseMyPosition();
    DisplayImage(1);
    DisplayImage(0);
    return 1;
}
