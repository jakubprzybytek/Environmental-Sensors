#ifndef INC_SENSORS_HPMA115C0_HPP_
#define INC_SENSORS_HPMA115C0_HPP_

#include <stm32l4xx_hal.h>

#include <main.h>

#define POWER_5V_ENABLE HAL_GPIO_WritePin(POWER_5V_ENABLE_GPIO_Port, POWER_5V_ENABLE_Pin, GPIO_PIN_SET);
#define POWER_5V_DISABLE HAL_GPIO_WritePin(POWER_5V_ENABLE_GPIO_Port, POWER_5V_ENABLE_Pin, GPIO_PIN_RESET);

#define HPMA115C0_HEAD									0x68
#define HPMA115C0_COMMAND_START_PARTICLE_MEASUREMENT	0x01
#define HPMA115C0_COMMAND_STOP_PARTICLE_MEASUREMENT		0x02
#define HPMA115C0_COMMAND_STOP_AUTO_SEND				0x20

#define HPMA115C0_SUCCESS								0xa5

#define HPMA115C0_MAX_DELAY								200

class Hpma115C0 {

private:
	UART_HandleTypeDef &huart;

	uint8_t buffer[16];

	HAL_StatusTypeDef sendCommand(uint8_t command);
	uint8_t checkSum(uint8_t *data, uint8_t length);

public:
	Hpma115C0(UART_HandleTypeDef &huart): huart(huart) {}

	HAL_StatusTypeDef init();
	HAL_StatusTypeDef deinit();

	HAL_StatusTypeDef startMeasurements();
	HAL_StatusTypeDef stopMeasurements();
	HAL_StatusTypeDef stopAutoSend();

	HAL_StatusTypeDef readMeasurements(uint16_t *pm1, uint16_t *pm2_5, uint16_t *pm4, uint16_t *pm10);
};

#endif
