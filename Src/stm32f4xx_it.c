/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @brief   Interrupt Service Routines.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdbool.h>
#include "driver.h"
#include "database.h"

#include "standby_mode.h"

#include "pcv_mode.h"
#include "simv_mode.h"
#include "psv_mode.h"
#include "acv_mode.h"

#include "pcv_alarms.h"
#include "simv_alarms.h"
#include "psv_alarms.h"
#include "acv_alarms.h"



/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
 extern int pwm,turbo_speed;
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
int tm1t=0,sw1=0,tm2_speed=0,spd=0,tf=0;
int t=500,t1=350,s1=20,s2=40,e=100,tm2=0;
int PSV_SV_Counter=0;

extern int t,t1,s1,s2,st[];
extern int sw2,e,status_bar;
extern int t3_counter,t3_counter_old,mode_counter;
int status_counter=0;
extern int duration_Ins,duration_Exp,turbo_speed_Ins,turbo_speed_Exp,is_inspiratory;

extern modes CURRENT_MODE;
extern bool Config_request,status_change_falg;
extern bool Audio_Paused_available,Alarm_Paused_available;
extern int32_t ACV_Vt_Sens,PCV_Vt_Sens,SIMV_Vt_Sens,PSV_Vt_Sens;

extern bool PSV_MODE_INS;
extern 	int  cnt_temp;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim12;
extern UART_HandleTypeDef huart2;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */ 
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles EXTI line[9:5] interrupts.
  */
void EXTI9_5_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI9_5_IRQn 0 */
	sw1 = 0;
	if(Audio_Paused_available)
	  buzzer(2,0);
	if(Alarm_Paused_available)
	   status(2,0);
	
  /* USER CODE END EXTI9_5_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_9);
  /* USER CODE BEGIN EXTI9_5_IRQn 1 */

  /* USER CODE END EXTI9_5_IRQn 1 */
}

/**
  * @brief This function handles TIM1 update interrupt and TIM10 global interrupt.
  */
void TIM1_UP_TIM10_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_UP_TIM10_IRQn 0 */
	tm1t++;
	if(tm1t==100)
		tm1t = 0;
	
	if(tm1t<pwm)
		HAL_GPIO_WritePin(PWM_GPIO_Port, PWM_Pin, GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(PWM_GPIO_Port, PWM_Pin, GPIO_PIN_RESET);

  /* USER CODE END TIM1_UP_TIM10_IRQn 0 */
  HAL_TIM_IRQHandler(&htim1);
  /* USER CODE BEGIN TIM1_UP_TIM10_IRQn 1 */

  /* USER CODE END TIM1_UP_TIM10_IRQn 1 */
}

/**
  * @brief This function handles TIM2 global interrupt.
  */
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */
	tm2_speed++;
	if(tm2_speed==10)
	{
		turbo_speed = sw2*600;
		sw2 = 0;
		tm2_speed = 0;
	}
	sw1++;
	

	
	if (sw1==300)
		if (HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_9))
			Config_request=true;
			//buzzer(2,1);
  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */

  /* USER CODE END TIM2_IRQn 1 */
}

/**
  * @brief This function handles TIM3 global interrupt.
  */
