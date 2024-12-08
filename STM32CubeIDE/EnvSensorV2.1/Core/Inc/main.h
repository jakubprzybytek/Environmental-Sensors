/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#define LED_4_Pin GPIO_PIN_0
#define LED_4_GPIO_Port GPIOC
#define LED_3_Pin GPIO_PIN_1
#define LED_3_GPIO_Port GPIOC
#define LED_2_Pin GPIO_PIN_2
#define LED_2_GPIO_Port GPIOC
#define LED_1_Pin GPIO_PIN_3
#define LED_1_GPIO_Port GPIOC
#define BATTERY_MEASURE_INPUT_Pin GPIO_PIN_0
#define BATTERY_MEASURE_INPUT_GPIO_Port GPIOA
#define E_INK_SELECT_Pin GPIO_PIN_4
#define E_INK_SELECT_GPIO_Port GPIOC
#define E_INK_DC_Pin GPIO_PIN_5
#define E_INK_DC_GPIO_Port GPIOC
#define E_INK_RESET_Pin GPIO_PIN_0
#define E_INK_RESET_GPIO_Port GPIOB
#define E_INK_BUSY_Pin GPIO_PIN_1
#define E_INK_BUSY_GPIO_Port GPIOB
#define E_INK_BUSY_EXTI_IRQn EXTI1_IRQn
#define POWER_5V_ENABLE_Pin GPIO_PIN_2
#define POWER_5V_ENABLE_GPIO_Port GPIOB
#define SWITCH_1_Pin GPIO_PIN_12
#define SWITCH_1_GPIO_Port GPIOB
#define SWITCH_1_EXTI_IRQn EXTI15_10_IRQn
#define SWITCH_2_Pin GPIO_PIN_13
#define SWITCH_2_GPIO_Port GPIOB
#define SWITCH_2_EXTI_IRQn EXTI15_10_IRQn
#define SWITCH_3_Pin GPIO_PIN_14
#define SWITCH_3_GPIO_Port GPIOB
#define SWITCH_3_EXTI_IRQn EXTI15_10_IRQn
#define SWITCH_4_Pin GPIO_PIN_15
#define SWITCH_4_GPIO_Port GPIOB
#define SWITCH_4_EXTI_IRQn EXTI15_10_IRQn
#define BATTERY_MEASURE_ENABLE_Pin GPIO_PIN_6
#define BATTERY_MEASURE_ENABLE_GPIO_Port GPIOC
#define SCD30_READY_Pin GPIO_PIN_8
#define SCD30_READY_GPIO_Port GPIOA
#define SDIO_POWER_ENABLE_Pin GPIO_PIN_11
#define SDIO_POWER_ENABLE_GPIO_Port GPIOA
#define SDIO_DETECT_Pin GPIO_PIN_12
#define SDIO_DETECT_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
