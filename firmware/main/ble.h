#ifndef BLE_H_
#define BLE_H_

#define MAX_PEER_NAME_SIZE 32
#define MAX_RX_SIZE 20

#include <arduino.h>
#include <bluefruit.h>

#include "config.h"

typedef struct {
	BLEDfu *service; ///< Over the air firmware update
	BLEUart *uart; ///< UART over bluetooth
	BLEDis *device_info; ///< Device information 
	uint8_t num_connections; ///< Number of concurrent connections
	// Valid TX power settings: -40dBm, -20dBm, -16dBm, -12dBm, -8dBm, -4dBm, 
	// 0dBm, +2dBm, +3dBm, +4dBm, +5dBm, +6dBm, +7dBm and +8dBm.	
	int8_t tx_power;
} Bluetooth_TypeDef;

typedef enum {
	BT_OK = 	0x00,
	BT_ERROR = 	0x01
} Bluetooth_StatusTypeDef;

void BluetoothInit(Bluetooth_TypeDef * _bt);
void BluetoothConnectCallback(uint16_t conn_handle);
void BluetoothDisconnectCallback(uint16_t conn_handle, uint8_t reason);
void BluetoothRxCallback(uint16_t conn_handle);
void BluetoothStartAdvertising();

#endif // BLE_H_