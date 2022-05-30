#include "imu.h"

Adafruit_MPU6050 mpu6050;
IMU_TypeDef imu = {
	.mpu6050 = &mpu6050,
	.frame_sync = MPU6050_FSYNC_OUT_DISABLED,
	.clock_select = MPU6050_INTR_8MHz,
	.accel_range = MPU6050_RANGE_2_G,
	.gyro_range = MPU6050_RANGE_500_DEG,
	.bandwidth = MPU6050_BAND_260_HZ,
	.highpass_filter = MPU6050_HIGHPASS_0_63_HZ,
	.cycle_rate = MPU6050_CYCLE_1_25_HZ, // 10 uA at 1.25 Hz
	.addr = DEFAULT_MPU6050_ADDR,
};

/**
 * Initialise intertial measurement unit (IMU) -> MPU6050
 */
void IMU_Init(){
	#ifdef DEBUG
		Serial.print("Initialising IMU...");
	#endif
	if(!imu.mpu6050->begin()) {
		#ifdef DEBUG
			Serial.println("sensor not found. Stopping.");
		#endif
		//while(1); // Stop execution. TODO watchdog should reset MC.
	}
	#ifdef DEBUG
		Serial.println("done.");
	#endif

	// Initialise internal setup
	imu.mpu6050->setFsyncSampleOutput(imu.frame_sync);
	imu.mpu6050->setClock(imu.clock_select);
	imu.mpu6050->setAccelerometerRange(imu.accel_range);
	imu.mpu6050->setGyroRange(imu.gyro_range);
	imu.mpu6050->setFilterBandwidth(imu.bandwidth);
	imu.mpu6050->setHighPassFilter(imu.highpass_filter);
	imu.mpu6050->setCycleRate(imu.cycle_rate);

	// Disable temperature sensor (save power)
	#ifdef DISABLE_MPU6050_TEMPERATURE
		imu.mpu6050->setTemperatureStandby(true);
	#endif

	// Disable gyroscope
	#ifdef DISABLE_MPU6050_GYROSCOPE
		imu.mpu6050->setGyroStandby(true, true, true);
	#endif

	// Enable motion interrupt
	imu.mpu6050->setMotionDetectionThreshold(1);
	imu.mpu6050->setMotionDetectionDuration(2);
	imu.mpu6050->setInterruptPinLatch(true);	
	imu.mpu6050->setInterruptPinPolarity(true);
	imu.mpu6050->setMotionInterrupt(true);

	/* Put MPU6050 into 10 uA sleep mode with readings every 1.25 Hz */
	// Must not be in sleep mode to enable low power cycle mode below
	imu.mpu6050->enableSleep(false);
	// Enable cycle mode (measurements freq according to Cycle Rate)
	imu.mpu6050->enableCycle(true);
}

/**
 * Read all sensors on IMU. Only really used for debugging.
 *
 * @param a Accelerometer sensor.
 * @param g Gyroscope sensor.
 * @param t Temperature sensor.
 */
void IMU_ReadAll(sensors_event_t *a, sensors_event_t *g, sensors_event_t *t){

	imu.mpu6050->getEvent(a, g, t);
	
	#ifdef DEBUG
		Serial.print("X:\t");
		Serial.print(a->acceleration.x, 1);
		Serial.print("\tY:\t");
		Serial.print(a->acceleration.y, 1);
		Serial.print("\tZ:\t");
		Serial.println(a->acceleration.z, 1);

		#ifndef DISABLE_MPU6050_GYROSCOPE
			Serial.print("\tX:\t");
			Serial.print(g->gyro.x, 1);
			Serial.print("\tY:\t");
			Serial.print(g->gyro.y, 1);
			Serial.print("\tZ:\t");
			Serial.println(g->gyro.z, 1);
		#endif

		#ifndef DISABLE_MPU6050_TEMPERATURE
			Serial.print("\tT:\t");
			Serial.print(t->temperature, 1);
			Serial.print(" \xC2\xB0");
			Serial.println("C");
		#endif
	#endif
}


