#include <bluefruit.h>

#include "ble.h"
#include "temperature.h"
#include "config.h"

BLEDfu bledfu;
BLEUart bleuart;
BLEDis bledis;

Bluetooth_TypeDef _bt = {
	.service = &bledfu,
	.uart = &bleuart,
	.device_info = &bledis,
	.num_connections = 1,
	.tx_power = 4, // dB
};

void setup() {
	Serial.begin(115200);
	#ifdef DEBUG
		while(!Serial);
	#endif // DEBUG

	pinMode(LED_BUILTIN, OUTPUT);

	BluetoothInit(&_bt); // Setup bluetooth coms

	// Setup temperature monitoring (MCP9808)
	if(TemperatureInit() == TEMP_OK) {
		#ifdef DEBUG
			Serial.println("MCP9808 temperature monitor initialised.");
		#endif
	}

}

void loop() {
	digitalWrite(LED_BUILTIN, HIGH);
	delay(1000);
	TemperatureRead();
	digitalWrite(LED_BUILTIN, LOW);
	delay(1000);
}
