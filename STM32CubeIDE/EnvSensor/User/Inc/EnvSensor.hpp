/*
 * EnvSensor.hpp
 *
 *  Created on: Dec 20, 2020
 *      Author: Chipotle
 */

#ifndef INC_ENVSENSOR_HPP_
#define INC_ENVSENSOR_HPP_

#include "stm32l4xx_hal.h"

#define LED_ON  	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET)
#define LED_OFF 	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET)
#define LED_TOGGLE	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin)

#ifdef __cplusplus
extern "C" {
#endif

extern int8_t EnvSensor_Init();

extern void EnvSensor_Loop();

extern void EnvSensor_Switch1();
extern void EnvSensor_Switch2();
extern void EnvSensor_Switch3();
extern void EnvSensor_Switch4();

#ifdef __cplusplus
}
#endif

#endif /* INC_ENVSENSOR_HPP_ */
