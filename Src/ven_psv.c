#include "ven_psv.h"

void start_psv_mode()
{
		
			   int start_command=rspy_receive_buffer[3];
	       if(start_command==0x01)
					{
  				 char buf[50];
	  			 sprintf(buf, "\r\n START PSV MODE ....\r\n");
		  		 print_debug((uint8_t *)buf, strlen(buf));
						
					 int i=8;	
					 while(1)
					 {				
						 if(CURRENT_MODE==STANDBY)						 
             {
							 char buf[50];
	  			     sprintf(buf, "\r\n START PSV MODE TO STANDBY....\r\n");
		  		     print_debug((uint8_t *)buf, strlen(buf));
							 
							 break;
						 }
							 
					   turbo(10*i);
						 HAL_Delay(3000);
						 turbo(20);
						 HAL_Delay(6000);
						 i--;
						 if(i==3)
							 i=8;
					 }
					}
					else
					{
						 char buf[50];					
					   sprintf(buf, "%s","\r\n START PSV MODE DATA Error!!!!\r\n");						
					   print_debug((uint8_t *)buf, 18);
					}
					

}
