#include "temperature.h"

Adafruit_MCP9808 mcp9080 = Adafruit_MCP9808();
bool temp_connected = false;

/**
 * Initialise MCP9808 temperature sensor.
 *
 * Default address for this I2C device is 0x18.
 */
void MCP9808_Init() {
	#ifdef DEBUG
		Serial.print("Initialising MCP9808 temperature sensor...");
	#endif
	if (!mcp9080.begin(MCP9808_ADDR)) {
		#ifdef DEBUG
			Serial.println("sensor not found. Stopping.");
		#endif
		while (1); // Stop execution. TODO should trigger watchdog.
	}
	#ifdef DEBUG
		Serial.println("done.");
	#endif

	temp_connected = true;

	mcp9080.setResolution(3); // 0.0625 °C
}

/**
 * Read temperature from MCP9808 in degrees Celcius.
 *
 * @returns t The temperature in degrees celcius.
 */
float MCP9808_Read() {
	if(!temp_connected) {
		#ifdef DEBUG
			Serial.print("MCP9808 not found. Exiting.");
		#endif
		return 0.0;
	}

	mcp9080.wake();
	float t = mcp9080.readTempC();
	mcp9080.shutdown_wake(1); // Sleep mode until wake

	#ifdef DEBUG
		Serial.print("MCP9808 Temperature = ");
		Serial.print(t, 2);
		Serial.print(" \xC2\xB0");
		Serial.println("C");
	#endif

	return t;
}

/**
 * Callback to measure temperature.
 */
void Temperature_MeasureCallback(TimerHandle_t xTimer){
	(void) xTimer;
	
	#ifdef DEBUG
		Serial.println("Temperature callback triggered.");
	#endif
	if(!temp_connected){
		#ifdef DEBUG
			Serial.println("MCP9808 not found. Exiting callback.");
		#endif
		return;
	}

	MCP9808_Read();
}
