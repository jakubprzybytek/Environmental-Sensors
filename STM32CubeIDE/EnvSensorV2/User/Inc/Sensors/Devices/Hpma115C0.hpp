#ifndef INC_SENSORS_HPMA115C0_HPP_
#define INC_SENSORS_HPMA115C0_HPP_

#include <stm32l4xx_hal.h>

#define HPMA115C0_MAX_DELAY		100

class Hpma115C0 {

private:
	//UART_HandleTypeDef &huart;

	uint8_t buffer[10];

public:
	//Hpma115C0(UART_HandleTypeDef &huart): huart(huart) {}

	HAL_StatusTypeDef init();

};

#endif
