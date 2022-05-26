#include "temperature.h"

Adafruit_MCP9808 temp_sensor = Adafruit_MCP9808();

/**
 * Initialise MCP9808 temperature sensor.
 * Default address for the I2C device is 0x18
 * @returns Temperature_StatusTypeDef Error codes for temperature sensor.
 */
void Temperature_Init() {
	#ifdef DEBUG
		Serial.print("Initialising temperature sensor...");
	#endif
	if (!temp_sensor.begin(MCP9808_ADDR)) {
		#ifdef DEBUG
			Serial.println("sensor not found. Stopping.");
		#endif
		while (1); // Stop execution. TODO should trigger watchdog.
	}
	#ifdef DEBUG
		Serial.println("done.");
	#endif

	temp_sensor.setResolution(3); // 0.0625 °C
}

/**
 * Read temperature from MCP9808 in degrees Celcius.
 * @returns t The temperature in degrees celcius.
 */
float Temperature_Read() {
	temp_sensor.wake();
	float t = temp_sensor.readTempC();
	temp_sensor.shutdown_wake(1); // Sleep mode until wake


	#ifdef DEBUG
		Serial.print("MCP9808 Temperature = ");
		Serial.print(t, 1);
		Serial.print(" \xC2\xB0");
		Serial.println("C");
	#endif

	return t;
}
