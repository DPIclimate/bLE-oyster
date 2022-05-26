#ifndef IMU_H_ 
#define IMU_H_ 

#include <arduino.h>
#include <Adafruit_MPU6050.h>
#include <Wire.h>

#include "config.h"

#define DEFAULT_MPU6050_ADDR 0x68

typedef struct {
	Adafruit_MPU6050 *mpu6050;
	mpu6050_fsync_out_t frame_sync;
	mpu6050_clock_select_t clock_select;
	mpu6050_accel_range_t accel_range;
	mpu6050_gyro_range_t gyro_range;
	mpu6050_bandwidth_t bandwidth;
	mpu6050_highpass_t highpass_filter;
	mpu6050_cycle_rate_t cycle_rate;
	uint8_t addr;
} IMU_TypeDef;

void IMU_Init();
void IMU_ReadAll(sensors_event_t *a, sensors_event_t *g, sensors_event_t *t);

#endif // IMU_H_
