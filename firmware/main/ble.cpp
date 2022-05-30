#include "ble.h"

BLEDfu bledfu; ///< Over the air updates
BLEUart bleuart; ///< Bluetooth UART
BLEDis bledis; ///< Device information
BLEBas blebas; ///< Device battery status

Bluetooth_TypeDef bt = {
	.service = &bledfu,
	.uart = &bleuart,
	.device_info = &bledis,
	.battery_status = &blebas,
	.num_connections = 1,
	.tx_power = 4, // dB
	.connection_timeout = 30, // seconds
};

/**
 * Initialise bluetooth communicaitons.
 *
 * Setup over the air (OTA) firmware updates, bluetooth UART, device
 * information (name, manufactuer etc.) and battery status. Also adjustable
 * here is the TX communications power and the max number for concurrent
 * bluetooth connections.
 */
void Bluetooth_Init(){

	Bluefruit.autoConnLed(true);
	Bluefruit.configPrphBandwidth(BANDWIDTH_MAX);

	// Max concurrent connections. Default 1
	Bluefruit.begin(bt.num_connections, 1);
	Bluefruit.setName("BLE Oyster");

	// Transmit power. Default 4 dB
	Bluefruit.setTxPower(bt.tx_power);

	// Connection callbacks for mobile devices
	Bluefruit.Periph.setConnectCallback(Bluetooth_ConnectCallback);
	Bluefruit.Periph.setDisconnectCallback(Bluetooth_DisconnectCallback);

	// Start OTA updates
	bt.service->begin();

	// Set device information
	bt.device_info->setManufacturer("Department of Primary Industries");
	bt.device_info->setModel("BLE Oyster");
	bt.device_info->begin();

	// BLE UART setup
	bt.uart->begin();
	bt.uart->setRxCallback(Bluetooth_RxCallback);

	// Setup battery information
	bt.battery_status->begin();
	bt.battery_status->write(100);

	Bluetooth_StartAdvertising(); // Start advertising 
}

/**
 * Start advertising bluetooth connection for external devices to
 * connect to.
 */
void Bluetooth_StartAdvertising() {
	Bluefruit.Advertising
		.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
	Bluefruit.Advertising.addTxPower();

	// Include UUID
	Bluefruit.Advertising.addService(*bt.uart);
	Bluefruit.Advertising.addName(); ///< Include name in packet

	// Set callback when advertising stops
	Bluefruit.Advertising.setStopCallback(Bluetooth_StopAdvCallback);
	
	// Defult advertising parameters
	Bluefruit.Advertising.restartOnDisconnect(true);
	Bluefruit.Advertising.setInterval(32, 244); 
	Bluefruit.Advertising.setFastTimeout(30); 

	// Start advertising with timeout
	Bluefruit.Advertising.start(bt.connection_timeout); 
}

/**
 * Debugging callback to notify when bluetooth advertising has timed out.
 */
void Bluetooth_StopAdvCallback(){
	#ifdef DEBUG
		Serial.println("BLE advertising has timed out. Stopping service.");
	#endif
}

/**
 * Callback event to handle connections over bluetooth.
 *
 * @param conn_handle Bluetooth connection handler.
 */
void Bluetooth_ConnectCallback(uint16_t conn_handle) {
	BLEConnection *connection = Bluefruit.Connection(conn_handle);
	#ifdef DEBUG
		char peer_name[MAX_PEER_NAME_SIZE] = {0};
		connection->getPeerName(peer_name, sizeof(peer_name));
		Serial.print("[Peripheral]: Connected to ---> ");
		Serial.println(peer_name);
	#endif
}

/**
 * Callback event to handle bluetooth disconnections.
 *
 * @param conn_handle Bluetooth connection handler.
 * @param reason Represents disconnection type.
 */
void Bluetooth_DisconnectCallback(uint16_t conn_handle, uint8_t reason) {
	(void) conn_handle;
	#ifdef DEBUG
		Serial.print("[Peripheral]: Disconnected. Reason = ");
		Serial.println(reason);
	#endif
	(void) reason;
}

/**
 * Callback event for handling messages from bluetooth devices.
 *
 * @param conn_handler BLE connection handler.
 */
void Bluetooth_RxCallback(uint16_t conn_handle) {
	(void) conn_handle;
	#ifdef DEBUG
		char str[MAX_RX_SIZE + 1] = {0};
		bt.uart->read(str, MAX_RX_SIZE);
		Serial.print("[Periph]: RX ---> ");
		Serial.print(str);
	#endif
}

void Bluetooth_Sleep(){
	// TODO place the device in sleep mode
	if(Bluefruit.connected(0)) {
		// Don't sleep if device connected	
		return;
	}
	#ifdef DEBUG
		Serial.println("Bluetooth sleep.");
	#endif
}

void Bluetooth_Wakeup(){
	#ifdef DEBUG
		Serial.println("Wakeup bluetooth.");
	#endif
	
	if(!Bluefruit.connected() && !Bluefruit.Advertising.isRunning()){
		#ifdef DEBUG
			Serial.println("Restarting BLE advertising.");
		#endif
		Bluefruit.Advertising.start(bt.connection_timeout); 
	} else {
		#ifdef DEBUG
			Serial.println("BLE advertising already running. Skipping.");
		#endif
	}
}

