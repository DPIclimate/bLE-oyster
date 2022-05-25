#include "temperature.h"

Adafruit_MCP9808 temp_sensor = Adafruit_MCP9808();

/**
 * Initialise MCP9808 temperature sensor.
 * Default address for the I2C device is 0x18
 * @returns Temperature_StatusTypeDef Error codes for temperature sensor.
 */
Temperature_StatusTypeDef TemperatureInit() {
	if(!temp_sensor.begin(MCP9808_ADDR)){
		#ifdef DEBUG
			Serial.println("Temperature sensor unavailable.");
		#endif
		return TEMP_ERROR;
	}
	temp_sensor.setResolution(3); // 0.0625 °C
	return TEMP_OK;
}

/**
 * Read temperature from MCP9808 in degrees Celcius.
 * @returns t The temperature in degrees celcius.
 */
float TemperatureRead() {
	temp_sensor.wake();
	float t = temp_sensor.readTempC();
	temp_sensor.shutdown_wake(1); // Sleep mode until wake

	#ifdef DEBUG
		Serial.print("MCP9808 Temperature = ");
		Serial.print(t, 1);
		Serial.println(" °C");
	#endif

	return t;
}
