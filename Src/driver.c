#include "driver.h"
#include "main.h"


extern ADC_HandleTypeDef hadc3;
extern TIM_OC_InitTypeDef sConfigOC;

extern ADC_HandleTypeDef hadc3;

extern DAC_HandleTypeDef hdac;

extern I2C_HandleTypeDef hi2c1;
extern I2C_HandleTypeDef hi2c2;

extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi2;

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim12;

extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart6;




unsigned char b[5];

int s,i=0,pwm=10;
float ans=0;
int sw2 = 0;
int speed =0;
extern int e,st[],status_bar;
extern bool status_change_falg;


void ADC_CNL(int x)
{
	ADC_ChannelConfTypeDef sConfig = {0};
	hadc3.Instance = ADC3;
  hadc3.Init.ScanConvMode = DISABLE;
  hadc3.Init.ContinuousConvMode = DISABLE;
  hadc3.Init.DiscontinuousConvMode = DISABLE;
  hadc3.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc3.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc3.Init.NbrOfConversion = 1;
  if (HAL_ADC_Init(&hadc3) != HAL_OK)
  {
    Error_Handler();
  }
	switch(x)
	{
		case 4 :	sConfig.Channel = ADC_CHANNEL_4;	break;
		case 5 :	sConfig.Channel = ADC_CHANNEL_5;	break;
		case 6 :	sConfig.Channel = ADC_CHANNEL_6;	break;
		case 8 :	sConfig.Channel = ADC_CHANNEL_8;	break;
		case 9 :	sConfig.Channel = ADC_CHANNEL_9;	break;
		case 10 :	sConfig.Channel = ADC_CHANNEL_10;	break;
		case 11 :	sConfig.Channel = ADC_CHANNEL_11;	break;
	}
		
	sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
	
}



int ADC_READ(int x)
{
	int value = 0;
	ADC_CNL(x);
  HAL_ADC_Stop(&hadc3);
	hadc3.Init.NbrOfConversion=2;
  HAL_ADC_Init(&hadc3);
  HAL_ADC_Start(&hadc3);
	if(HAL_ADC_PollForConversion(&hadc3,500)== HAL_OK)
	{
		value = HAL_ADC_GetValue(&hadc3);
  }
	return value;	
	
}

void led(int x,int y)
{
	if (y==1)
	{
		switch (x)
		{
			case 1:	HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_SET);	break;
			case 2:	HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);	break;
			case 3:	HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);	break;
			case 4:	HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET);	break;
			case 5:	HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_SET);	break;
			case 6:	HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, GPIO_PIN_SET);	break;
			case 7:	HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin, GPIO_PIN_SET);	break;
			case 8:	HAL_GPIO_WritePin(LED7_GPIO_Port, LED7_Pin, GPIO_PIN_SET);	break;
	
		}
	}
	else
	{
		switch (x)
		{
			case 1:	HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_RESET);	break;
			case 2:	HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);	break;
			case 3:	HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);	break;
			case 4:	HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_RESET);	break;
			case 5:	HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_RESET);	break;
			case 6:	HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, GPIO_PIN_RESET);	break;
			case 7:	HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin, GPIO_PIN_RESET);	break;
			case 8:	HAL_GPIO_WritePin(LED7_GPIO_Port, LED7_Pin, GPIO_PIN_RESET);	break;

		}
	}
}

int bcd2bin(int bcd)
{
	int bin = (bcd >> 4) * 10;
	bin += bcd & 0x0F;
	
	return bin;
}


