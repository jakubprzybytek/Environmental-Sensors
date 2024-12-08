/*
 * Hpma115C0Config.hpp
 *
 *  Created on: May 20, 2023
 *      Author: jakub.przybytek
 */

#ifndef INC_SENSORS_DEVICES_HPMA115C0CONFIG_HPP_
#define INC_SENSORS_DEVICES_HPMA115C0CONFIG_HPP_

extern osThreadId_t particlesSensorThreadHandle;

#define UART_RECEIVED_THREAD_FLAG 0x02

#define UART_WAIT() osThreadFlagsWait(UART_RECEIVED_THREAD_FLAG, osFlagsWaitAll, 2000 / portTICK_RATE_MS)

#define UART_NOTIFY() osThreadFlagsSet(particlesSensorThreadHandle, UART_RECEIVED_THREAD_FLAG);

#endif /* INC_SENSORS_DEVICES_HPMA115C0CONFIG_HPP_ */
