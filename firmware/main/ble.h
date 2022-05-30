#ifndef BLE_H_
#define BLE_H_

#define MAX_PEER_NAME_SIZE 32
#define MAX_RX_SIZE 20

#include <arduino.h>
#include <bluefruit.h>

#include "config.h"
#include "temperature.h"

/**
 * Bluetooth handler.
 *
 * Allows for the setup of bluetooth specific services. 
 * - OTA firmware updates
 * - UART over bluetooth
 * - Device information
 * - Battery status
 *
 * Also provided are options for TX power (may need to be adjusted) and 
 * the maxiumum number for concurrent connections over bluetooth.
 */
typedef struct {
	BLEDfu *service; ///< Over the air firmware update
	BLEUart *uart; ///< UART over bluetooth
	BLEDis *device_info; ///< Device information 
	BLEBas *battery_status; ///< Battery status
	uint8_t num_connections; ///< Number of concurrent connections
	/* Valid TX power settings: -40dBm, -20dBm, -16dBm, -12dBm, -8dBm, -4dBm, 
	 0dBm, +2dBm, +3dBm, +4dBm, +5dBm, +6dBm, +7dBm and +8dBm.*/
	int8_t tx_power; ///< Transmission power
	uint16_t connection_timeout; ///< Timeout in seconds
} Bluetooth_TypeDef;

void Bluetooth_Init();
void Bluetooth_ConnectCallback(uint16_t conn_handle);
void Bluetooth_DisconnectCallback(uint16_t conn_handle, uint8_t reason);
void Bluetooth_RxCallback(uint16_t conn_handle);
void Bluetooth_StartAdvertising();
void Bluetooth_StopAdvCallback();
void Bluetooth_Sleep();
void Bluetooth_Wakeup();

#endif // BLE_H_
