//=====================================================================================
//=================== PSV ST = PRESSURE SUPPORT VENTILATION SPONTANEOUS TIMED ===========
//=====================================================================================


#include "psv_mode.h"
#include "database.h"
#include "driver.h"

extern int PSV_IPAP,PSV_EPAP, PSV_RISE_TIME, PSV_TRRIG_I, PSV_BUR, PSV_Apnea,PSV_MAXP, PSV_TRIIG_E,PSV_Target_Vt;
extern int is_inspiratory;
extern int turbo_speed_Ins,turbo_speed_Exp,raise_step;
extern int duration_Ins,duration_Exp;
<<<<<<< HEAD
extern int Current_P1,Current_P2, Current_F1, Current_F2;
extern int t3_counter;

 int Tt_psv=0, Ti_psv=0, Te_psv=0, Tflat_psv=0, trs_step_psv=0, raise_step_psv=100;
 int Trs_psv=0;
 int PSV_IPAP_Sens=0, PSV_EPAP_Sens=0;
 int PSV_Fi_Sens=0, PSV_Fe_Sens=0, PSV_Qi_maxi=0;
 int pwm_i_psv=0, pwm_e_psv=0, pwm_max_psv=0;
 int Pe_Ad_psv=0, Pe_Pa_psv=0, Q_Pa_psv=0, Q_Ad_psv=0;
 float  Pe_psv= -4.7, Bias_Flow_psv=20.0;
 int start_ins_psv_mode=0, Flow=0, Maxi_Flow=0, counter_Maxi_Flow=0;


	
