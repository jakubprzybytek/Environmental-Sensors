/*
 * EnvSensor.hpp
 *
 *  Created on: Dec 20, 2020
 *      Author: Chipotle
 */

#ifndef INC_ENVSENSORV2_HPP_
#define INC_ENVSENSORV2_HPP_

#include "stm32l4xx_hal.h"

#include "main.h"

#include "EnvSensorCommon.hpp"

#ifdef __cplusplus
extern "C" {
#endif

extern void EnvSensorV2_Init();

void switch1Pressed();
void switch2Pressed();
void switch3Pressed();
void switch4Pressed();

#ifdef __cplusplus
}
#endif

#endif /* INC_ENVSENSORV2_HPP_ */
