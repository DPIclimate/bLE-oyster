#include "ble.h"
#include "temperature.h"
#include "imu.h"
#include "config.h"

sensors_event_t a, g, t;

void setup() {
	Serial.begin(115200);

	#ifdef DEBUG
		while(!Serial) yield();
	#endif

	///< Setup bluetooth
	Bluetooth_Init();

	///< Setup temperature monitoring (MCP9808)
	Temperature_Init();

	///< Setup IMU (gyro / accelerometer)
	IMU_Init();

}

void loop() {
	Temperature_Read();
	IMU_ReadAll(&a, &g, &t);
	delay(500);
}

