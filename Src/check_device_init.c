
#include "check_device_init.h"
#include "stdbool.h"

extern int turbo_speed_Ins,turbo_speed_Exp,turbo_speed;
extern bool turbo_error,pressure_s1_error,pressure_s2_error,flow_s1_error,flow_s2_error,buzzer_error;
int k=0,l=0,m=0,n=0,o=0,p=0,q=0,r=0,sa=0,ta=0;
	   float sum=0;
		 
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
		 
		 sum=0;
		   k=pressure(1);
		   l=pressure(1);
       m=pressure(1);
       n=pressure(1);
       o=pressure(1);
       p=pressure(1);
       q=pressure(1);
       r=pressure(1);
       sa=pressure(1);
       ta=pressure(1);
		
	     sum=(k+l+m+n+o+p+q+r+sa+ta);
		 
		 if((sum/10)<-1)
		 {
			  pressure_s1_error=true;		
		 }
		 	 
		   k=pressure(2);
		   l=pressure(2);
       m=pressure(2);
       n=pressure(2);
       o=pressure(2);
       p=pressure(2);
       q=pressure(2);
       r=pressure(2);
       sa=pressure(2);
       ta=pressure(2);
		
	     sum=(k+l+m+n+o+p+q+r+sa+ta);
		 
		 if((sum/10)<-1)
		 {
			  pressure_s2_error=true;		
		 }

		   k=flow(1);
		   l=flow(1);
       m=flow(1);
       n=flow(1);
       o=flow(1);
       p=flow(1);
       q=flow(1);
       r=flow(1);
       sa=flow(1);
       ta=flow(1);
		
	    sum=(k+l+m+n+o+p+q+r+sa+ta);
		 
		 if(sum/100<-1)
		 {
			  flow_s1_error=true;		
		 }
		 
		   k=flow(2);
		   l=flow(2);
       m=flow(2);
       n=flow(2);
       o=flow(2);
       p=flow(2);
       q=flow(2);
       r=flow(2);
       sa=flow(2);
       ta=flow(2);
		
	     sum=(k+l+m+n+o+p+q+r+sa+ta);
		 
		 if(sum/100<-1)
		 {
			  flow_s2_error=true;		
		 }
		 
		 if (HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_8))
			buzzer_error = true;
		else
			buzzer_error = false;
		 
		 buzzer(2,0);
}

