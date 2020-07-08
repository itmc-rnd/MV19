/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "show_alarms.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define MAX_BUFFER_SIZE 500


const unsigned  int CrcTable[] = {
  0X0000, 0XC0C1, 0XC181, 0X0140, 0XC301, 0X03C0, 0X0280, 0XC241,
  0XC601, 0X06C0, 0X0780, 0XC741, 0X0500, 0XC5C1, 0XC481, 0X0440,
  0XCC01, 0X0CC0, 0X0D80, 0XCD41, 0X0F00, 0XCFC1, 0XCE81, 0X0E40,
  0X0A00, 0XCAC1, 0XCB81, 0X0B40, 0XC901, 0X09C0, 0X0880, 0XC841,
  0XD801, 0X18C0, 0X1980, 0XD941, 0X1B00, 0XDBC1, 0XDA81, 0X1A40,
  0X1E00, 0XDEC1, 0XDF81, 0X1F40, 0XDD01, 0X1DC0, 0X1C80, 0XDC41,
  0X1400, 0XD4C1, 0XD581, 0X1540, 0XD701, 0X17C0, 0X1680, 0XD641,
  0XD201, 0X12C0, 0X1380, 0XD341, 0X1100, 0XD1C1, 0XD081, 0X1040,
  0XF001, 0X30C0, 0X3180, 0XF141, 0X3300, 0XF3C1, 0XF281, 0X3240,
  0X3600, 0XF6C1, 0XF781, 0X3740, 0XF501, 0X35C0, 0X3480, 0XF441,
  0X3C00, 0XFCC1, 0XFD81, 0X3D40, 0XFF01, 0X3FC0, 0X3E80, 0XFE41,
  0XFA01, 0X3AC0, 0X3B80, 0XFB41, 0X3900, 0XF9C1, 0XF881, 0X3840,
  0X2800, 0XE8C1, 0XE981, 0X2940, 0XEB01, 0X2BC0, 0X2A80, 0XEA41,
  0XEE01, 0X2EC0, 0X2F80, 0XEF41, 0X2D00, 0XEDC1, 0XEC81, 0X2C40,
  0XE401, 0X24C0, 0X2580, 0XE541, 0X2700, 0XE7C1, 0XE681, 0X2640,
  0X2200, 0XE2C1, 0XE381, 0X2340, 0XE101, 0X21C0, 0X2080, 0XE041,
  0XA001, 0X60C0, 0X6180, 0XA141, 0X6300, 0XA3C1, 0XA281, 0X6240,
  0X6600, 0XA6C1, 0XA781, 0X6740, 0XA501, 0X65C0, 0X6480, 0XA441,
  0X6C00, 0XACC1, 0XAD81, 0X6D40, 0XAF01, 0X6FC0, 0X6E80, 0XAE41,
  0XAA01, 0X6AC0, 0X6B80, 0XAB41, 0X6900, 0XA9C1, 0XA881, 0X6840,
  0X7800, 0XB8C1, 0XB981, 0X7940, 0XBB01, 0X7BC0, 0X7A80, 0XBA41,
  0XBE01, 0X7EC0, 0X7F80, 0XBF41, 0X7D00, 0XBDC1, 0XBC81, 0X7C40,
  0XB401, 0X74C0, 0X7580, 0XB541, 0X7700, 0XB7C1, 0XB681, 0X7640,
  0X7200, 0XB2C1, 0XB381, 0X7340, 0XB101, 0X71C0, 0X7080, 0XB041,
  0X5000, 0X90C1, 0X9181, 0X5140, 0X9301, 0X53C0, 0X5280, 0X9241,
  0X9601, 0X56C0, 0X5780, 0X9741, 0X5500, 0X95C1, 0X9481, 0X5440,
  0X9C01, 0X5CC0, 0X5D80, 0X9D41, 0X5F00, 0X9FC1, 0X9E81, 0X5E40,
  0X5A00, 0X9AC1, 0X9B81, 0X5B40, 0X9901, 0X59C0, 0X5880, 0X9841,
  0X8801, 0X48C0, 0X4980, 0X8941, 0X4B00, 0X8BC1, 0X8A81, 0X4A40,
  0X4E00, 0X8EC1, 0X8F81, 0X4F40, 0X8D01, 0X4DC0, 0X4C80, 0X8C41,
  0X4400, 0X84C1, 0X8581, 0X4540, 0X8701, 0X47C0, 0X4680, 0X8641,
  0X8201, 0X42C0, 0X4380, 0X8341, 0X4100, 0X81C1, 0X8081, 0X4040
};

//int t=500,t1=350,s1=20,s2=40,tf=0,e=100,tm2=0;

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */



/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc3;

DAC_HandleTypeDef hdac;

I2C_HandleTypeDef hi2c1;

SPI_HandleTypeDef hspi1;
SPI_HandleTypeDef hspi2;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;
TIM_HandleTypeDef htim12;

UART_HandleTypeDef huart4;
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;
UART_HandleTypeDef huart6;

/* USER CODE BEGIN PV */

uint8_t rspy_receive_buffer[MAX_BUFFER_SIZE];
//bool packet_received = false;
extern bool data_received_from_raspy;
int packet_received = 0;
int rspy_receive_buffer_index = 0;
bool send_complete = true, paceket_decoded = false;
extern modes CURRENT_MODE;
extern int Current_Pressure_Ins, Current_Pressure_Exp, Current_Flow_Ins, Current_Flow_Exp;
extern float Current_P_Triger;
extern int LED_POWER1, LED_POWER2, LED_BATTRY_Red, LED_BATTRY_Green, LED_Apnea, LED_ALARM_Hi, LED_ALARM_Low, LED_STANDBY1, LED_STANDBY2, LED_ACV1, LED_ACV2, LED_ACP, LED_SIMV, LED_PSV;
extern int sent_ALARM_Hi_code, sent_ALARM_Low_code;
bool no_alarm_sent = false;

