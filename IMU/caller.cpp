#include "Imu.h"

int main(){
    Imu MyImu;
    MyImu.InitStruct();
    MyImu.getAllData();

    int times = 20;
    while(times){
        MyImu.getAcceleroData();
        times--;
        usleep(1000);
    }

    times = 20;
    while(times){
        MyImu.getGyroData();
        times--;
        usleep(1000);
    }

    times = 20;
    while(times){
        MyImu.getmagnetoData();
        times--;
        usleep(1000);
    }
    return 1;
}