void TIM3_IRQHandler(void)
{
  /* USER CODE BEGIN TIM3_IRQn 0 */


		
		
	if(CURRENT_MODE==PSV)
	{
		if(PSV_SV_Counter>35)
	 {
      PSV_SV_Counter=0;
		  if(CURRENT_MODE!=STOP && CURRENT_MODE!=STANDBY)
	    HAL_GPIO_WritePin(Valve3_GPIO_Port,Valve3_Pin,GPIO_PIN_RESET);
	 }
	 else
	 {
		 if(PSV_MODE_INS==false)
		    PSV_SV_Counter++;
		 else
			 PSV_SV_Counter=0;
	 }
	 
	 if(PSV_MODE_INS==true)   // ins
	 {
		  spd = turbo_speed_Ins;
		  
		 if(CURRENT_MODE!=STOP && CURRENT_MODE!=STANDBY)
		   HAL_GPIO_WritePin(Valve3_GPIO_Port,Valve3_Pin,GPIO_PIN_SET);
		  
		 t3_counter++;
		 PSV_Vt_Sens=0;
		 cnt_temp=0;
		  
		 is_inspiratory=1;
		 
	 }
	 else   //Exp  - No action
	 {
		  t3_counter=0;
		  cnt_temp=-100;
		  spd = turbo_speed_Exp;
		  is_inspiratory=0;
		 
		 //PSV_SV_Counter=0;
		 
	 }
	 
	}
	else  // modes == STOP,STANDBY,SIMV, PCV, ACV
	{
		t3_counter++;
	
		if(t3_counter>=duration_Ins+duration_Exp )
	{
		   cnt_temp=cnt_temp+1;

		t3_counter = 0;
		t3_counter_old=0;
		ACV_Vt_Sens=0;
		PCV_Vt_Sens=0;
		SIMV_Vt_Sens=0;
		
		
	}
	if(t3_counter<=duration_Ins )
	{
		
		spd = turbo_speed_Ins;
    if(CURRENT_MODE!=STOP && CURRENT_MODE!=STANDBY)
		   HAL_GPIO_WritePin(Valve3_GPIO_Port,Valve3_Pin,GPIO_PIN_SET);
		is_inspiratory=1;
		
		
	}
	if(t3_counter>duration_Ins)
	{
//     if(CURRENT_MODE!=STOP && CURRENT_MODE!=STANDBY)
//	    HAL_GPIO_WritePin(Valve3_GPIO_Port,Valve3_Pin,GPIO_PIN_RESET);
		spd = turbo_speed_Exp;
		is_inspiratory=0;
		 ACV_Vt_Sens=0;
		
		
	}
	if(t3_counter>duration_Ins+30)
	{
    if(CURRENT_MODE!=STOP && CURRENT_MODE!=STANDBY)
	    HAL_GPIO_WritePin(Valve3_GPIO_Port,Valve3_Pin,GPIO_PIN_RESET);
	}

//	if((t3_counter%10)==0)
//	{	
}
		if(spd>=0)	
			turbo(spd);
	//}

		if(t3_counter%100)
		{
			led(6,0);
		}
		else
		{
		  led(6,1);
		}
  /* USER CODE END TIM3_IRQn 0 */
  HAL_TIM_IRQHandler(&htim3);
  /* USER CODE BEGIN TIM3_IRQn 1 */

  /* USER CODE END TIM3_IRQn 1 */
}

/**
  * @brief This function handles TIM4 global interrupt.
  */
void TIM4_IRQHandler(void)
{
  /* USER CODE BEGIN TIM4_IRQn 0 */
   mode_counter++;
	
	if(mode_counter==50)
	{
		
		mode_counter=0;
		if(CURRENT_MODE==STANDBY) // STANDBY
    {
	       STANDBY_Mode();
    }	
		else if(CURRENT_MODE==PSV)
		{
		   PSV_Mode();
			// PSV_Alarms();
		}
    else if(CURRENT_MODE==PCV)
		{
		   PCV_Mode();
			// PCV_Alarms();
		}	
    else if(CURRENT_MODE==ACV)
		{
			
		   ACV_Mode();
		//	 ACV_Alarms();
		}	
     else if(CURRENT_MODE==SIMV)
		{
		   SIMV_Mode();
			// SIMV_Alarms();
		}	

		else // STOP
		{
		   turbo_speed_Ins=0,turbo_speed_Exp=0;
		}
			
	}
  /* USER CODE END TIM4_IRQn 0 */
  HAL_TIM_IRQHandler(&htim4);
  /* USER CODE BEGIN TIM4_IRQn 1 */

  /* USER CODE END TIM4_IRQn 1 */
}

/**
  * @brief This function handles USART2 global interrupt.
  */
void USART2_IRQHandler(void)
{
  /* USER CODE BEGIN USART2_IRQn 0 */

  /* USER CODE END USART2_IRQn 0 */
  HAL_UART_IRQHandler(&huart2);
  /* USER CODE BEGIN USART2_IRQn 1 */

  /* USER CODE END USART2_IRQn 1 */
}

/**
  * @brief This function handles EXTI line[15:10] interrupts.
  */
void EXTI15_10_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI15_10_IRQn 0 */
	sw2++;		
  /* USER CODE END EXTI15_10_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_10);
  /* USER CODE BEGIN EXTI15_10_IRQn 1 */
	
	
  /* USER CODE END EXTI15_10_IRQn 1 */
}

/**
  * @brief This function handles TIM8 break interrupt and TIM12 global interrupt.
  */
void TIM8_BRK_TIM12_IRQHandler(void)
{
  /* USER CODE BEGIN TIM8_BRK_TIM12_IRQn 0 */
	if (status_change_falg==1)
	{	
		status_change_falg = 0;
		for(status_counter=1;status_counter<status_bar+2;status_counter++)
		{
			HAL_GPIO_WritePin(LED_DATA_GPIO_Port, LED_DATA_Pin, st[status_counter]);
			HAL_GPIO_WritePin(LED_CLK_GPIO_Port, LED_CLK_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(LED_CLK_GPIO_Port, LED_CLK_Pin, GPIO_PIN_RESET);
			
		}
	}
  /* USER CODE END TIM8_BRK_TIM12_IRQn 0 */
  HAL_TIM_IRQHandler(&htim12);
  /* USER CODE BEGIN TIM8_BRK_TIM12_IRQn 1 */

  /* USER CODE END TIM8_BRK_TIM12_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
