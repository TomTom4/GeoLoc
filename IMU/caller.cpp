#include "Imu.h"

int main(){
    Imu MyImu = new Imu();
    MyImu.InitStruct();
    MyImu.getAllData();
    return 1;
}