extern int turbo_speed_Ins, turbo_speed_Exp, turbo_speed, is_inspiratory, raise_step;
extern int pwm_i_acp, pwm_e_pcv, ACP_RATE;
extern int pwm_i_simv, pwm_e_simv, SIMV_RATE_SIMV;
extern char buf[1000];
char buf2[10];
uint8_t rspy_receive_buffer_Data[1000];
extern bool Config_request;
extern int duration_Ins, duration_Exp;
extern int t3_counter;
extern bool PSV_MODE_STEP;
extern bool PSV_MODE_INS;
extern bool ALARM_Hi, ALARM_Low;

extern bool turbo_error, pressure_s1_error, pressure_s2_error, flow_s_error, buzzer_error;
extern bool flow_s1_error, flow_s2_error;

extern bool ALARM_RECEIVED;
extern int ALARM_CODE;
extern bool sigh_occured;
extern int sigh_counter;

extern int cnt_temp;
extern int is_trigger_simv;
extern int32_t ACV_Vt_Sens, ACP_Vt_Sens, SIMV_Vt_Sens, PSV_Vt_Sens;

extern int Pressure_Report, Flow_Report, Voloume_Report, PasOxi_Report, O2_Report;
extern bool send_report;
extern uint8_t report_response_packet[156];
extern int report_response_packet_index;
extern int packet_index;
int loop_indx = 0;
uint8_t dt[141];

int max_flow1 = 0, max_flow2 = 0;

HAL_StatusTypeDef uart_status;

extern int32_t ACV_Vt_Sens_Ins, ACV_Vt_Sens_Exp;

uint16_t rx_rd_index, rx_wr_index;
volatile uint16_t rx_counter;
volatile uint8_t rx_overflow;
bool receiving = false;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC3_Init(void);
static void MX_DAC_Init(void);
static void MX_SPI1_Init(void);
static void MX_SPI2_Init(void);
static void MX_UART4_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_USART6_UART_Init(void);
static void MX_I2C1_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM4_Init(void);
static void MX_TIM12_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_ADC3_Init();
	MX_DAC_Init();
	MX_SPI1_Init();
	MX_SPI2_Init();
	MX_UART4_Init();
	MX_USART1_UART_Init();
	MX_USART2_UART_Init();
	MX_USART3_UART_Init();
	MX_USART6_UART_Init();
	MX_I2C1_Init();
	MX_TIM1_Init();
	MX_TIM2_Init();
	MX_TIM3_Init();
	MX_TIM4_Init();
	MX_TIM12_Init();
	/* USER CODE BEGIN 2 */

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */

	  //HAL_UART_Receive_IT(&huart2, &rx_buffer2, 1);



	  // int cnt=0;


	driver_init();
	HAL_Delay(200);
	check_devices();

	HAL_TIM_Base_Start_IT(&htim4);

	status(LED_POWER1, 1);  //POWER LED
	status(LED_POWER2, 1);  //POWER LED

	status(LED_STANDBY1, 1);  //Mode led STANDBY on
	status(LED_STANDBY2, 1);  //Mode led STANDBY on

	status(LED_BATTRY_Red, 1);  //POWER Battry
	//status(LED_BATTRY_Green, 1);  //POWER Battry


	__HAL_UART_ENABLE_IT(&huart2, UART_IT_RXNE);

	while (1)
	{

		if (packet_received == 1)
		{


			paceket_decoded = false;
			HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);

			decode_raspi_packet();


			data_received_from_raspy = false;

			rspy_receive_buffer_index = 0;
			//HAL_Delay(500);
			packet_received = 0;

		}
		else
		{
			if (paceket_decoded)
			{

				if (Config_request)
				{
					create_response_for_raspberry(5, 0);
					Config_request = false;
				}

				if (CURRENT_MODE > 1)
				{
					if (send_report)
					{

						//						 if(max_flow1<=ACV_Vt_Sens_Ins)
						//				        max_flow1=ACV_Vt_Sens_Ins;
						//						if(Voloume_Report!= max_flow1)
						//						{

						//							create_report_for_raspberry(20,Pressure_Report,Flow_Report,max_flow1,PasOxi_Report,O2_Report);
						//					  }
						//						else
											// create_report_for_raspberry(20,Pressure_Report,Flow_Report,Voloume_Report,PasOxi_Report,O2_Report);


						report_response_packet[0] = 0xFE;
						report_response_packet[1] = 0x8D;  // len  141=0x8D   10*14=140 + Function_id = 141
						report_response_packet[2] = packet_index++;    //packect Index 
						report_response_packet[3] = 0x14;    //function_id;  20 = 0x14 
						if (packet_index > 50000)
							packet_index = 1;
						// START Calculate CRC
						for (loop_indx = 0; loop_indx < 141; loop_indx++)
						{
							dt[loop_indx] = report_response_packet[3 + loop_indx];
						}
						uint16_t resp_crc = crc_calc(dt, report_response_packet[1]);
						if (resp_crc <= 256)
						{
							report_response_packet[144] = 0x00;
							report_response_packet[145] = resp_crc;
						}
						else
						{
							report_response_packet[144] = (int)resp_crc / 256;
							report_response_packet[145] = resp_crc % 256;
						}
						// END Calculate CRC
						report_response_packet[146] = 0xFF;
						report_response_packet[147] = 0x0A;





						send_rspy(report_response_packet, 148);

						//						buf[0] = 0;
						//												
						//						for(int i=0; i<148; i++){
						//							sprintf(buf2,"%02d ",report_response_packet[i]);//,length(report_response_packet));
						//							strcat(buf, buf2); 							
						//						}
						//						
						//		        print_debug((uint8_t *)buf, strlen(buf));
						//					
						//						sprintf(buf,"\r\n\r\n");
						//						print_debug((uint8_t *)buf, strlen(buf));

						report_response_packet_index = 0;
						send_report = false;


						//	sprintf(buf, "\f  Voloume_Report=%d ,  MAX ACV_Vt_Sens_Ins=%d  ",Voloume_Report, max_flow1);
								//HAL_UART_Receive_IT(&huart2, &rx_buffer2, 1);	
					}
					else
					{
						//while(HAL_UART_Receive(&huart2, &c, 1, 5) == HAL_UART_ERROR_NONE); 				
					}
				}

				if (ALARM_RECEIVED)
				{
					if (ALARM_Hi == true)
					{
						if (sent_ALARM_Hi_code == 0)
						{
							buzzer(2, 1);
							status(LED_ALARM_Hi, 1);  //  ALARM Hi LED On
							status(LED_ALARM_Low, 0);  //  ALARM Low LED OFF
							ALARM_RECEIVED = false;

							sent_ALARM_Hi_code = ALARM_CODE;
							create_response_for_raspberry(111, ALARM_CODE);
							no_alarm_sent = false;
						}
					}
					else
					{
						if (ALARM_Low == true)
						{
							if (sent_ALARM_Low_code == 0)
							{
								buzzer(2, 1);
								status(LED_ALARM_Hi, 0);  //  ALARM Hi LED OFF
								status(LED_ALARM_Low, 1);  //  ALARM Low LED on							 
								ALARM_RECEIVED = false;

								sent_ALARM_Low_code = ALARM_CODE;
								create_response_for_raspberry(111, ALARM_CODE);
								no_alarm_sent = false;
							}

						}
					}
				}
				else  // NO ALARM
				{


					if (no_alarm_sent == false)
					{
					  buzzer(2, 0);
					  status(LED_ALARM_Hi, 0);
					  status(LED_ALARM_Low, 0);

					  ALARM_RECEIVED = false;
					  sent_ALARM_Hi_code = 0;
					  sent_ALARM_Low_code = 0;
						
						create_response_for_raspberry(111, 0);
						no_alarm_sent = true;
					}

				}
			}

			HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);

