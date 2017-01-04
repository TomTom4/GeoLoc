#include <stdint.h>
#include "Imu.h"
#include <unistd.h>

int main(){
    Imu MyImu;
//    MyImu.InitStruct();
//    MyImu.getAllData();
/*
    int times = 20;
    while(times){
        MyImu.getAcceleroData();
    	MyImu.DisplayAcceleroData();
	times--;
        usleep(2000000);
    }

    times = 20;
    while(times){
        MyImu.getGyroData();
	MyImu.DisplayGyroData();
        times--;
        usleep(2000000);
    }

    times = 20;
    while(times){
        MyImu.getmagnetoData();
	    MyImu.DisplayMagnetoData();
        times--;
        usleep(2000000);
    }
*/
    int times = 500;
    MyImu.get_calibration_Data();
    MyImu.DisplayHeading();
/*
    while(times){
        MyImu.DisplayHeading();
	usleep(10000);    
	times--;
    }
*/

    return 1;
}
