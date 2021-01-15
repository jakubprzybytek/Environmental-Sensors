/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define READOUT_RETRY_INTERVAL 0.5
#define DISPLAY_REFRESH_INTERVAL 5 * 60
#define MEASUREMENT_INTERVAL 10
#define E_INK_Select_Pin GPIO_PIN_3
#define E_INK_Select_GPIO_Port GPIOA
#define E_INK_DC_Pin GPIO_PIN_4
#define E_INK_DC_GPIO_Port GPIOA
#define E_INK_Reset_Pin GPIO_PIN_5
#define E_INK_Reset_GPIO_Port GPIOA
#define E_INK_Busy_Pin GPIO_PIN_6
#define E_INK_Busy_GPIO_Port GPIOA
#define E_INK_Busy_EXTI_IRQn EXTI9_5_IRQn
#define Switch1_Pin GPIO_PIN_7
#define Switch1_GPIO_Port GPIOA
#define Switch1_EXTI_IRQn EXTI9_5_IRQn
#define Switch2_Pin GPIO_PIN_0
#define Switch2_GPIO_Port GPIOB
#define Switch2_EXTI_IRQn EXTI0_IRQn
#define Switch3_Pin GPIO_PIN_1
#define Switch3_GPIO_Port GPIOB
#define Switch3_EXTI_IRQn EXTI1_IRQn
#define Switch4_Pin GPIO_PIN_2
#define Switch4_GPIO_Port GPIOB
#define Switch4_EXTI_IRQn EXTI2_IRQn
#define LED_Pin GPIO_PIN_11
#define LED_GPIO_Port GPIOB
#define Buzzer_Pin GPIO_PIN_12
#define Buzzer_GPIO_Port GPIOB
#define SD_Select_Pin GPIO_PIN_8
#define SD_Select_GPIO_Port GPIOA
#define SCD30_Ready_Pin GPIO_PIN_11
#define SCD30_Ready_GPIO_Port GPIOA
#define AuxPowerEnable_Pin GPIO_PIN_12
#define AuxPowerEnable_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