void turbo(int x)
{
	if((pwm+e)>x)
		pwm = x;
	else
		pwm = pwm+e;
}
void turbo_break(int x)
{
		HAL_GPIO_WritePin(DR3_GPIO_Port, DR3_Pin, x);
}
void driver_init(void)
{	
	for(i=1;i<status_bar+2;i++)
	{
		st[i] = 0;
		status(i,st[i]);
	}



	turbo(0);
	HAL_TIM_Base_Start_IT(&htim1);
	HAL_TIM_Base_Start_IT(&htim2);
	HAL_TIM_Base_Start_IT(&htim3);
	HAL_TIM_Base_Start_IT(&htim12);
	
	HAL_GPIO_WritePin(DR3_GPIO_Port, DR3_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(DR4_GPIO_Port, DR4_Pin, GPIO_PIN_SET);
	HAL_Delay(30);
	HAL_GPIO_WritePin(DR4_GPIO_Port, DR4_Pin, GPIO_PIN_RESET);
	HAL_Delay(30);
	HAL_GPIO_WritePin(DR4_GPIO_Port, DR4_Pin, GPIO_PIN_SET);
	
}
void buzzer(int x,int y)
{
	if(y==1)
	{
		switch (x)
		{
			case 1:	HAL_GPIO_WritePin(Buzzer1_GPIO_Port, Buzzer1_Pin, GPIO_PIN_SET)	;	break;
			case 2:	HAL_GPIO_WritePin(Buzzer2_GPIO_Port, Buzzer2_Pin, GPIO_PIN_SET)	;	break;
			case 3:	HAL_GPIO_WritePin(Buzzer3_GPIO_Port, Buzzer3_Pin, GPIO_PIN_SET)	;	break;
			case 4:	HAL_GPIO_WritePin(Buzzer4_GPIO_Port, Buzzer4_Pin, GPIO_PIN_SET)	;	break;
		}
	}
	else
	{
	switch (x)
		{
			case 1:	HAL_GPIO_WritePin(Buzzer1_GPIO_Port, Buzzer1_Pin, GPIO_PIN_RESET);	break;
			case 2:	HAL_GPIO_WritePin(Buzzer2_GPIO_Port, Buzzer2_Pin, GPIO_PIN_RESET);	break;
			case 3:	HAL_GPIO_WritePin(Buzzer3_GPIO_Port, Buzzer3_Pin, GPIO_PIN_RESET);	break;
			case 4:	HAL_GPIO_WritePin(Buzzer4_GPIO_Port, Buzzer4_Pin, GPIO_PIN_RESET);	break;
		}
	}
		
	
}
void flash(int x,int y)
{
	
	
	
}

void delay(int x)
{
	int microseconds,i=0;
	microseconds *= (HAL_RCC_GetHCLKFreq() / 1000000);
	while (i < microseconds)
	{
		i++;
	}
	
}

int sec(void)
{
		b[0]=0; 		
		HAL_I2C_Master_Transmit(&hi2c1,0x68<<1,b,1,100);  		
		HAL_I2C_Master_Receive(&hi2c1,0x68<<1,b,1,100);  
		s = bcd2bin(b[0]);
		return s;

}
int min(void)
{
		b[0]=1; 		
		HAL_I2C_Master_Transmit(&hi2c1,0x68<<1,b,1,100);  		
		HAL_I2C_Master_Receive(&hi2c1,0x68<<1,b,1,100);  
		s = bcd2bin(b[0]);
		return s;

}
int hour(void)
{
		b[0]=2; 		
		HAL_I2C_Master_Transmit(&hi2c1,0x68<<1,b,1,100);  		
		HAL_I2C_Master_Receive(&hi2c1,0x68<<1,b,1,100);  
		s = bcd2bin(b[0]);
		return s;

}
int day(void)
{
		b[0]=3; 		
		HAL_I2C_Master_Transmit(&hi2c1,0x68<<1,b,1,100);  		
		HAL_I2C_Master_Receive(&hi2c1,0x68<<1,b,1,100);  
		s = bcd2bin(b[0]);
		return s;

}
int month(void)
{
		b[0]=4; 		
		HAL_I2C_Master_Transmit(&hi2c1,0x68<<1,b,1,100);  		
		HAL_I2C_Master_Receive(&hi2c1,0x68<<1,b,1,100);  
		s = bcd2bin(b[0]);
		return s;

}




float pressure(int x)
{
	switch (x)
	{
		case 1 :	i = ADC_READ(8);	break;
		case 2 :	i = ADC_READ(6);	break;
		case 3 :	i = ADC_READ(10);	break;
	}
	ans = ((0.002717*i)-0.4125)*10;
	return ans;
}

float flow(int x)
{
	switch (x)
	{
		case 1 :	i = ADC_READ(11);	break;
		case 2 :	i = ADC_READ(4);	break;
		case 3 :	i = ADC_READ(5);	break;
	}
	ans = ((0.3419*i)-230)-250;
	return ans;
}


void status(int x,int y)
{
	st[x] = y;
	status_change_falg=true;
	
}

int year(void)
{
		b[0]=5; 		
		HAL_I2C_Master_Transmit(&hi2c1,0x68<<1,b,1,100);  		
		HAL_I2C_Master_Receive(&hi2c1,0x68<<1,b,1,100);  
		s = bcd2bin(b[0]);
		return s;

}