//			if (max_flow1 <= Current_Pressure_Ins)
//				max_flow1 = Current_Pressure_Ins;

//			if (max_flow2 <= Current_Pressure_Exp)
//				max_flow2 = Current_Pressure_Exp;

			//		sprintf(buf, "\f  F-ins=%d , F-exp=%d  , MAX ACV_Vt_Sens_Ins=%d    , MAX ACV_Vt_Sens_Exp=%d  , E-I=%d  ",Current_Flow_Ins,Current_Flow_Exp, max_flow1,max_flow2,(max_flow2-max_flow1));

					//__HAL_UART_DISABLE_IT(&huart2, UART_IT_RXNE);			
					 sprintf(buf, "\f cnt=%d , pd=%d, indx=%d, T=%d , Ins=%d , Exp=%d , t_spd_I=%d , t_spd_E=%d  ,t_spd=%d , M=%d - is_I=%d , P-ins=%d , P-exp=%d  pi-pe=%d ,P-Trriger= %4.2f, F-ins=%d , F-exp=%d , MAX Current_Pressure_Ins=%d    , MAX Current_Pressure_Exp=%d   , ACV_Vt_Sens=%d           ", cnt_temp,(int)paceket_decoded,rspy_receive_buffer_index,is_trigger_simv,duration_Ins,duration_Exp,turbo_speed_Ins,turbo_speed_Exp, turbo_speed,(int)CURRENT_MODE,is_inspiratory,Current_Pressure_Ins,Current_Pressure_Exp,Current_Pressure_Ins-Current_Pressure_Exp,Current_P_Triger,Current_Flow_Ins,Current_Flow_Exp, max_flow1,max_flow2,ACV_Vt_Sens);
						//sprintf(buf, "\f status= %X", HAL_UART_GetState(&huart2));			
						//sprintf(buf, "status= %X - %X\r\n", uart_status, HAL_UART_GetState(&huart2));		 
				//	 sprintf(buf,"\f cnt=%d , array=%d",cnt_temp,0);//,length(report_response_packet));
				   print_debug((uint8_t *)buf, strlen(buf));
					//__HAL_UART_ENABLE_IT(&huart2, UART_IT_RXNE);


					//HAL_UART_Transmit(&huart1,(uint8_t *) buf, 200, 20 );
					HAL_Delay(200);
		}

	}
	/* USER CODE END WHILE */

	/* USER CODE BEGIN 3 */

  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Configure the main internal regulator output voltage
	*/
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
	/** Initializes the CPU, AHB and APB busses clocks
	*/
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLM = 8;
	RCC_OscInitStruct.PLL.PLLN = 72;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 3;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}
	/** Initializes the CPU, AHB and APB busses clocks
	*/
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
		| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
	{
		Error_Handler();
	}
}

