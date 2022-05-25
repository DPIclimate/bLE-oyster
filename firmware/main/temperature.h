#ifndef TEMPERATURE_H_
#define TEMPERATURE_H_

#define MCP9808_ADDR 0x18

#include <arduino.h>
#include <Wire.h>
#include <Adafruit_MCP9808.h>

#include "config.h"

typedef enum {
	TEMP_OK = 		0x00,
	TEMP_ERROR = 	0x01,
} Temperature_StatusTypeDef;

Temperature_StatusTypeDef TemperatureInit();
float TemperatureRead();

#endif // TEMPERATURE_H_
