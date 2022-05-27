#ifndef TEMPERATURE_H_
#define TEMPERATURE_H_

#define MCP9808_ADDR 0x18

#include <arduino.h>
#include <Wire.h>
#include <Adafruit_MCP9808.h>

#include "config.h"
#ifdef USE_DS18B20
	#define ONEWIRE_BUS 13 ///< Digital pin
	#define DS18B20_RESOLUTION 12 ///< Read resolution in bits
	#include "OneWire.h"
	#include "DallasTemperature.h"
#endif

/* MCP9808 temperature sensor */
void MCP9808_Init(); ///< Initialise MCP9808 temperature sensor
float MCP9808_Read(); ///< Read temperature in deg C from MCP9808 

/* DS18B20 temperature sensor */
void DS18B20_Init(); ///< Initialise OneWire DS18B20 temperature sensor
float DS18B20_Read(); ///< Read temperature in deg C from DS18B20

#endif // TEMPERATURE_H_
