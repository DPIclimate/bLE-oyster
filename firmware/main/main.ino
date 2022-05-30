#include "ble.h"
#include "temperature.h"
#include "imu.h"
#include "config.h"

void setup() {
	#ifdef DEBUG
		Serial.begin(115200);
		while(!Serial) yield();
	#endif

	///< Setup bluetooth
	Bluetooth_Init();

	///< Setup temperature monitoring (MCP9808)
	MCP9808_Init();

	///< Setup IMU (gyro / accelerometer)
	IMU_Init();

	// Setup the IMU interrupt pin
	// Attach interrupt to wakeup bluetooth on HIGH -> LOW transition
	// ISR_DEFERRED is needed if calls are made to Bluefruit and subseqently
	// FreeRTOS (timing issue)
	pinMode(IMU_IRQ_PIN, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(IMU_IRQ_PIN), Bluetooth_Wakeup, 
			ISR_DEFERRED | FALLING);

	// Setup measure temperature callback
	// pdMS_TO_TICKS max size handles uin32_t
	// Requires suspendLoop() in main.ino
	TimerHandle_t mt = xTimerCreate("Measure Temperature", 
			pdMS_TO_TICKS(1000*60*2), pdTRUE, (void *)0, 
			Temperature_MeasureCallback);
	xTimerStart(mt, 2000);

	// Loop function not needed so disable to save power
	suspendLoop();
}

void loop() {}

