#ifndef INC_ENVSENSORV2_1_HPP_
#define INC_ENVSENSORV2_1_HPP_

#include "stm32l4xx_hal.h"

#include "main.h"


#ifdef __cplusplus
extern "C" {
#endif

extern void EnvSensorV2_1_Init();

void mainStateThreadStart();
void mainStateThread(void *pvParameters);

void switch1Pressed();
void switch2Pressed();
void switch3Pressed();
void switch4Pressed();

#ifdef __cplusplus
}
#endif

#endif /* INC_ENVSENSORV2_HPP_ */