void PSV_Mode()
{
	     
	//Ti_psv=6000/PSV_BUR;
	Trs_psv=PSV_RISE_TIME*20;
//	PSV_Qi_maxi=PSV_Target_Vt/6000;
//	Ti_psv=300; 
//	
//	if (PSV_Fi_Sens==PSV_Qi_maxi)
//	{
//		if (((PSV_Fi_Sens-PSV_Qi_maxi)/PSV_Qi_maxi >= PSV_TRIIG_E) && PSV_IPAP_Sens)
//			Ti_psv=t3_counter;
//	}

=======
extern int Current_Pressure_Ins,Current_Pressure_Exp, Current_Flow_Ins, Current_Flow_Exp;
extern int t3_counter;
extern float Current_P_Triger;	

 int Tt_psv=0, Ti_psv=0, Te_psv=0, Tflat_psv=0, trs_step_psv=0, raise_step_psv=100;
 int Trs_psv=0;
 int PSV_Ins_Pressure=0, PSV_Exp_Pressure=0;
 int PSV_Ins_Flow=0, PSV_Exp_Flow=0, PSV_Qi_maxi=0;
 int pwm_i_psv=0, pwm_e_psv=0, pwm_max_psv=0;
 int Pe_Ad_psv=0, Pe_Pa_psv=0, Q_Pa_psv=0, Q_Ad_psv=0;
 float  Pe_psv= -1.7, Bias_Flow_psv=20.0,PSV_Exp_Pressure_Trriger=0.0;
 int start_ins_psv_mode=0, Maxi_Flow=1, counter_Maxi_Flow=0;

extern int PSV_Flow_MAXi_sens;
extern bool PSV_MODE_INS;


void PSV_Mode()
{
	     

	Trs_psv=PSV_RISE_TIME*20;
>>>>>>> c63a33440ac7da4f4de159016f77aa7bd58c3882
	
	pwm_max_psv=(PSV_MAXP/55.0)*100;
	pwm_i_psv=(PSV_IPAP/55.0)*100;
	pwm_e_psv=(PSV_EPAP/55.0)*100;
	
	Pe_Pa_psv=Pe_psv-0.3;
	Pe_Ad_psv=Pe_psv-0.3-0.1*PSV_TRRIG_I;
	Q_Pa_psv=Bias_Flow_psv+3.5;
	Q_Ad_psv=Bias_Flow_psv+4;

  duration_Ins=Ti_psv;
  duration_Exp=Te_psv;
	
//============================ Inspiratory Phase

<<<<<<< HEAD
if (start_ins_psv_mode==1)
{

   if(is_inspiratory==1)
    {	
		   	PSV_IPAP_Sens= Current_P1;
		    PSV_EPAP_Sens= Current_P2;
        PSV_Fi_Sens=Current_F1;      
	
        if (PSV_EPAP_Sens<=PSV_IPAP)   // for certainty that expiration is Done 
				   	{  	
	            	if ((PSV_IPAP_Sens-PSV_IPAP)<=pwm_i_psv)     // Delet negetive value of pwm
		              	pwm_i_psv=pwm_i_psv - (PSV_IPAP_Sens-PSV_IPAP);
=======

   if(is_inspiratory>0)
    {	
		   	PSV_Ins_Pressure= Current_Pressure_Ins;
		    PSV_Exp_Pressure= Current_Pressure_Exp;
        PSV_Ins_Flow=Current_Flow_Exp;      
	
        if (PSV_Exp_Pressure<=PSV_IPAP)   // for certainty that expiration is Done 
				   	{  	
	            	if ((PSV_Ins_Pressure-PSV_IPAP)<=pwm_i_psv)     // Delet negetive value of pwm
		              	pwm_i_psv=pwm_i_psv - (PSV_Ins_Pressure-PSV_IPAP);
>>>>>>> c63a33440ac7da4f4de159016f77aa7bd58c3882
	              else
			            	pwm_i_psv=pwm_i_psv;
						
	       turbo_speed_Ins=pwm_i_psv;
<<<<<<< HEAD
	       duration_Ins=Ti_psv;
=======
	      // duration_Ins=Ti_psv;
>>>>>>> c63a33440ac7da4f4de159016f77aa7bd58c3882
       	trs_step_psv=(int)(turbo_speed_Ins-turbo_speed_Exp)/(Trs_psv);
		  	if (trs_step_psv==0)
				  	trs_step_psv=1;
         raise_step=trs_step_psv;


<<<<<<< HEAD
         if (PSV_Fi_Sens>Flow)	
				 {
					 Flow=PSV_Fi_Sens;
				 }
				 else{
					    Maxi_Flow=PSV_Fi_Sens;
					    Flow=0;
					   counter_Maxi_Flow=t3_counter;
					   if(((Flow-Maxi_Flow)*100)/Maxi_Flow>= PSV_TRIIG_E)
				    	  {
						     start_ins_psv_mode=0;
=======
         if (PSV_Ins_Flow>PSV_Flow_MAXi_sens)	
				 {
					 PSV_Flow_MAXi_sens=PSV_Ins_Flow;
				 }
				 else{
					    
					    
					   counter_Maxi_Flow=t3_counter;
					 if(PSV_Flow_MAXi_sens>0)
					   if(((PSV_Flow_MAXi_sens-PSV_Ins_Flow)*100)/PSV_Flow_MAXi_sens>= (-1)*PSV_TRIIG_E)
				    	  {
						       PSV_MODE_INS=false;
									
>>>>>>> c63a33440ac7da4f4de159016f77aa7bd58c3882
					      }
				 }
				 
						
				   	}
			  		else
				  	{
<<<<<<< HEAD
							 	turbo_speed_Ins=10;
=======
							 PSV_MODE_INS=false;
							 	turbo_speed_Ins=12;
>>>>>>> c63a33440ac7da4f4de159016f77aa7bd58c3882
							  duration_Ins=Ti_psv;
				   	}
 
   }

<<<<<<< HEAD
}

//============================ Expiratory Phase
if (start_ins_psv_mode==0)
{
    if(is_inspiratory==0)
      {	

			    PSV_EPAP_Sens=Current_P2;
	        PSV_Fe_Sens=Current_F2;  
	
         if (PSV_TRRIG_I==1)
			     {
			     	    if((PSV_Fi_Sens>Q_Pa_psv) || (PSV_IPAP_Sens>Pe_Pa_psv))
			         	 {
					         t3_counter=duration_Ins+duration_Exp+1;
							  	 start_ins_psv_mode=1;
								 
		     	    	 }
							 else
						  	 {
								   if ((PSV_EPAP_Sens-PSV_EPAP)>pwm_e_psv)     //  Delet negetive value of pwm
								       pwm_e_psv=pwm_e_psv - (PSV_EPAP_Sens-PSV_EPAP);
									 else
									   	 pwm_e_psv= 0;
	
	          	  turbo_speed_Exp=pwm_e_psv;
	              duration_Exp=duration_Exp+1;
=======


//============================ Expiratory Phase

    if(is_inspiratory==0)
      {	

			    PSV_Exp_Pressure=Current_Pressure_Exp;
	        PSV_Exp_Flow=Current_Flow_Exp;  
	
				PSV_Exp_Pressure_Trriger=(-1.0)* Current_P_Triger;
				
				
         if (PSV_TRRIG_I==1)
			     {
			     	    if(/*(PSV_Ins_Flow>Q_Pa_psv) ||*/ (PSV_Exp_Pressure_Trriger<Pe_Pa_psv))
			         	 {
//					         t3_counter=duration_Ins+duration_Exp+1;
//							  	 start_ins_psv_mode=1;
									 
									 turbo_speed_Ins=pwm_i_psv;
								   PSV_MODE_INS=true;
		     	    	 }
							 else
						  	 {
//								   if ((PSV_Exp_Pressure-PSV_EPAP)>pwm_e_psv)     //  Delete negetive value of pwm
//								       pwm_e_psv=pwm_e_psv - (PSV_Exp_Pressure-PSV_EPAP);
//									 else
									   	 pwm_e_psv= 12;
	                  
	          	  turbo_speed_Exp=pwm_e_psv;
									  PSV_MODE_INS=false;
	           //   duration_Exp=duration_Exp+1;
>>>>>>> c63a33440ac7da4f4de159016f77aa7bd58c3882
								 }
				 
			 }
			 
			 else 
			 {
<<<<<<< HEAD
				     	 if((PSV_Fi_Sens>Q_Ad_psv) || (PSV_IPAP_Sens>Pe_Ad_psv))
			       	 {
					     	 t3_counter=duration_Ins+duration_Exp+1;;
								 start_ins_psv_mode=1;
								 
			      	 }
							 else
							 {
								 if ((PSV_EPAP_Sens-PSV_EPAP)>pwm_e_psv)  //   Delet negetive value of pwm
								     pwm_e_psv=pwm_e_psv - (PSV_EPAP_Sens-PSV_EPAP);
								 else
									 pwm_e_psv= 0;
	
	          	  turbo_speed_Exp=pwm_e_psv;
	              duration_Exp=duration_Exp+1;
=======
				     	 if(/*(PSV_Ins_Flow>Q_Ad_psv) || */(PSV_Exp_Pressure_Trriger<Pe_Ad_psv))
			       	 {
//					     	 t3_counter=duration_Ins+duration_Exp+1;;
//								 start_ins_psv_mode=1;
								 turbo_speed_Ins=pwm_i_psv;
								 PSV_MODE_INS=true;
			      	 }
							 else
							 {
//								 if ((PSV_Exp_Pressure-PSV_EPAP)>pwm_e_psv)  //   Delete negetive value of pwm
//								     pwm_e_psv=pwm_e_psv - (PSV_Exp_Pressure-PSV_EPAP);
//								 else
									 pwm_e_psv= 12;
	
	          	  turbo_speed_Exp=pwm_e_psv;
								  PSV_MODE_INS=false;
	             // duration_Exp=duration_Exp+1;
>>>>>>> c63a33440ac7da4f4de159016f77aa7bd58c3882
							 }
				 
			 }      	
       
    }
	}
<<<<<<< HEAD
}    
=======
  
>>>>>>> c63a33440ac7da4f4de159016f77aa7bd58c3882
