
#include "check_device_init.h"
#include "stdbool.h"

extern int turbo_speed_Ins,turbo_speed_Exp,turbo_speed;
extern bool turbo_error,pressure_s1_error,pressure_s2_error,flow_s1_error,flow_s2_error,buzzer_error;

int sum_check=0;
		 
void check_devices()                 /////////////////////// ALARM CHECK
{
	

	  
	   turbo_speed_Ins=12,turbo_speed_Exp=12;
     HAL_Delay(5000);
	
	   buzzer(2,1);
	
	   if(turbo_speed==0)
		 {
			 turbo_error=true;		
		 }
		 turbo_speed_Ins=0,turbo_speed_Exp=0;
		 
		   sum_check=0;
		   sum_check+=pressure(1);
		   sum_check+=pressure(1);
       sum_check+=pressure(1);
       sum_check+=pressure(1);
       sum_check+=pressure(1);
       sum_check+=pressure(1);
       sum_check+=pressure(1);
       sum_check+=pressure(1);
       sum_check+=pressure(1);
       sum_check+=pressure(1);
		
	   
		 
		 if((sum_check/10)<-1)
		 {
			  pressure_s1_error=true;		
		 }
		 	sum_check=0;
		  sum_check+=pressure(2);
		  sum_check+=pressure(2);
      sum_check+=pressure(2);
      sum_check+=pressure(2);
      sum_check+=pressure(2);
      sum_check+=pressure(2);
      sum_check+=pressure(2);
      sum_check+=pressure(2);
      sum_check+=pressure(2);
      sum_check+=pressure(2);
		
	  
		 
		 if((sum_check/10)<-1)
		 {
			  pressure_s2_error=true;		
		 }

		  sum_check=0;
		  sum_check+=flow(1);
		  sum_check+=flow(1);
      sum_check+=flow(1);
      sum_check+=flow(1);
      sum_check+=flow(1);
      sum_check+=flow(1);
      sum_check+=flow(1);
      sum_check+=flow(1);
      sum_check+=flow(1);
      sum_check+=flow(1);
				 
		 if(sum_check/100<-1)
		 {
			  flow_s1_error=true;		
		 }
		 
		 
		  sum_check=0;
		  sum_check+=flow(2);
		  sum_check+=flow(2);
      sum_check+=flow(2);
      sum_check+=flow(2);
      sum_check+=flow(2);
      sum_check+=flow(2);
      sum_check+=flow(2);
      sum_check+=flow(2);
      sum_check+=flow(2);
      sum_check+=flow(2);
		
	  
		 
		 if(sum_check/100<-1)
		 {
			  flow_s2_error=true;		
		 }
		 
		 if (HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_8))
			buzzer_error = true;
		else
			buzzer_error = false;
		 
		 buzzer(2,0);
}

