#ifndef TEMPERATURE_H_
#define TEMPERATURE_H_

#define MCP9808_ADDR 0x18

#include <arduino.h>
#include <Wire.h>
#include <Adafruit_MCP9808.h>

#include "config.h"

void Temperature_Init();
float Temperature_Read();

#endif // TEMPERATURE_H_
