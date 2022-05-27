#include "temperature.h"

#ifdef USE_MCP9808
	Adafruit_MCP9808 mcp9080 = Adafruit_MCP9808();
#endif

#ifdef USE_DS18B20
	OneWire oneWire(ONEWIRE_BUS);
	DallasTemperature ds18b20(&oneWire);
#endif

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

	mcp9080.setResolution(3); // 0.0625 °C
}

/**
 * Read temperature from MCP9808 in degrees Celcius.
 *
 * @returns t The temperature in degrees celcius.
 */
float MCP9808_Read() {
	mcp9080.wake();
	float t = mcp9080.readTempC();
	mcp9080.shutdown_wake(1); // Sleep mode until wake

	#ifdef DEBUG
		Serial.print("MCP9808 Temperature = ");
		Serial.print(t, 1);
		Serial.print(" \xC2\xB0");
		Serial.println("C");
	#endif

	return t;
}

/**
 * Initialise DS18B20 temperature sensor.
 *
 * This temperature sensor uses a OneWire interface.
 */
void DS18B20_Init() {
	#ifdef DEBUG
		Serial.print("Initialising DS18B20 temperature sensor...");
	#endif
	ds18b20.begin(); ///< Returns void (no error handling)
	ds18b20.setResolution(DS18B20_RESOLUTION);
	#ifdef DEBUG
		Serial.println("done.");
	#endif
}

/**
 * Read temperature from DS18B20 in degrees Celcius.
 *
 * @returns t The temperature in degrees celcius.
 */
float DS18B20_Read() {

	ds18b20.requestTemperatures();
	float t = ds18b20.getTempCByIndex(0);

	#ifdef DEBUG
		Serial.print("DS18B20 Temperature = ");
		Serial.print(t, 1);
		Serial.print(" \xC2\xB0");
		Serial.println("C");
	#endif

	return t;
}