/**
  * @brief ADC3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC3_Init(void)
{

	/* USER CODE BEGIN ADC3_Init 0 */

	/* USER CODE END ADC3_Init 0 */

	ADC_ChannelConfTypeDef sConfig = { 0 };

	/* USER CODE BEGIN ADC3_Init 1 */

	/* USER CODE END ADC3_Init 1 */
	/** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
	*/
	hadc3.Instance = ADC3;
	hadc3.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV8;
	hadc3.Init.Resolution = ADC_RESOLUTION_12B;
	hadc3.Init.ScanConvMode = DISABLE;
	hadc3.Init.ContinuousConvMode = DISABLE;
	hadc3.Init.DiscontinuousConvMode = DISABLE;
	hadc3.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	hadc3.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hadc3.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc3.Init.NbrOfConversion = 1;
	hadc3.Init.DMAContinuousRequests = DISABLE;
	hadc3.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	if (HAL_ADC_Init(&hadc3) != HAL_OK)
	{
		Error_Handler();
	}
	/** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	*/
	sConfig.Channel = ADC_CHANNEL_4;
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN ADC3_Init 2 */

	/* USER CODE END ADC3_Init 2 */

}

/**
  * @brief DAC Initialization Function
  * @param None
  * @retval None
  */
static void MX_DAC_Init(void)
{

	/* USER CODE BEGIN DAC_Init 0 */

	/* USER CODE END DAC_Init 0 */

	DAC_ChannelConfTypeDef sConfig = { 0 };

	/* USER CODE BEGIN DAC_Init 1 */

	/* USER CODE END DAC_Init 1 */
	/** DAC Initialization
	*/
	hdac.Instance = DAC;
	if (HAL_DAC_Init(&hdac) != HAL_OK)
	{
		Error_Handler();
	}
	/** DAC channel OUT1 config
	*/
	sConfig.DAC_Trigger = DAC_TRIGGER_NONE;
	sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
	if (HAL_DAC_ConfigChannel(&hdac, &sConfig, DAC_CHANNEL_1) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN DAC_Init 2 */

	/* USER CODE END DAC_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

	/* USER CODE BEGIN I2C1_Init 0 */

	/* USER CODE END I2C1_Init 0 */

	/* USER CODE BEGIN I2C1_Init 1 */

	/* USER CODE END I2C1_Init 1 */
	hi2c1.Instance = I2C1;
	hi2c1.Init.ClockSpeed = 100000;
	hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
	hi2c1.Init.OwnAddress1 = 0;
	hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c1.Init.OwnAddress2 = 0;
	hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	if (HAL_I2C_Init(&hi2c1) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN I2C1_Init 2 */

	/* USER CODE END I2C1_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

	/* USER CODE BEGIN SPI1_Init 0 */

	/* USER CODE END SPI1_Init 0 */

	/* USER CODE BEGIN SPI1_Init 1 */

	/* USER CODE END SPI1_Init 1 */
	/* SPI1 parameter configuration*/
	hspi1.Instance = SPI1;
	hspi1.Init.Mode = SPI_MODE_MASTER;
	hspi1.Init.Direction = SPI_DIRECTION_2LINES;
	hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi1.Init.NSS = SPI_NSS_SOFT;
	hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
	hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi1.Init.CRCPolynomial = 10;
	if (HAL_SPI_Init(&hspi1) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN SPI1_Init 2 */

	/* USER CODE END SPI1_Init 2 */

}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

	/* USER CODE BEGIN SPI2_Init 0 */

	/* USER CODE END SPI2_Init 0 */

	/* USER CODE BEGIN SPI2_Init 1 */

	/* USER CODE END SPI2_Init 1 */
	/* SPI2 parameter configuration*/
	hspi2.Instance = SPI2;
	hspi2.Init.Mode = SPI_MODE_MASTER;
	hspi2.Init.Direction = SPI_DIRECTION_2LINES;
	hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi2.Init.NSS = SPI_NSS_HARD_INPUT;
	hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
	hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi2.Init.CRCPolynomial = 10;
	if (HAL_SPI_Init(&hspi2) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN SPI2_Init 2 */

	/* USER CODE END SPI2_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

	/* USER CODE BEGIN TIM1_Init 0 */

	/* USER CODE END TIM1_Init 0 */

	TIM_ClockConfigTypeDef sClockSourceConfig = { 0 };
	TIM_MasterConfigTypeDef sMasterConfig = { 0 };

	/* USER CODE BEGIN TIM1_Init 1 */

	/* USER CODE END TIM1_Init 1 */
	htim1.Instance = TIM1;
	htim1.Init.Prescaler = 400;
	htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim1.Init.Period = 100;
	htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim1.Init.RepetitionCounter = 0;
	htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
	{
		Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
	{
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN TIM1_Init 2 */

	/* USER CODE END TIM1_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

	/* USER CODE BEGIN TIM2_Init 0 */

	/* USER CODE END TIM2_Init 0 */

	TIM_ClockConfigTypeDef sClockSourceConfig = { 0 };
	TIM_MasterConfigTypeDef sMasterConfig = { 0 };

	/* USER CODE BEGIN TIM2_Init 1 */

	/* USER CODE END TIM2_Init 1 */
	htim2.Instance = TIM2;
	htim2.Init.Prescaler = 7135;
	htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim2.Init.Period = 100;
	htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
	{
		Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
	{
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN TIM2_Init 2 */

	/* USER CODE END TIM2_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

	/* USER CODE BEGIN TIM3_Init 0 */

	/* USER CODE END TIM3_Init 0 */

	TIM_ClockConfigTypeDef sClockSourceConfig = { 0 };
	TIM_MasterConfigTypeDef sMasterConfig = { 0 };

	/* USER CODE BEGIN TIM3_Init 1 */

	/* USER CODE END TIM3_Init 1 */
	htim3.Instance = TIM3;
	htim3.Init.Prescaler = 7135;
	htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim3.Init.Period = 100;
	htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
	{
		Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
	{
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN TIM3_Init 2 */

	/* USER CODE END TIM3_Init 2 */

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

	/* USER CODE BEGIN TIM4_Init 0 */

	/* USER CODE END TIM4_Init 0 */

	TIM_ClockConfigTypeDef sClockSourceConfig = { 0 };
	TIM_MasterConfigTypeDef sMasterConfig = { 0 };

	/* USER CODE BEGIN TIM4_Init 1 */

	/* USER CODE END TIM4_Init 1 */
	htim4.Instance = TIM4;
	htim4.Init.Prescaler = 7200;
	htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim4.Init.Period = 10;
	htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
	{
		Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
	{
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN TIM4_Init 2 */

	/* USER CODE END TIM4_Init 2 */

}

/**
  * @brief TIM12 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM12_Init(void)
{

	/* USER CODE BEGIN TIM12_Init 0 */

	/* USER CODE END TIM12_Init 0 */

	TIM_ClockConfigTypeDef sClockSourceConfig = { 0 };

	/* USER CODE BEGIN TIM12_Init 1 */

	/* USER CODE END TIM12_Init 1 */
	htim12.Instance = TIM12;
	htim12.Init.Prescaler = 7200;
	htim12.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim12.Init.Period = 1000;
	htim12.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim12.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim12) != HAL_OK)
	{
		Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim12, &sClockSourceConfig) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN TIM12_Init 2 */

	/* USER CODE END TIM12_Init 2 */

}

/**
  * @brief UART4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_UART4_Init(void)
{

	/* USER CODE BEGIN UART4_Init 0 */

	/* USER CODE END UART4_Init 0 */

	/* USER CODE BEGIN UART4_Init 1 */

	/* USER CODE END UART4_Init 1 */
	huart4.Instance = UART4;
	huart4.Init.BaudRate = 9600;
	huart4.Init.WordLength = UART_WORDLENGTH_8B;
	huart4.Init.StopBits = UART_STOPBITS_1;
	huart4.Init.Parity = UART_PARITY_NONE;
	huart4.Init.Mode = UART_MODE_TX_RX;
	huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart4.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart4) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN UART4_Init 2 */

	/* USER CODE END UART4_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

	/* USER CODE BEGIN USART1_Init 0 */

	/* USER CODE END USART1_Init 0 */

	/* USER CODE BEGIN USART1_Init 1 */

	/* USER CODE END USART1_Init 1 */
	huart1.Instance = USART1;
	huart1.Init.BaudRate = 9600;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart1) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN USART1_Init 2 */

	/* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

	/* USER CODE BEGIN USART2_Init 0 */

	/* USER CODE END USART2_Init 0 */

	/* USER CODE BEGIN USART2_Init 1 */

	/* USER CODE END USART2_Init 1 */
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart2) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN USART2_Init 2 */

	/* USER CODE END USART2_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

	/* USER CODE BEGIN USART3_Init 0 */

	/* USER CODE END USART3_Init 0 */

	/* USER CODE BEGIN USART3_Init 1 */

	/* USER CODE END USART3_Init 1 */
	huart3.Instance = USART3;
	huart3.Init.BaudRate = 9600;
	huart3.Init.WordLength = UART_WORDLENGTH_8B;
	huart3.Init.StopBits = UART_STOPBITS_1;
	huart3.Init.Parity = UART_PARITY_NONE;
	huart3.Init.Mode = UART_MODE_TX_RX;
	huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart3.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart3) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN USART3_Init 2 */

	/* USER CODE END USART3_Init 2 */

}

/**
  * @brief USART6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART6_UART_Init(void)
{

	/* USER CODE BEGIN USART6_Init 0 */

	/* USER CODE END USART6_Init 0 */

	/* USER CODE BEGIN USART6_Init 1 */

	/* USER CODE END USART6_Init 1 */
	huart6.Instance = USART6;
	huart6.Init.BaudRate = 9600;
	huart6.Init.WordLength = UART_WORDLENGTH_8B;
	huart6.Init.StopBits = UART_STOPBITS_1;
	huart6.Init.Parity = UART_PARITY_NONE;
	huart6.Init.Mode = UART_MODE_TX_RX;
	huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart6.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart6) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN USART6_Init 2 */

	/* USER CODE END USART6_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOE, EEPROM_WP_Pin | EEPROM_A1_Pin | EEPROM_A0_Pin | Valve1_Pin
		| Valve2_Pin | Valve3_Pin | PWM_Pin | SPI2_PWR_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOF, LED_CLK_Pin | LED_DATA_Pin | Buzzer3_Pin | Buzzer4_Pin
		| Alarm_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(RSPY2_GPIO_Port, RSPY2_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOD, Buzzer1_Pin | Buzzer2_Pin | LED0_Pin | LED1_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOG, LED2_Pin | LED3_Pin | LED4_Pin | LED5_Pin
		| LED6_Pin | LED7_Pin | DR2_Pin | DR3_Pin
		| DR4_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(RS485_EN_GPIO_Port, RS485_EN_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pins : EEPROM_WP_Pin EEPROM_A1_Pin EEPROM_A0_Pin Valve1_Pin
							 Valve2_Pin Valve3_Pin PWM_Pin SPI2_PWR_Pin */
	GPIO_InitStruct.Pin = EEPROM_WP_Pin | EEPROM_A1_Pin | EEPROM_A0_Pin | Valve1_Pin
		| Valve2_Pin | Valve3_Pin | PWM_Pin | SPI2_PWR_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	/*Configure GPIO pins : LED_CLK_Pin LED_DATA_Pin Buzzer3_Pin Buzzer4_Pin
							 Alarm_Pin */
	GPIO_InitStruct.Pin = LED_CLK_Pin | LED_DATA_Pin | Buzzer3_Pin | Buzzer4_Pin
		| Alarm_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

	/*Configure GPIO pin : RSPY1_Pin */
	GPIO_InitStruct.Pin = RSPY1_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(RSPY1_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pin : RSPY2_Pin */
	GPIO_InitStruct.Pin = RSPY2_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(RSPY2_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : Buzzer1_Pin Buzzer2_Pin LED0_Pin LED1_Pin */
	GPIO_InitStruct.Pin = Buzzer1_Pin | Buzzer2_Pin | LED0_Pin | LED1_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	/*Configure GPIO pins : LED2_Pin LED3_Pin LED4_Pin LED5_Pin
							 LED6_Pin LED7_Pin DR2_Pin */
	GPIO_InitStruct.Pin = LED2_Pin | LED3_Pin | LED4_Pin | LED5_Pin
		| LED6_Pin | LED7_Pin | DR2_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

	/*Configure GPIO pins : PG8 DR1_Pin */
	GPIO_InitStruct.Pin = GPIO_PIN_8 | DR1_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

	/*Configure GPIO pin : RS485_EN_Pin */
	GPIO_InitStruct.Pin = RS485_EN_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(RS485_EN_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pin : PG9 */
	GPIO_InitStruct.Pin = GPIO_PIN_9;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

	/*Configure GPIO pin : PG10 */
	GPIO_InitStruct.Pin = GPIO_PIN_10;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

	/*Configure GPIO pin : DR3_Pin */
	GPIO_InitStruct.Pin = DR3_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(DR3_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pin : DR4_Pin */
	GPIO_InitStruct.Pin = DR4_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(DR4_GPIO_Port, &GPIO_InitStruct);

	/* EXTI interrupt init*/
	HAL_NVIC_SetPriority(EXTI9_5_IRQn, 1, 0);
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

	HAL_NVIC_SetPriority(EXTI15_10_IRQn, 1, 0);
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 4 */

void decode_raspi_packet()
{
	int data_lenth = rspy_receive_buffer[1];

	if (data_lenth > MAX_BUFFER_SIZE)
	{
		return;
	}

	if (rspy_receive_buffer[0] == 0xFE && rspy_receive_buffer[1] >= 1 && rspy_receive_buffer[data_lenth + 6 - 2] == 0xFF && rspy_receive_buffer[data_lenth + 6 - 1] == 0x0A)
	{
		uint16_t recieved_crc = rspy_receive_buffer[data_lenth + 6 - 4] * 256 + rspy_receive_buffer[data_lenth + 6 - 3];

		for (int i = 0; i < data_lenth; i++)
		{
			rspy_receive_buffer_Data[i] = rspy_receive_buffer[i + 2];
		}

		uint16_t calc_crc = crc_calc(rspy_receive_buffer_Data, data_lenth);

		if (calc_crc == recieved_crc)
		{

			if (rspy_receive_buffer[2] == 0x6E) //  Check System Function
			{
				CURRENT_MODE = STOP;

				if (rspy_receive_buffer[3] == 0x01)
				{
					check_devices();
				}

				if (turbo_error || pressure_s1_error || pressure_s2_error || flow_s1_error || flow_s2_error || buzzer_error)
					create_checking_signal_for_raspberry(0x6E, 1, turbo_error, pressure_s1_error, pressure_s2_error, flow_s1_error, flow_s2_error, buzzer_error);
				else
					create_checking_signal_for_raspberry(0x6E, 0, 0, 0, 0, 0, 0, 0);
			}
			else if (rspy_receive_buffer[2] == 0x00) //  SET Standby MODE Function
			{
				cnt_temp = 0;
				CURRENT_MODE = STANDBY;
				status(LED_ACP, 0);  //MODE LED OFF
				status(LED_ACV1, 0);  //MODE LED OFF
				status(LED_ACV2, 0);  //MODE LED OFF
				status(LED_SIMV, 0);  //MODE LED OFF
				status(LED_PSV, 0);  //MODE LED OFF


				status(LED_STANDBY1, 1);  //Mode led STANDBY on
				status(LED_STANDBY2, 1);  //Mode led STANDBY on
				t3_counter = duration_Ins;

				duration_Ins = 500;
				duration_Exp = 500;
				turbo_speed_Ins = 1, turbo_speed_Exp = 1;
				create_response_for_raspberry(0, 0);

			}
			else if (rspy_receive_buffer[2] == 0x04) //  SET STOP MODE Function
			{
				cnt_temp = 0;
				CURRENT_MODE = STOP;
				status(LED_ACP, 0);  //MODE LED OFF
				status(LED_ACV1, 0);  //MODE LED OFF
				status(LED_ACV2, 0);  //MODE LED OFF
				status(LED_SIMV, 0);  //MODE LED OFF
				status(LED_PSV, 0);  //MODE LED OFF


				status(LED_STANDBY1, 1);  //Mode led STANDBY on
				status(LED_STANDBY2, 1);  //Mode led STANDBY on

				t3_counter = duration_Ins;

				duration_Ins = 500;
				duration_Exp = 500;
				turbo_speed_Ins = 1, turbo_speed_Exp = 1;
				create_response_for_raspberry(4, 0);

			}
			else if (rspy_receive_buffer[2] == 0x01) //  SET Date and Time Function
			{

				create_response_for_raspberry(1, 0);
				date_time_decoder();
			}
			else if (rspy_receive_buffer[2] == 0x02) //  SET MODE Function
			{
				is_inspiratory = 0;
				cnt_temp = 0;
				ACV_Vt_Sens = 0;
				ACP_Vt_Sens = 0;
				SIMV_Vt_Sens = 0;
				PSV_Vt_Sens = 0;
				status(LED_ACP, 0);  //MODE LED OFF
				status(LED_ACV1, 0);  //MODE LED OFF
				status(LED_ACV2, 0);  //MODE LED OFF
				status(LED_SIMV, 0);  //MODE LED OFF
				status(LED_PSV, 0);  //MODE LED OFF


				status(LED_STANDBY1, 0);  //Mode led STANDBY OFF
				status(LED_STANDBY2, 0);  //Mode led STANDBY OFF
				send_report = false;
				sigh_occured = false;
				sigh_counter = 0;

				if (rspy_receive_buffer[3] == 0x01)    // PSV MODE
				{

					CURRENT_MODE = PSV;
					status(LED_PSV, 1);     //Mode led PSV on
					t3_counter = duration_Ins;
					PSV_MODE_STEP = 2;
					is_inspiratory = 0;
					PSV_MODE_INS = false;

					psv_mode_decoder();

					create_response_for_raspberry(2, 1);

				}
				else if (rspy_receive_buffer[3] == 0x02)   //ACP MODE
				{
					CURRENT_MODE = ACP;
					status(LED_ACP, 1);     //Mode led ACP on
					t3_counter = duration_Ins;

					acp_mode_decoder();
					create_response_for_raspberry(2, 2);
				}
				else if (rspy_receive_buffer[3] == 0x03)   // ACV MODE
				{
					CURRENT_MODE = ACV;
					status(LED_ACV1, 1);     //Mode led ACV on
					status(LED_ACV2, 1);     //Mode led ACV on
					sigh_counter = 0;
					t3_counter = duration_Ins;
					acv_mode_decoder();
					create_response_for_raspberry(2, 3);
				}
				else if (rspy_receive_buffer[3] == 0x04)  // SIMV MODE
				{

					CURRENT_MODE = SIMV;
					status(LED_SIMV, 1);     //Mode led SIMV on
					t3_counter = duration_Ins;

					simv_mode_decoder();
					create_response_for_raspberry(2, 4);
				}
				else
				{
					// Nothing		
				  // Received Data MODE Error!!!!					   
				}
			}
			else if (rspy_receive_buffer[2] == 0x03) //  SET ALARM Function
			{
				if (rspy_receive_buffer[3] == 0x01)    // PSV ALARM
				{
					psv_alarm_decoder();
					create_response_for_raspberry(3, 1);
				}
				else if (rspy_receive_buffer[3] == 0x02)   //ACP ALARM
				{
					pcv_alarm_decoder();
					create_response_for_raspberry(3, 2);
				}
				else if (rspy_receive_buffer[3] == 0x03)   // ACV ALARM
				{
					acv_alarm_decoder();
					create_response_for_raspberry(3, 3);
				}
				else if (rspy_receive_buffer[3] == 0x04)  // SIMV ALARM
				{
					simv_alarm_decoder();
					create_response_for_raspberry(3, 4);
				}
				else
				{
					// Nothing		
				  // Received Data ALARM Error!!!!
				}
			}
			else if (rspy_receive_buffer[2] == 0x06) //  Received STOP ALARM Function
			{
				cnt_temp = 0;
				buzzer(2, 0);
				//				status(LED_ALARM_Hi, 0);  //  ALARM Hi LED OFF
				//				status(LED_ALARM_Low, 0);  //  ALARM Low LED OFF

			}
		}
		else
		{
			// Nothing		
		  // Received CRC Error!!!!
		}
	}
}



// BEGIN OF CREATE RESPONSE FOR RASPBERRY

void create_checking_signal_for_raspberry(int function_id, int param_id, bool tubo, bool sp1, bool sp2, bool flow1, bool flow2, bool bz)
{
	uint8_t response[15];

	response[0] = 0xFE;
	response[1] = 0x08;
	if (packet_index > 50000)
		packet_index = 1;
	response[2] = packet_index++;    //packect Index 
	response[3] = function_id;
	response[4] = param_id;
	response[5] = tubo;
	response[6] = sp1;
	response[7] = sp2;
	response[8] = flow1;
	response[9] = flow2;
	response[10] = bz;
	{
		uint8_t dt[8];
		dt[0] = response[3];  dt[1] = response[4];
		dt[2] = response[5];  dt[3] = response[6];
		dt[4] = response[7];  dt[5] = response[8];
		dt[6] = response[9];  dt[7] = response[10];

		uint16_t resp_crc = crc_calc(dt, response[1]);
		if (resp_crc <= 256)
		{
			response[11] = 0x00;
			response[12] = resp_crc;
		}
		else
		{
			response[11] = (int)resp_crc / 256;
			response[12] = resp_crc % 256;
		}
	}
	response[13] = 0xFF;
	response[14] = 0x0A;



	send_rspy(response, 15);
}


void create_response_for_raspberry(int function_id, int param_id)
{
	uint8_t response[9];

	response[0] = 0xFE;
	response[1] = 0x02;
	if (packet_index > 50000)
		packet_index = 1;
	response[2] = packet_index++;    //packect Index 	
	response[3] = function_id;
	response[4] = param_id;
	{
		uint8_t dt[2];
		dt[0] = response[3];  dt[1] = response[4];
		uint16_t resp_crc = crc_calc(dt, response[1]);
		if (resp_crc <= 256)
		{
			response[5] = 0x00;
			response[6] = resp_crc;
		}
		else
		{
			response[5] = (int)resp_crc / 256;
			response[6] = resp_crc % 256;
		}
	}
	response[7] = 0xFF;
	response[8] = 0x0A;

	send_rspy(response, 9);

}

void create_report_for_raspberry(int function_id, int pressure, int flow, int volume, int palsOxi, int o2)
{
	uint8_t response[21];

	//	if(max_flow1<=volume)
	//				max_flow1=volume;
	//	
	//	if(max_flow2<=ACV_Vt_Sens_Ins)
	//				max_flow2=ACV_Vt_Sens_Ins;
	//	
	//	  	sprintf(buf, "turbo_speed=%d - pressure= %d  flow=%d - volume=%d -max-Vol=%d ,max-SENS=%d \r\n",turbo_speed_Ins, pressure, flow,volume,max_flow1,max_flow2);		 
	//		   print_debug((uint8_t *)buf, strlen(buf));

	response[0] = 0xFE;
	response[1] = 0x0F;  // len
	response[2] = function_id;
	if (pressure < 0)
	{
		response[3] = 0xFF;
		response[4] = (-1) * pressure;
	}
	else
	{
		response[3] = 0x00;
		response[4] = pressure;
	}
	if (flow < 0)
	{
		response[5] = 0xFF;
		flow = flow * (-1);
		response[6] = (int)flow / 256;
		response[7] = flow % 256;
	}
	else
	{
		response[5] = 0x00;
		response[6] = (int)flow / 256;
		response[7] = flow % 256;
	}

	if (volume < 0)
	{
		response[8] = 0xFF;
		volume = volume * (-1);
		response[9] = (int)volume / 256;
		response[10] = volume % 256;
	}
	else
	{
		response[8] = 0x00;
		response[9] = (int)volume / 256;
		response[10] = volume % 256;
	}
	if (palsOxi < 0)
	{
		response[11] = 0xFF;
		palsOxi = palsOxi * (-1);
		response[12] = (int)palsOxi / 256;
		response[13] = palsOxi % 256;
	}
	else
	{
		response[11] = 0x00;
		response[12] = (int)palsOxi / 256;
		response[13] = palsOxi % 256;
	}
	if (o2 < 0)
	{
		response[14] = 0xFF;
		palsOxi = palsOxi * (-1);
		response[15] = (int)o2 / 256;
		response[16] = o2 % 256;
	}
	else
	{
		response[14] = 0x00;
		response[15] = (int)o2 / 256;
		response[16] = o2 % 256;
	}
	{
		uint8_t dt[15];
		dt[0] = response[2];   dt[1] = response[3];
		dt[2] = response[4];   dt[3] = response[5];
		dt[4] = response[6];   dt[5] = response[7];
		dt[6] = response[8];   dt[7] = response[9];
		dt[8] = response[10];  dt[9] = response[11];
		dt[10] = response[12];  dt[11] = response[13];
		dt[12] = response[14];  dt[11] = response[15];
		dt[14] = response[16];

		uint16_t resp_crc = crc_calc(dt, response[1]);
		if (resp_crc <= 256)
		{
			response[17] = 0x00;
			response[18] = resp_crc;
		}
		else
		{
			response[17] = (int)resp_crc / 256;
			response[18] = resp_crc % 256;
		}
	}
	response[19] = 0xFF;
	response[20] = 0x0A;

	send_rspy(response, 21);

}

// END OF CREATE RESPONSE FOR RASPBERRY

//  BEGIN OF DATE and TIME Packet DECODER

void date_time_decoder()
{
	int YYh = rspy_receive_buffer[3];
	int YYl = rspy_receive_buffer[4];
	int MM = rspy_receive_buffer[5];
	int DD = rspy_receive_buffer[6];
	int hh = rspy_receive_buffer[7];
	int mm = rspy_receive_buffer[8];
	int ss = rspy_receive_buffer[9];

	//int date=YYh*1000000+YYl*10000+MM*100+DD;
}

//  END OF DATE and TIME Packet DECODER



uint16_t crc_calc(const uint8_t* data, uint8_t data_size)
{
	uint16_t crc = 0xFFFF;
	for (int i = 0; i < data_size; i++)
	{
		crc = ((CrcTable[(crc ^ data[i]) & 0xFF]) ^ (crc >> 8)) & 0xFFFF;
	}

	return crc;
}
void send_rspy(uint8_t* data, int size)
{
	//HAL_UART_Transmit_IT(&huart2, data, size);

	send_complete = false;

	for (int i = 0; i < size; i++)
	{
		//HAL_UART_Transmit_IT(&huart2, data+i, 1);
		HAL_UART_Transmit(&huart2, data + i, 1, 100);
		//HAL_Delay(10);
	}

	send_complete = true;
	paceket_decoded = true;
}



void print_debug(uint8_t* data, int size)
{
	HAL_UART_Transmit(&huart1, data, size, 1000);
	//HAL_UART_Transmit(&huart1, (uint8_t *)"\n", 2, 1000);
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */

	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
	/* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
	   tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	   /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
