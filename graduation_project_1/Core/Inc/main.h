/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#define step_x_Pin GPIO_PIN_1
#define step_x_GPIO_Port GPIOA
#define dir_x_Pin GPIO_PIN_2
#define dir_x_GPIO_Port GPIOA
#define step_d_Pin GPIO_PIN_4
#define step_d_GPIO_Port GPIOA
#define dir_d_Pin GPIO_PIN_5
#define dir_d_GPIO_Port GPIOA
#define dir_c_Pin GPIO_PIN_6
#define dir_c_GPIO_Port GPIOA
#define step_c_Pin GPIO_PIN_7
#define step_c_GPIO_Port GPIOA
#define step_e_Pin GPIO_PIN_4
#define step_e_GPIO_Port GPIOC
#define dir_e_Pin GPIO_PIN_5
#define dir_e_GPIO_Port GPIOC
#define x_limit_Pin GPIO_PIN_0
#define x_limit_GPIO_Port GPIOB
#define d_limit_Pin GPIO_PIN_1
#define d_limit_GPIO_Port GPIOB
#define c_limit_Pin GPIO_PIN_2
#define c_limit_GPIO_Port GPIOB
#define e_limit_Pin GPIO_PIN_7
#define e_limit_GPIO_Port GPIOE
#define led_Pin GPIO_PIN_13
#define led_GPIO_Port GPIOD

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
