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
 #define MAX_BUFFER_SIZE 500
 
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
int tm1t=0,sw1=0,tm2_speed=0,spd=0,tf=0;
int t=500,t1=350,s1=20,s2=40,e=100,tm2=0;
int PSV_SV_Counter=0,t2_counter=0;

float sumf=0.0;
int sum=0;

//int a=0,b=0,c=0,d=0,e1=0,f=0,g=0,h=0,i=0,j=0,Counter_loop=0;
//float af=0.0,bf=0.0,cf=0.0,df=0.0,ef=0.0,ff=0.0,gf=0.0,hf=0.0,iff=0.0,jf=0.0;
extern bool data_received_from_raspy;
extern int pressure_sensor_Ins,pressure_sensor_Exp,pressure_sensor_Triger,flow_sensor_Ins,flow_sensor_Exp;
extern int t,t1,s1,s2,st[20];
extern int sw2,e,status_bar;
extern int t3_counter,t3_counter_old,mode_counter;
int status_counter=0;
extern int duration_Ins,duration_Exp,turbo_speed_Ins,turbo_speed_Exp,is_inspiratory;
extern float Current_P_Triger;

extern modes CURRENT_MODE;
extern bool Config_request,status_change_falg;
extern bool Audio_Paused_available,Alarm_Paused_available;
extern int32_t ACV_Vt_Sens,PCV_Vt_Sens,SIMV_Vt_Sens,PSV_Vt_Sens;

extern bool PSV_MODE_INS;
extern int T_expiration;
extern 	int  cnt_temp;

extern int Current_Pressure_Ins,Current_Pressure_Exp,Current_Flow_Ins,Current_Flow_Exp;
int Pressure_Report_tmp=0,Flow_Report_tmp=0,O2_Report_tmp=0,Voloume_Report_tmp=0;
extern int Pressure_Report,Flow_Report,Voloume_Report,PasOxi_Report,O2_Report;
extern bool send_report;
extern int send_report_count_per_second;
extern bool receiving;

#define RX_BUFFER_SIZE 64	// Must be the same as defined in main.c file

/*extern char rx_buffer[RX_BUFFER_SIZE];
extern uint16_t rx_wr_index;
extern volatile uint16_t rx_counter;
extern volatile uint8_t rx_overflow;
extern bool receiving;*/

