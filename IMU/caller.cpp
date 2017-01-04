#include "Imu.h"
#include <unistd.h>

int main(){
    Imu MyImu;
    MyImu.InitStruct();
    MyImu.getAllData();

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

    MyImu.get_calibration_Data ();

    while(times){
        MyImu.DisplayHeading();
    }

    return 1;
}
