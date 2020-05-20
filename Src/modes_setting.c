#include "modes_setting.h"


//  BEGIN OF MODE Packet DECODER
    
int psv_mode_decoder()
{
			   PSV_IPAP=rspy_receive_buffer[4];
	       PSV_EPAP=rspy_receive_buffer[5];
				 PSV_RISE_TIME=rspy_receive_buffer[6];
				 PSV_TRRIG_I=rspy_receive_buffer[7];
				 PSV_BUR=rspy_receive_buffer[8];
				 PSV_Apnea=rspy_receive_buffer[9];
			   PSV_MAXP=rspy_receive_buffer[10];
				 int TRIIG_E_Sign=rspy_receive_buffer[11];
				 int TRIIG_E=rspy_receive_buffer[12];
			
				 if(TRIIG_E_Sign==255)
					 PSV_TRIIG_E=-1*TRIIG_E;
				 else
					 PSV_TRIIG_E=TRIIG_E;
							 
         int PSV_Target_Vt=rspy_receive_buffer[13]*16+rspy_receive_buffer[14];			
  
			 
				   return 0;
}

void pcv_mode_decoder()
{
	PCV_IPAP=rspy_receive_buffer[4];
	       PCV_EPAP=rspy_receive_buffer[5];
				 PCV_RISE_TIME=rspy_receive_buffer[6];
				 PCV_RATE=rspy_receive_buffer[7];
				 PCV_IT_RATIO=rspy_receive_buffer[8];
				 PCV_Inspiratory=rspy_receive_buffer[9]; 
				 PCV_Expiratory=rspy_receive_buffer[10];
			   PCV_TRRIG_I=rspy_receive_buffer[11];
			   PCV_MAXP=rspy_receive_buffer[12];

         PCV_Target_Vt=rspy_receive_buffer[13]*16+rspy_receive_buffer[14];			
  
				 char buf[50];
				 sprintf(buf, "PCV - IPAP=%d , EPAP=%d , RISE_TIME=%d ,  RATE=%d , IT_RATIO=%d , Inspiratory=%d , Expiratory=%d ,TRRIG_I=%d , MAXP=%d , Target_Vt=%d  %s", PCV_IPAP,PCV_EPAP, PCV_RISE_TIME, PCV_RATE, PCV_IT_RATIO, PCV_Inspiratory, PCV_Expiratory,PCV_TRRIG_I,PCV_MAXP,PCV_Target_Vt ,"\r\n");
				 print_debug((uint8_t *)buf, strlen(buf));
}

void acv_mode_decoder()
{
			    ACV_EPAP=rspy_receive_buffer[4];
	        ACV_RAMP=rspy_receive_buffer[5];
				  ACV_RATE=rspy_receive_buffer[6];
				  ACV_IT_RATIO=rspy_receive_buffer[7];
				  ACV_Inspiratory=rspy_receive_buffer[8]; 
				  ACV_Expiratory=rspy_receive_buffer[9];
			    ACV_TRRIG_I=rspy_receive_buffer[10];
				 int Vt_Sigh_I=rspy_receive_buffer[11];
				 int Vt_Sigh_F=rspy_receive_buffer[12];
			   ACV_Vt_Sigh=Vt_Sigh_I+(Vt_Sigh_F/10);
				 
				 ACV_MAXP=rspy_receive_buffer[13];

          ACV_Sigh_Rate=rspy_receive_buffer[14]*16+rspy_receive_buffer[15];			
				  ACV_Vt=rspy_receive_buffer[16]*16+rspy_receive_buffer[17];
  
				 char buf[50];
				 sprintf(buf, "ACV - EPAP=%d , RAMP=%d , RATE=%d , IT_RATIO=%d , Inspiratory=%d , Expiratory=%d ,TRRIG_I=%d , Vt_Sigh=%d/%d == %f, MAXP=%d , Sigh_Rate=%d , Vt=%d  %s", ACV_EPAP,ACV_RAMP, ACV_RATE,ACV_IT_RATIO, ACV_Inspiratory, ACV_Expiratory,ACV_TRRIG_I,Vt_Sigh_I,Vt_Sigh_F , ACV_Vt_Sigh,ACV_MAXP,ACV_Sigh_Rate,ACV_Vt ,"\r\n");
				 print_debug((uint8_t *)buf, strlen(buf));


}		
		
void simv_mode_decoder()
{
			    SIMV_IPAP=rspy_receive_buffer[5];
	        SIMV_EPAP=rspy_receive_buffer[6];
				  SIMV_RATE_SIMV=rspy_receive_buffer[7];
				  SIMV_IT_RATIO=rspy_receive_buffer[8];
				  SIMV_Inspiratory=rspy_receive_buffer[9]; 
				  SIMV_Expiratory=rspy_receive_buffer[10];
			    SIMV_TRRIG_I=rspy_receive_buffer[11];
				  SIMV_BUR=rspy_receive_buffer[12];
				  SIMV_Apnea=rspy_receive_buffer[13];
				  SIMV_Vt=rspy_receive_buffer[14]*16+rspy_receive_buffer[15];
  
				 char buf[50];
				 sprintf(buf, "SIMV - IPAP=%d , EPAP=%d , RATE_SIMV=%d ,  IT_RATIO=%d , Inspiratory=%d , Expiratory=%d ,TRRIG_I=%d , BUR=%d , Apnea=%d , Vt=%d  %s", SIMV_IPAP,SIMV_EPAP, SIMV_RATE_SIMV,SIMV_IT_RATIO, SIMV_Inspiratory, SIMV_Expiratory,SIMV_TRRIG_I,SIMV_BUR,SIMV_Apnea,SIMV_Vt ,"\r\n");
				 print_debug((uint8_t *)buf, strlen(buf));

}
    
//  END OF MODE Packet DECODER


