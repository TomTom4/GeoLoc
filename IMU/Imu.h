#ifndef _IMU_H
#define _IMU_H

/**************************************************/
/*                    ALIAS                       */
/**************************************************/
#define    MPU9250_ADDRESS            0x68
#define    MAG_ADDRESS                0x0C

#define    GYRO_FULL_SCALE_250_DPS    0x00
#define    GYRO_FULL_SCALE_500_DPS    0x08
#define    GYRO_FULL_SCALE_1000_DPS   0x10
#define    GYRO_FULL_SCALE_2000_DPS   0x18

#define    ACC_FULL_SCALE_2_G        0x00
#define    ACC_FULL_SCALE_4_G        0x08
#define    ACC_FULL_SCALE_8_G        0x10
#define    ACC_FULL_SCALE_16_G       0x18

#define    ACCELERO_GYRO_ID          0x03
#define    MAGNETO_ID                0x05

#define    MAG_MUL_16_BITS           0.15 		// (0.15uT/LSB)
#define    MAG_MUL_14_BITS           0.6

#define    GYRO_MUL_250_DPS          2*250.0/32767.0
#define    GYRO_MUL_500_DPS          2*500.0/32768.0
#define    GYRO_MUL_1000_DPS	       2*1000.0/32767.0
#define    GYRO_MUL_2000_DPS         2*2000.0/32767.0

#define    ACCELERO_MUL_2_G          2.0/32767.0
#define    ACCELERO_MUL_4_G          4.0/32767.0
#define    ACCELERO_MUL_8_G          8.0/32767.0
#define    ACCELERO_MUL_16_G         16.0/32767.0

#define    ACCELERO_OFF_X            -0.035
#define    ACCELERO_OFF_Y            -0.02
#define    ACCELERO_OFF_Z            0.02

#define    CUTOFF_FREQ_GYR           550.0              // 500 Hz(500DPS MAX) - for HF filters
#define    CUTOFF_FREQ_ACC_MAG       100.0              // 100 Hz(car fastest mecanical dynmics) - for HF filters

#define    GRAVITY                   -1         	// in G
#define    ACC_G_TO_SI               9.81


// IMU Structures

typedef struct _AcceleroData
{
	float x;
    float y;
    float z;
} AcceleroData;

typedef struct _GyroData
{
    float x;
    float y;
    float z;
} GyroData;

typedef struct _MagnetoData
{
    float x;
    float y;
    float z;
	float gain_x;
    float gain_y;
    float gain_z;
} MagnetoData;

class Imu
{
  private:
    int acc_gyr_id; // Identifiant Gyroscope
    int mag_id; // Identifiant magnetometer

    AcceleroData accelero_offset; // Accelerometer offset structure
    AcceleroData accelero_data; // Accelerometer data structure
    AcceleroData accelero_data_old; // Accelerometer data structure


    GyroData gyro_offset; // Gyroscope offser structure TOUT A 0 ????
    GyroData gyro_data; // Gyroscope data structure
    GyroData gyro_data_old; // Gyroscope data structure

    MagnetoData magneto_offset; // magnetometer offset structure
    MagnetoData magneto_data; // magnetometer data structure
    MagnetoData magneto_data_old; // magnetometer data structure

public:


    /***********************************SETUP*************************************/
    /* Init all IMU sensors                                                      */
    /* WARING : results are valid if car is horizontal (max 10° on Yaw and Roll) */
    /*****************************************************************************/
    Imu();

    void getAllData(void);

    /*****************************GET_ACCELERO_DATA*******************************/
    /* Get the raw acceleration on all 3 axis converted to G (M/s/s)             */
    /* Use accelero_offset                                                       */
    /* Update accelero_data                                                      */
    /*****************************************************************************/

    void getAcceleroData(void);

    /*****************************GET_GYRO_DATA***********************************/
    /* Get the raw rotation speed on all 3 axis converted to DPS                 */
    /* Use gyro_offset                                                           */
    /* Update gyro_offset                                                        */
    /*****************************************************************************/

    void getGyroData(void);

    /*****************************GET_magNETO_DATA********************************/
    /* Get the raw magnetic field value on all 3 axis converted to uT            */
    /* Use magneto_offset                                                        */
    /* Update magneto_data structur                                              */
    /*****************************************************************************/

    void getmagnetoData(void);

    /*****************************AVERAGE_MAGNETO_DATA****************************/
    /* Returns the magneto data average on 5 measurements                        */
    /* Use magneto_offset (in getMagnetoData)                                    */
    /* Update magneto_data                                                       */
    /*****************************************************************************/

    void averageMagnetoData ();

    /*****************************GYRO_CALIB**************************************/
    /* Get the offsets of gyroscope                                              */
    /* WARNING : DO NOT MOVE (10 sec)                                            */
    /* Update accelero_offset                                                    */
    /*****************************************************************************/

    void gyroCalib(void);

    /*****************************MAGNETO_CALIB***********************************/
    /* To find the magnetometer sensor calib parameters (Offsets and Gains on    */
    /* all 3 axis)                						                                   */
    /* WARNING : inaccurate !! Need manual verifications and adjustments !!      */
    /* Use magneto_offset (in getMagnetoData)                                    */
    /* Update magneto_offset                                                     */
    /*****************************************************************************/

    void magnetoCalib(void);

    /*****************************LP_FILTERING_IMU**************************************/
    /* Apply a simple Low Pass filter to raw IMU data	                           */
    /* In : Accelero / Gyro / Magneto data to filter & precedent values for these data */
    /* In/Out : filtered Accelero / Gyro / Magneto data                                */
    /***********************************************************************************/

    // low pass at 100 Hz on Accelero / Gyro / Mag raw data

    void lpFiltering(void);

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

    //void update_U (struct Matrix * M);

};





#endif
