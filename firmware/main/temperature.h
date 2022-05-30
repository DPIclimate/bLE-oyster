#ifndef TEMPERATURE_H_
#define TEMPERATURE_H_

#define MCP9808_ADDR 0x18

#include <arduino.h>
#include <Wire.h>
#include <Adafruit_MCP9808.h>

#include "config.h"

typedef struct {
	Adafruit_MCP9808 *mcp9080;
	bool connected;
} Temperature_TypeDef;

/* MCP9808 temperature sensor */
void MCP9808_Init(); ///< Initialise MCP9808 temperature sensor
float MCP9808_Read(); ///< Read temperature in deg C from MCP9808 

/* Temperature Callbacks */
void Temperature_MeasureCallback(TimerHandle_t xTimerId);

#endif // TEMPERATURE_H_
