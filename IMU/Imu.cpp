#include "Imu.h"

  public:

    /***********************************SETUP*************************************/
    /* Init all IMU sensors                                                      */
    /* WARING : results are valid if car is horizontal (max 10° on Yaw and Roll) */
    /*****************************************************************************/
    Imu::IMU()
    {
      //init i2c device MPU9250
      acc_gyr_id = wiringPiI2CSetup(MPU9250_ADDRESS);
      // Configure gyroscope range
      wiringPiI2CWriteReg8(acc_gyr_id,27,GYRO_FULL_SCALE_500_DPS);
      // Configure accelerometers range
      wiringPiI2CWriteReg8(acc_gyr_id,28,ACC_FULL_SCALE_8_G);
      // Set by pass mode for the magnetometers
      wiringPiI2CWriteReg8(acc_gyr_id,0x37,0x02);

      //init i2c device magneto
      mag_id = wiringPiI2CSetup(mag_ADDRESS);
      //output magneto 16 bits & continuous mode 100Hz
      wiringPiI2CWriteReg8(mag_id,0x0A,0x16);

      Imu::gyroCalib();
      Imu::magnetoCalib();

      Imu::getAllData();
      Imu::getAllData();
      Imu::lpFiltering();
    }

    void Imu::getAllData(void)
    {
      Imu::getAcceleroData();
      Imu::getGyroData();
      Imu::getmagnetoData();
    }

    /*****************************GET_ACCELERO_DATA*******************************/
    /* Get the raw acceleration on all 3 axis converted to G (M/s/s)             */
    /* Use accelero_offset                                                       */
    /* Update accelero_data                                                      */
    /*****************************************************************************/

    void Imu::getAcceleroData(void)
    {
      uint8_t buf[6];

      // Read accelerometer & Create 16 bits values from 8 bits data

      buf[0] = wiringPiI2CReadReg8(acc_gyr_id,0x3B);
      buf[1] = wiringPiI2CReadReg8(acc_gyr_id,0x3C);

      buf[2] = wiringPiI2CReadReg8(acc_gyr_id,0x3D);
      buf[3] = wiringPiI2CReadReg8(acc_gyr_id,0x3E);

      buf[4] = wiringPiI2CReadReg8(acc_gyr_id,0x3F);
      buf[5] = wiringPiI2CReadReg8(acc_gyr_id,0x40);


      int16_t ax=(buf[0]<<8 | buf[1]);  // sign depends on IMU orientation
      int16_t ay=(buf[2]<<8 | buf[3]);  // sign depends on IMU orientation
      int16_t az=buf[4]<<8 | buf[5];

      //convert it to G
      accelero_data_old.x = accelero_data.x;
      accelero_data_old.y = accelero_data.y;
      accelero_data_old.z = accelero_data.z;

      accelero_data.x = (float)ax * ACCELERO_MUL_8_G + accelero_offset.x;  // real existing bias on X axis
      accelero_data.y = (float)ay * ACCELERO_MUL_8_G + accelero_offset.y;
      accelero_data.z = -((float)az * ACCELERO_MUL_8_G + accelero_offset.z);
    }

    /*****************************GET_GYRO_DATA***********************************/
    /* Get the raw rotation speed on all 3 axis converted to DPS                 */
    /* Use gyro_offset                                                           */
    /* Update gyro_offset                                                        */
    /*****************************************************************************/

    void Imu::getGyroData(void)
    {
    uint8_t buf[6];

      // Read gyroscope & Create 16 bits values from 8 bits data

      buf[0] = wiringPiI2CReadReg8(acc_gyr_id,0x43);
      buf[1] = wiringPiI2CReadReg8(acc_gyr_id,0x44);

      buf[2] = wiringPiI2CReadReg8(acc_gyr_id,0x45);
      buf[3] = wiringPiI2CReadReg8(acc_gyr_id,0x46);

      buf[4] = wiringPiI2CReadReg8(acc_gyr_id,0x47);
      buf[5] = wiringPiI2CReadReg8(acc_gyr_id,0x48);


      int16_t gx=(buf[0]<<8 | buf[1]);  // sign depends on IMU orientation
      int16_t gy=(buf[2]<<8 | buf[3]);  // sign depends on IMU orientation
      int16_t gz=buf[4]<<8 | buf[5];

      //convert it to DPS
      gyro_data_old.x = gyro_data.x;
      gyro_data_old.y = gyro_data.y;
      gyro_data_old.z = gyro_data.z;

      gyro_data.x = -((float)gx * GYRO_MUL_500_DPS + gyro_offset.x) ;
      gyro_data.y = -((float)gy * GYRO_MUL_500_DPS + gyro_offset.y);
      gyro_data.z = -((float)gz * GYRO_MUL_500_DPS + gyro_offset.z);     //-   clockwise convention

    }

    /*****************************GET_magNETO_DATA********************************/
    /* Get the raw magnetic field value on all 3 axis converted to uT            */
    /* Use magneto_offset                                                        */
    /* Update magneto_data structur                                              */
    /*****************************************************************************/

    void Imu::getmagnetoData(void)
    {
      uint8_t ST1;

      // Acess request to magnetometer chip
      do
      {
        ST1 = wiringPiI2CReadReg8(mag_id,0x02);
      }
      while (!(ST1&0x01));

      // Read magnetometer data
      uint8_t mag[7];

      mag[0] = wiringPiI2CReadReg8(mag_id,0x03);
      mag[1] = wiringPiI2CReadReg8(mag_id,0x04);

      mag[2] = wiringPiI2CReadReg8(mag_id,0x05);
      mag[3] = wiringPiI2CReadReg8(mag_id,0x06);

      mag[4] = wiringPiI2CReadReg8(mag_id,0x07);
      mag[5] = wiringPiI2CReadReg8(mag_id,0x08);

      // Read ST2 for continuous mesurement
      mag[6] = wiringPiI2CReadReg8(mag_id,0x09);

      // Create 16 bits values from 8 bits data

      // magnetometer
      int16_t mx=-(mag[1]<<8 | mag[0]);
      int16_t my=-(mag[3]<<8 | mag[2]);
      int16_t mz=-(mag[5]<<8 | mag[4]);

      //convert it to uT (float)
      magneto_data_old.x = magneto_data.x;
      magneto_data_old.y = magneto_data.y;
      magneto_data_old.z = magneto_data.z;

      magneto_data.x = ((float)mx * magneto_offset.gain_x * MAG_MUL_16_BITS - magneto_offset.x);
      magneto_data.y = ((float)my * magneto_offset.gain_y * MAG_MUL_16_BITS - magneto_offset.y);
      magneto_data.z = ((float)mz * magneto_offset.gain_z * MAG_MUL_16_BITS - magneto_offset.z);

    }

    /*****************************AVERAGE_MAGNETO_DATA****************************/
    /* Returns the magneto data average on 5 measurements                        */
    /* Use magneto_offset (in getMagnetoData)                                    */
    /* Update magneto_data                                                       */
    /*****************************************************************************/

    void Imu::averageMagnetoData ()
    {
      float sum_x = 0.0;
      float sum_y = 0.0;
      float sum_z = 0.0;

      // Loop for 5 measurements

      for (int i = 0; i< 5 ; i++)
      {
        // Get magneto_data & build the sum
        getMagnetoData();
        sum_x += magneto_data.x;
        sum_y += magneto_data.y;
        sum_z += magneto_data.z;
      }
      // Build the average value for each axis
      magneto_data.x = sum_x / 5.0;
      magneto_data.y = sum_y / 5.0;
      magneto_data.z = sum_z / 5.0;
    }

    /*****************************GYRO_CALIB**************************************/
    /* Get the offsets of gyroscope                                              */
    /* WARNING : DO NOT MOVE (10 sec)                                            */
    /* Update accelero_offset                                                    */
    /*****************************************************************************/

    void Imu::gyroCalib(void)
    {
      // sgyro_data tmp
      gyro_data G;

      // gyro tmp offsets
      float o_gx = 0.0;
      float o_gy = 0.0;
      float o_gz = 0.0;

      // compute average offsets
      for (int i = 0; i < 500;i++)
      {
        // Get data
        getGyroData(&G); // TO DO
        // compute mean for all offsets (addition)
        o_gx += G.X;
        o_gy += G.Y;
        o_gz += G.Z;
        usleep(10000); // A VERIF
      }

      // compute mean
      o_gx /= 500;
      o_gy /= 500;
      o_gz /= 500;

      gyro_offset.X = o_gx;
      gyro_offset.Y = o_gy;
      gyro_offset.Z = o_gz;
    }

    /*****************************MAGNETO_CALIB***********************************/
    /* To find the magnetometer sensor calib parameters (Offsets and Gains on    */
    /* all 3 axis)                						                                   */
    /* WARNING : inaccurate !! Need manual verifications and adjustments !!      */
    /* Use magneto_offset (in getMagnetoData)                                    */
    /* Update magneto_offset                                                     */
    /*****************************************************************************/

    void Imu::magnetoCalib(void)
    {
      int sample_count = 0;
      int32_t mag_bias[3];  mag_bias[0] = 0;   mag_bias[1] = 0;   mag_bias[2] = 0;
      int32_t mag_scale[3]; mag_scale[0] = 0;  mag_scale[1] = 0;  mag_scale[2] = 0;
      int16_t mag_max[3];   mag_max[0] = 0x80; mag_max[1] = 0x80; mag_max[2] = 0x80;
      int16_t mag_min[3];   mag_min[0] = 0x7F; mag_min[1] = 0x7F; mag_min[2] = 0x7F;

      struct magneto_data M;
      struct accelero_data A;

      sample_count = 2000;                                  // 60 sec de calib
      int i = 0;
      for(int i = 0; i < sample_count; i++)
      {
        getAcceleroData(); // modif accelero_data
        // take in account magnero measuremet only if car horizontal
        if(accelero_data.z < -0.9765) // WUT ????
        {
          getMagnetoData();  // modif magneto_data

          if(magneto_data.x > mag_max[0]) mag_max[0] = magneto_data.x;
          if(magneto_data.x < mag_min[0]) mag_min[0] = magneto_data.x;

          if(magneto_data.y > mag_max[1]) mag_max[1] = magneto_data.y;
          if(magneto_data.y < mag_min[1]) mag_min[1] = magneto_data.y;

          if(magneto_data.z > mag_max[2]) mag_max[2] = magneto_data.z;
          if(magneto_data.z < mag_min[2]) mag_min[2] = magneto_data.z;

          usleep(10000);  // at 100 Hz ODR, new mag data is available every 10 ms
        }
      }
      // Get hard iron correction
      mag_bias[0]  = (mag_max[0] + mag_min[0])/2;  // get average x mag bias in counts
      mag_bias[1]  = (mag_max[1] + mag_min[1])/2;  // get average y mag bias in counts
      mag_bias[2]  = (mag_max[2] + mag_min[2])/2;  // get average z mag bias in counts

      magneto_offset.x = (float) mag_bias[0];  // save mag biases in counts for main program
      magneto_offset.y = (float) mag_bias[1];
      magneto_offset.z = (float) mag_bias[2];

      // Get soft iron correction estimate
      mag_scale[0]  = (mag_max[0] - mag_min[0])/2;  // get average x axis max chord length in counts
      mag_scale[1]  = (mag_max[1] - mag_min[1])/2;  // get average y axis max chord length in counts
      mag_scale[2]  = (mag_max[2] - mag_min[2])/2;  // get average z axis max chord length in counts

      float avg_rad = mag_scale[0] + mag_scale[1] + mag_scale[2];
      avg_rad /= 3.0;

      magneto_offset.gain_x = avg_rad/((float)mag_scale[0]);
      magneto_offset.gain_y = avg_rad/((float)mag_scale[1]);
      magneto_offset.gain_z = avg_rad/((float)mag_scale[2]);

      printf("Mag Calibration done!\n");
    }

    /*****************************LP_FILTERING_IMU**************************************/
    /* Apply a simple Low Pass filter to raw IMU data	                           */
    /* In : Accelero / Gyro / Magneto data to filter & precedent values for these data */
    /* In/Out : filtered Accelero / Gyro / Magneto data                                */
    /***********************************************************************************/

    // low pass at 100 Hz on Accelero / Gyro / Mag raw data

    void Imu::lpFiltering(void)
    {
      // apply Low Pass filters to IMU data
      accelero_data.x = (1-alpha_LP_acc_mag) * accelero_data.x + alpha_LP_acc_mag * accelero_data_old.x;
      accelero_data.y = (1-alpha_LP_acc_mag) * accelero_data.y + alpha_LP_acc_mag * accelero_data_old.y;
      accelero_data.z = (1-alpha_LP_acc_mag) * accelero_data.z + alpha_LP_acc_mag * accelero_data_old.z;

      //gyro_data.x = (1-alpha_LP_gyr) * gyro_data.x + alpha_LP_gyr * gyro_data_old.x;
      //gyro_data.Y = (1-alpha_LP_gyr) * gyro_data.Y + alpha_LP_gyr * gyro_data_old.y;
      //gyro_data.Z = (1-alpha_LP_gyr) * gyro_data.Z + alpha_LP_gyr * gyro_data_old.z;

      magneto_data.x = (1-alpha_LP_acc_mag) * magneto_data.x + alpha_LP_acc_mag * magneto_data_old.x;
      magneto_data.y = (1-alpha_LP_acc_mag) * magneto_data.y + alpha_LP_acc_mag * magneto_data_old.y;
      magneto_data.z = (1-alpha_LP_acc_mag) * magneto_data.z + alpha_LP_acc_mag * magneto_data_old.z;

      // update data (return) & update previous step data
      accelero_data_old = accelero_data;
      gyro_data_old = gyro_data;
      magneto_data_old = magneto_data;
    }

    /*****************************REMOVE_GRAVITY**********************************/
    /* Removes the gravity influence from accelerometer raw data knowing IMU     */
    /* orientation.    							     */
    /* In : accelero data in earth referential				     */
    /* In/Out : Updated accelero data (without gravity)                          */
    /*****************************************************************************/

    /*void remove_gravity (struct Matrix * In, struct Matrix * Out)
    {

      // Substract gravity to acceleration data

      Out->pMatrix[0] = In->pMatrix[0] ;
      Out->pMatrix[1] = In->pMatrix[1] ;
    }*/

    /*****************************CHANGE_REFERENTIAL_TO_MAP********************************************/
    /* Convert IMU referential acceleration to map referential acceleration using rotation matrix     */
    /* Out : Acceleration in map referential                                                          */
    /**************************************************************************************************/

    /*void change_referential_to_map (struct accelero_data A_IMU, struct Matrix * A_map)
    {
      struct Matrix Acc_IMU;
      Acc_IMU.M = 2;
      Acc_IMU.N = 1;
      (Acc_IMU.pMatrix) = (float*)malloc(Acc_IMU.M * Acc_IMU.N * sizeof(float));

      Acc_IMU.pMatrix[0] = A_IMU.X*acc_G_to_SI;
      Acc_IMU.pMatrix[1] = A_IMU.Y*acc_G_to_SI;

      (Rot.pMatrix)[0]  = cos(Yaw*PI/180.0);  (Rot.pMatrix)[1]  = -sin(Yaw*PI/180.0);
      (Rot.pMatrix)[2]  = sin(Yaw*PI/180.0);  (Rot.pMatrix)[3]  =  cos(Yaw*PI/180.0);

      mul_matrixes(&Rot, &Acc_IMU, A_map);
    }*/


    /*****************************UPDATE_U***********************************************/
    /* Fill the input vector for prediction model with accelero data X & Y              */
    /* Out : The acceleration vector  -  U                                              */
    /************************************************************************************/

    /*void update_U (struct Matrix * M)
    {

      //magneto_data_.pMatrix[0] = 0;  magneto_data_.pMatrix[1] = 0;
      change_referential_to_map (ACCDATA_f, M);   // still gravity influence
      //remove_gravity(&U_uncompensated, M);                      // after removing gravity
    }*/
