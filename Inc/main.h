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
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "driver.h"
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
void start_psv_mode(void);
	
void decode_raspi_packet(void);
uint16_t crc_calc(uint8_t *data, uint8_t data_size);

void start_standby(void);
void date_time_decoder(void);

void psv_mode_decoder(void);
void pcv_mode_decoder(void);
void acv_mode_decoder(void);
void simv_mode_decoder(void);

void psv_alarm_decoder(void);
void pcv_alarm_decoder(void);
void acv_alarm_decoder(void);
void simv_alarm_decoder(void);

void create_response_for_raspberry(int function_id,int param_id);
void send_rspy(uint8_t *data, int size);
void print_debug(uint8_t *data, int size);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define EEPROM_WP_Pin GPIO_PIN_4
#define EEPROM_WP_GPIO_Port GPIOE
#define EEPROM_A1_Pin GPIO_PIN_5
#define EEPROM_A1_GPIO_Port GPIOE
#define EEPROM_A0_Pin GPIO_PIN_6
#define EEPROM_A0_GPIO_Port GPIOE
#define Flow1_Pin GPIO_PIN_6
#define Flow1_GPIO_Port GPIOF
#define FLow2_Pin GPIO_PIN_7
#define FLow2_GPIO_Port GPIOF
#define Pressure2_Pin GPIO_PIN_8
#define Pressure2_GPIO_Port GPIOF
#define Pressure1_Pin GPIO_PIN_10
#define Pressure1_GPIO_Port GPIOF
#define Pressure3_Pin GPIO_PIN_0
#define Pressure3_GPIO_Port GPIOC
#define Flow3_Pin GPIO_PIN_1
#define Flow3_GPIO_Port GPIOC
#define RSPY_TX_Pin GPIO_PIN_2
#define RSPY_TX_GPIO_Port GPIOA
#define RSPY_RX_Pin GPIO_PIN_3
#define RSPY_RX_GPIO_Port GPIOA
#define RSPY1_Pin GPIO_PIN_4
#define RSPY1_GPIO_Port GPIOC
#define RSPY2_Pin GPIO_PIN_5
#define RSPY2_GPIO_Port GPIOC
#define Buzzer3_Pin GPIO_PIN_11
#define Buzzer3_GPIO_Port GPIOF
#define Buzzer4_Pin GPIO_PIN_12
#define Buzzer4_GPIO_Port GPIOF
#define Alarm_Pin GPIO_PIN_13
#define Alarm_GPIO_Port GPIOF
#define Valve1_Pin GPIO_PIN_7
#define Valve1_GPIO_Port GPIOE
#define Valve2_Pin GPIO_PIN_8
#define Valve2_GPIO_Port GPIOE
#define Valve3_Pin GPIO_PIN_9
#define Valve3_GPIO_Port GPIOE
#define PWM_Pin GPIO_PIN_11
#define PWM_GPIO_Port GPIOE
#define SPI2_PWR_Pin GPIO_PIN_15
#define SPI2_PWR_GPIO_Port GPIOE
#define Buzzer1_Pin GPIO_PIN_10
#define Buzzer1_GPIO_Port GPIOD
#define Buzzer2_Pin GPIO_PIN_11
#define Buzzer2_GPIO_Port GPIOD
#define LED0_Pin GPIO_PIN_14
#define LED0_GPIO_Port GPIOD
#define LED1_Pin GPIO_PIN_15
#define LED1_GPIO_Port GPIOD
#define LED2_Pin GPIO_PIN_2
#define LED2_GPIO_Port GPIOG
#define LED3_Pin GPIO_PIN_3
#define LED3_GPIO_Port GPIOG
#define LED4_Pin GPIO_PIN_4
#define LED4_GPIO_Port GPIOG
#define LED5_Pin GPIO_PIN_5
#define LED5_GPIO_Port GPIOG
#define LED6_Pin GPIO_PIN_6
#define LED6_GPIO_Port GPIOG
#define LED7_Pin GPIO_PIN_7
#define LED7_GPIO_Port GPIOG
#define LED8_Pin GPIO_PIN_8
#define LED8_GPIO_Port GPIOG
#define RS485_TX_Pin GPIO_PIN_6
#define RS485_TX_GPIO_Port GPIOC
#define RS485_RX_Pin GPIO_PIN_7
#define RS485_RX_GPIO_Port GPIOC
#define RS485_EN_Pin GPIO_PIN_8
#define RS485_EN_GPIO_Port GPIOA
#define DR1_Pin GPIO_PIN_11
#define DR1_GPIO_Port GPIOG
#define DR2_Pin GPIO_PIN_12
#define DR2_GPIO_Port GPIOG
#define DR3_Pin GPIO_PIN_13
#define DR3_GPIO_Port GPIOG
#define DR4_Pin GPIO_PIN_14
#define DR4_GPIO_Port GPIOG
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
