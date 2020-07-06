#include "modes_setting.h"


//  BEGIN OF MODE Packet DECODER

void psv_mode_decoder()
{
	PSV_IPAP = rspy_receive_buffer[4];
	PSV_EPAP = rspy_receive_buffer[5];
	PSV_RISE_TIME = rspy_receive_buffer[6];
	PSV_TRRIG_I = rspy_receive_buffer[7];
	PSV_BUR = rspy_receive_buffer[8];
	PSV_Apnea = rspy_receive_buffer[9];
	PSV_MAXP = rspy_receive_buffer[10];
	int TRIIG_E_Sign = rspy_receive_buffer[11];
	int TRIIG_E = rspy_receive_buffer[12];

	if (TRIIG_E_Sign == 255)
		PSV_TRIIG_E = -1 * TRIIG_E;
	else
		PSV_TRIIG_E = TRIIG_E;

	PSV_Target_Vt = rspy_receive_buffer[13] * 256 + rspy_receive_buffer[14];

}


void acp_mode_decoder()
{
	ACP_IPAP = rspy_receive_buffer[4];
	ACP_EPAP = rspy_receive_buffer[5];
	ACP_RISE_TIME = rspy_receive_buffer[6];
	ACP_RATE = rspy_receive_buffer[7];
	ACP_IT_RATIO = rspy_receive_buffer[8];
	ACP_Inspiratory = rspy_receive_buffer[9];
	ACP_Expiratory = rspy_receive_buffer[10];

	ACP_Ti = ACP_Inspiratory + (ACP_Expiratory / 10.0);

	ACP_TRRIG_I = rspy_receive_buffer[11];
	ACP_MAXP = rspy_receive_buffer[12];

	ACP_Target_Vt = rspy_receive_buffer[13] * 256 + rspy_receive_buffer[14];

}

void acv_mode_decoder()
{
	ACV_EPAP = rspy_receive_buffer[4];
	ACV_RAMP = rspy_receive_buffer[5];
	ACV_RATE = rspy_receive_buffer[6];
	ACV_IT_RATIO = rspy_receive_buffer[7];

	ACV_Inspiratory = rspy_receive_buffer[8];
	ACV_Expiratory = rspy_receive_buffer[9];

	ACV_Ti = ACV_Inspiratory + (ACV_Expiratory / 10.0);

	ACV_TRRIG_I = rspy_receive_buffer[10];

	ACV_Sigh = rspy_receive_buffer[11];
	int Vt_Sigh_I = rspy_receive_buffer[12];

	int Vt_Sigh_F = rspy_receive_buffer[13];
	ACV_Vt_Sigh = Vt_Sigh_I + (Vt_Sigh_F / 10.0);
	ACV_Sigh_Rate = rspy_receive_buffer[14] * 256 + rspy_receive_buffer[15];

	ACV_Vt = rspy_receive_buffer[16] * 256 + rspy_receive_buffer[17];

}

void simv_mode_decoder()
{
	SIMV_IPAP = rspy_receive_buffer[4];
	SIMV_EPAP = rspy_receive_buffer[5];
	SIMV_RATE_SIMV = rspy_receive_buffer[6];
	SIMV_IT_RATIO = rspy_receive_buffer[7];
	SIMV_Inspiratory = rspy_receive_buffer[8];
	SIMV_Expiratory = rspy_receive_buffer[9];

	SIMV_Ti = SIMV_Inspiratory + (SIMV_Expiratory / 10.0);

	SIMV_TRRIG_I = rspy_receive_buffer[10];
	SIMV_BUR = rspy_receive_buffer[11];
	SIMV_Apnea = rspy_receive_buffer[12];
	SIMV_Vt = rspy_receive_buffer[13] * 256 + rspy_receive_buffer[14];

}

//  END OF MODE Packet DECODER


