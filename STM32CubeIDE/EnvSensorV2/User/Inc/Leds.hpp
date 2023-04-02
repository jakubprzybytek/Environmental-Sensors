/*
 * Leds.hpp
 *
 *  Created on: 2 Apr 2023
 *      Author: jakub.przybytek
 */

#ifndef INC_LEDS_HPP_
#define INC_LEDS_HPP_

#define CPU_LED_Port LED_1_GPIO_Port
#define CPU_LED_Pin LED_1_Pin
#define CPU_LED_On() HAL_GPIO_WritePin(CPU_LED_Port, CPU_LED_Pin, GPIO_PIN_SET)
#define CPU_LED_Off() HAL_GPIO_WritePin(CPU_LED_Port, CPU_LED_Pin, GPIO_PIN_RESET)

#define DISPLAY_LED_Port LED_3_GPIO_Port
#define DISPLAY_LED_Pin LED_3_Pin
#define DISPLAY_LED_On() HAL_GPIO_WritePin(DISPLAY_LED_Port, DISPLAY_LED_Pin, GPIO_PIN_SET)
#define DISPLAY_LED_Off() HAL_GPIO_WritePin(DISPLAY_LED_Port, DISPLAY_LED_Pin, GPIO_PIN_RESET)

#endif /* INC_LEDS_HPP_ */
