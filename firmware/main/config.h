#ifndef CONFIG_H_
#define CONFIG_H_

/**
 * DEBUG mode.
 * Comment out if not needed.
 */
#define DEBUG

/**
 * Use DS18B20 temperature sensor
 * Comment out if not using
 */
#define USE_DS18B20

/**
 * Use MCP9808 temperature sensor
 * Comment out if not using
 */
#define USE_MCP9808

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
