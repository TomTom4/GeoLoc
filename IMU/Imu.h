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
	float x, y, z;
}AcceleroData;

typedef struct _GyroData
{
	float x, y, z;
}GyroData;

typedef struct _MagnetoData
{
	float x, y, z;
  float gain_x, gain_y, gain_z;
}MagnetoData;

#endif
