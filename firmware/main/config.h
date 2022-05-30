#ifndef CONFIG_H_
#define CONFIG_H_

/**
 * DEBUG mode.
 * Comment out if not needed.
 */
#define DEBUG

/**
 * Internal pin definitions. Includes:
 * - Blue LED
 * - Push button
 * - RGB LED clock line
 * - RGB LED data line 
 */
#define INTERNAL_BLUE_LED 		3 ///< Blue onboard lED
#define INTERNAL_PUSH_BTN 		4 ///< Onboard push button
#define INTERNAL_RGB_LED_CLK 	6 ///< RGB LED clock line
#define INTERNAL_RGB_LED_DATA 	8 ///< RGB LED data line

/**
 * IMU interrupt pin. 
 * This is initialised in imu.cpp and checked in ble.cpp
 */
#define IMU_IRQ_PIN 			12 ///< Digital interrupt pin

/**
 * DISABLE Gyroscope in MPU6050.
 * Comment out to enable. WARNING! Miniumum operatiing current of 3.6 mA
 */
#define DISABLE_MPU6050_GYROSCOPE

/**
 * DISABLE temperature sensor in MPU6050.
 * Comment out to enable.
 */
#define DISABLE_MPU6050_TEMPERATURE


#endif // CONFIG_H_