extern uint8_t rspy_receive_buffer[MAX_BUFFER_SIZE];
extern int rspy_receive_buffer_index;
extern int packet_received;
extern int max_flow1,max_flow2;
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
	
	     sum=0;
			 sum+=(int)pressure(pressure_sensor_Ins);
		   sum+=(int)pressure(pressure_sensor_Ins);
       sum+=(int)pressure(pressure_sensor_Ins);
       sum+=(int)pressure(pressure_sensor_Ins);
       sum+=(int)pressure(pressure_sensor_Ins);
       sum+=(int)pressure(pressure_sensor_Ins);
       sum+=(int)pressure(pressure_sensor_Ins);
       sum+=(int)pressure(pressure_sensor_Ins);
       sum+=(int)pressure(pressure_sensor_Ins);
       sum+=(int)pressure(pressure_sensor_Ins);
			      
		   if(sum<=0)
		   {
         Current_Pressure_Ins=0;
		   }
		   else
		   {
			   Current_Pressure_Ins=(int)((sum*20)/100);
		   }
			 
		   sum=0;
		   sum+=(int)pressure(pressure_sensor_Exp);
		   sum+=(int)pressure(pressure_sensor_Exp);
       sum+=(int)pressure(pressure_sensor_Exp);
       sum+=(int)pressure(pressure_sensor_Exp);
       sum+=(int)pressure(pressure_sensor_Exp);
       sum+=(int)pressure(pressure_sensor_Exp);
       sum+=(int)pressure(pressure_sensor_Exp);
       sum+=(int)pressure(pressure_sensor_Exp);
       sum+=(int)pressure(pressure_sensor_Exp);
       sum+=(int)pressure(pressure_sensor_Exp);
		
	     
		   if(sum<=0)
		   {
         Current_Pressure_Exp=0;
		   }
		   else
		   {
			   Current_Pressure_Exp=(int)(sum/10);
		   }
			 
    	sumf=0;
			sumf+=pressure(pressure_sensor_Triger);
		  sumf+=pressure(pressure_sensor_Triger);
      sumf+=pressure(pressure_sensor_Triger);
      sumf+=pressure(pressure_sensor_Triger);
      sumf+=pressure(pressure_sensor_Triger);
      sumf+=pressure(pressure_sensor_Triger);
      sumf+=pressure(pressure_sensor_Triger);
      sumf+=pressure(pressure_sensor_Triger);
      sumf+=pressure(pressure_sensor_Triger);
      sumf+=pressure(pressure_sensor_Triger);
		

		   if(sumf<=0)
		   {
         Current_P_Triger=0;
		   }
		   else
		   {
			   Current_P_Triger=sumf/4;
		   }
			 
			 sum=0;
			 sum+=(int)flow(flow_sensor_Ins);
		   sum+=(int)flow(flow_sensor_Ins);
       sum+=(int)flow(flow_sensor_Ins);
       sum+=(int)flow(flow_sensor_Ins);
       sum+=(int)flow(flow_sensor_Ins);
       sum+=(int)flow(flow_sensor_Ins);
       sum+=(int)flow(flow_sensor_Ins);
       sum+=(int)flow(flow_sensor_Ins);
       sum+=(int)flow(flow_sensor_Ins);
       sum+=(int)flow(flow_sensor_Ins);
		     
		   if(sum<=0)
		   {
         Current_Flow_Ins=0;
		   }
		   else
		   {
			   Current_Flow_Ins=(int)(sum/10);
		   }
    
			 Current_Flow_Ins=Current_Flow_Ins*110/100;
			 
			 
			 sum=0; 
			 sum+=(int)flow(flow_sensor_Exp);
		   sum+=(int)flow(flow_sensor_Exp);
       sum+=(int)flow(flow_sensor_Exp);
       sum+=(int)flow(flow_sensor_Exp);
       sum+=(int)flow(flow_sensor_Exp);
       sum+=(int)flow(flow_sensor_Exp);
       sum+=(int)flow(flow_sensor_Exp);
       sum+=(int)flow(flow_sensor_Exp);
       sum+=(int)flow(flow_sensor_Exp);
       sum+=(int)flow(flow_sensor_Exp);
			     
		   if(sum<=0)
		   {
         Current_Flow_Exp=0;
		   }
		   else
		   {
			   Current_Flow_Exp=(int)(sum/10);
		   }
			 //Current_Flow_Ins=Current_Flow_Exp;
	
 
			 t2_counter++;

	if(t2_counter>=100/send_report_count_per_second)
	{
		
     t2_counter=0;	

		Pressure_Report=Pressure_Report_tmp/100/send_report_count_per_second; 

		if(CURRENT_MODE==SIMV)
			Voloume_Report=SIMV_Vt_Sens;
		else if(CURRENT_MODE==PCV)
		  Voloume_Report=PCV_Vt_Sens;
		else if(CURRENT_MODE==ACV)
			Voloume_Report=ACV_Vt_Sens;
		else if(CURRENT_MODE==PSV)
			Voloume_Report=PSV_Vt_Sens;
		else
			Voloume_Report=0;
					
    Voloume_Report_tmp=	Voloume_Report;
		
		Flow_Report=Flow_Report_tmp/100/send_report_count_per_second; 
	
		send_report = !data_received_from_raspy;
		
		
		PasOxi_Report= O2_Report_tmp/100/send_report_count_per_second;
		
  	Pressure_Report_tmp=0;		
		
		
		Flow_Report_tmp=0;
		
		O2_Report_tmp=0;

	}
	else
	{
		Pressure_Report_tmp=Pressure_Report_tmp+Current_Pressure_Ins;
		
		Flow_Report_tmp=Flow_Report_tmp+Current_Flow_Ins;
		
		O2_Report_tmp=Voloume_Report_tmp;
	}

	
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
		 // PSV_Vt_Sens=0;
      PSV_SV_Counter=0;
		  if(CURRENT_MODE!=STOP && CURRENT_MODE!=STANDBY)
	    HAL_GPIO_WritePin(Valve3_GPIO_Port,Valve3_Pin,GPIO_PIN_RESET);
	 }
	 else
	 {
		 if(PSV_MODE_INS==false)
		 {
		    PSV_SV_Counter++;
			  T_expiration++;
		 }
		 else
		 {
			 PSV_SV_Counter=0;
			 T_expiration=0;
		 }
	 }
	 
	 if(PSV_MODE_INS==true)   // ins
	 {
		 
		  spd = turbo_speed_Ins;
		  
		 if(CURRENT_MODE!=STOP && CURRENT_MODE!=STANDBY)
		   HAL_GPIO_WritePin(Valve3_GPIO_Port,Valve3_Pin,GPIO_PIN_SET);
		  
		 t3_counter++;
		 //
		 cnt_temp=0;
		  
		 is_inspiratory=1;
		 
	 }
	 else   //Exp  - No action
	 {
//	 	t3_counter++;
//		if(t3_counter>=duration_Ins+duration_Exp )
     	t3_counter = 0;

		  cnt_temp=-100;
		  spd = turbo_speed_Exp;
		  is_inspiratory=0;
		 PSV_Vt_Sens=0;
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
		
		max_flow1=0;
		max_flow2=0;
		
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
//		ACV_Vt_Sens=0;
//		PCV_Vt_Sens=0;
//		SIMV_Vt_Sens=0;
		

		
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
  //HAL_UART_IRQHandler(&huart2);
  /* USER CODE BEGIN USART2_IRQn 1 */

	if (__HAL_UART_GET_IT_SOURCE(&huart2, UART_IT_RXNE))
	{
		status(2,1);
		rspy_receive_buffer[rspy_receive_buffer_index] = huart2.Instance->DR;
		
		rspy_receive_buffer_index++;
		if (rspy_receive_buffer_index >= MAX_BUFFER_SIZE)
		{
			rspy_receive_buffer_index = 0;
		}
		
		if(rspy_receive_buffer_index > 0 && rspy_receive_buffer[rspy_receive_buffer_index-2]==0xFF &&rspy_receive_buffer[rspy_receive_buffer_index-1]==0x0A)// && rx_buffer == 10)
		{		  
			packet_received = 1;			
			data_received_from_raspy=true;
		}
	}
	
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
			HAL_GPIO_WritePin(LED_DATA_GPIO_Port, LED_DATA_Pin, (GPIO_PinState)st[status_counter]);
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
