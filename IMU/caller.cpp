#include "Imu.h"

int main(){
    Imu MyImu;
    MyImu.InitStruct();
    MyImu.getAllData();

    int times = 20;
    while(times){
        MyImu.getAcceleroData();
        times--;
    }

    times = 20;
    while(times){
        MyImu.getGyroData();
        times--;
    }

    times = 20;
    while(times){
        MyImu.getmagnetoData();
        times--;
    }
    return 1;
}
