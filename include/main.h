/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "stm32f4xx_hal.h"

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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED1_Pin GPIO_PIN_13
#define LED1_GPIO_Port GPIOC
#define servo1_Pin GPIO_PIN_0
#define servo1_GPIO_Port GPIOA
#define servo2_Pin GPIO_PIN_1
#define servo2_GPIO_Port GPIOA
#define servo3_Pin GPIO_PIN_2
#define servo3_GPIO_Port GPIOA
#define servo4_Pin GPIO_PIN_3
#define servo4_GPIO_Port GPIOA
#define M1_STEP_Pin GPIO_PIN_4
#define M1_STEP_GPIO_Port GPIOA
#define M1_DIR_Pin GPIO_PIN_5
#define M1_DIR_GPIO_Port GPIOA
#define M1_SLP_Pin GPIO_PIN_6
#define M1_SLP_GPIO_Port GPIOA
#define M2_STEP_Pin GPIO_PIN_7
#define M2_STEP_GPIO_Port GPIOA
#define M2_DIR_Pin GPIO_PIN_0
#define M2_DIR_GPIO_Port GPIOB
#define M2_SLP_Pin GPIO_PIN_1
#define M2_SLP_GPIO_Port GPIOB
#define LED3_Pin GPIO_PIN_2
#define LED3_GPIO_Port GPIOB
#define LED4_Pin GPIO_PIN_10
#define LED4_GPIO_Port GPIOB
#define trig1_Pin GPIO_PIN_12
#define trig1_GPIO_Port GPIOB
#define trig2_Pin GPIO_PIN_13
#define trig2_GPIO_Port GPIOB
#define trig3_Pin GPIO_PIN_14
#define trig3_GPIO_Port GPIOB
#define trig4_Pin GPIO_PIN_15
#define trig4_GPIO_Port GPIOB
#define echo1_Pin GPIO_PIN_8
#define echo1_GPIO_Port GPIOA
#define echo2_Pin GPIO_PIN_9
#define echo2_GPIO_Port GPIOA
#define echo3_Pin GPIO_PIN_10
#define echo3_GPIO_Port GPIOA
#define echo4_Pin GPIO_PIN_11
#define echo4_GPIO_Port GPIOA
#define LED2_Pin GPIO_PIN_12
#define LED2_GPIO_Port GPIOA
#define M4_SLP_Pin GPIO_PIN_15
#define M4_SLP_GPIO_Port GPIOA
#define M4_DIR_Pin GPIO_PIN_3
#define M4_DIR_GPIO_Port GPIOB
#define M4_STEP_Pin GPIO_PIN_4
#define M4_STEP_GPIO_Port GPIOB
#define M3_SLP_Pin GPIO_PIN_5
#define M3_SLP_GPIO_Port GPIOB
#define M3_DIR_Pin GPIO_PIN_8
#define M3_DIR_GPIO_Port GPIOB
#define M3_STEP_Pin GPIO_PIN_9
#define M3_STEP_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
