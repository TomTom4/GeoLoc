#include "pwm.h"

TIM_Config PWM2_Parameters;
TIM_Config PWM3_Parameters;
TIM_Config PWM4_Parameters;


//***************** INIT PWM ********************//


void PWM2_Init(uint32_t CHANNEL, int frequence_Hz)
{
	int Nbre_Cycles, PWM_Period, Final_Prescaler = 0;
	float Prescaler, temp = 0.0;
	int Overflow = 65535;  // 2^16-1
	
	
	Nbre_Cycles = (int)(SYSTEM_CLOCK_STM32/frequence_Hz);
	
	temp = Nbre_Cycles/Overflow;
	
	while(Prescaler < temp)
	{ 
		Prescaler = Prescaler + 2.0;
	}
	
	Final_Prescaler = (int)(Prescaler);
	
	PWM_Period = Nbre_Cycles/Final_Prescaler;
	
	//TIM2 initialization
	PWM2_Parameters = TIM2_Init(Final_Prescaler, PWM_Period, CHANNEL, 0);

}

void PWM3_Init(uint32_t CHANNEL, int frequence_Hz)
{
	int Nbre_Cycles, PWM_Period, Final_Prescaler = 0;
	float Prescaler, temp = 0.0;
	int Overflow = 65535;  // 2^16-1
	
	
	Nbre_Cycles = (int)(SYSTEM_CLOCK_STM32/frequence_Hz);
	
	temp = Nbre_Cycles/Overflow;
	
	while(Prescaler < temp)
	{ 
		Prescaler = Prescaler + 2.0;
	}
	
	Final_Prescaler = (int)(Prescaler);
	
	PWM_Period = Nbre_Cycles/Final_Prescaler;
	
	//TIM3 initialization
	PWM3_Parameters = TIM3_Init(Final_Prescaler, PWM_Period, CHANNEL, 0);
}

void PWM4_Init(uint32_t CHANNEL, int frequence_Hz)
{
	int Nbre_Cycles, PWM_Period, Final_Prescaler = 0;
	float Prescaler, temp = 0.0;
	int Overflow = 65535;  // 2^16-1
	
	
	Nbre_Cycles = (int)(SYSTEM_CLOCK_STM32/frequence_Hz);
	
	temp = Nbre_Cycles/Overflow;
	
	while(Prescaler < temp)
	{ 
		Prescaler = Prescaler + 2.0;
	}
	
	Final_Prescaler = (int)(Prescaler);
	
	PWM_Period = Nbre_Cycles/Final_Prescaler;
	
	//TIM4 initialization
	PWM4_Parameters = TIM4_Init(Final_Prescaler, PWM_Period, CHANNEL, 0);
}



//***************** SET DUTY_CYCLE PWM ********************//

void PWM_Set_DutyCycle(TIM_TypeDef* TIMER, uint32_t CHANNEL, int DutyCycle)
{
	int channel_pulse = 0;
	if(TIMER == TIM2)
	{
		channel_pulse = (int)((DutyCycle*PWM2_Parameters.TIM_Period)/100);
		PWM2_Parameters = TIM2_Init(PWM2_Parameters.TIM_Prescaler,PWM2_Parameters.TIM_Period, CHANNEL, channel_pulse);
	}
	else if (TIMER == TIM3)
	{
		channel_pulse = (int)((DutyCycle*PWM3_Parameters.TIM_Period)/100);
		PWM3_Parameters = TIM3_Init(PWM3_Parameters.TIM_Prescaler,PWM2_Parameters.TIM_Period, CHANNEL, channel_pulse);
	}
	else if (TIMER == TIM4)
	{
		channel_pulse = (int)((DutyCycle*PWM4_Parameters.TIM_Period)/100);
		PWM4_Parameters = TIM4_Init(PWM4_Parameters.TIM_Prescaler,PWM2_Parameters.TIM_Period, CHANNEL, channel_pulse);
	}
}



//***************** START PWM ********************//

void PWM2_Start(uint32_t CHANNEL)
{
	TIM_Start(TIM2);
	
	switch(CHANNEL)
	{
		case(TIM_CHANNEL_1):
		{
			TIM_Channel_Start(TIM2, TIM_CHANNEL_1);
		}
		break;
		
		case(TIM_CHANNEL_2):
		{
			TIM_Channel_Start(TIM2, TIM_CHANNEL_2);
		}
		break;
		
		case(TIM_CHANNEL_3):
		{
			TIM_Channel_Start(TIM2, TIM_CHANNEL_3);
		}
		break;
		
		case(TIM_CHANNEL_4):
		{
			TIM_Channel_Start(TIM2, TIM_CHANNEL_4);
		}
		break;
		
		default:
		break;	
		
	}
		
}

void PWM3_Start(uint32_t CHANNEL)
{
	TIM_Start(TIM3);
	
	switch(CHANNEL)
	{
		case(TIM_CHANNEL_1):
		{
			TIM_Channel_Start(TIM3, TIM_CHANNEL_1);
		}
		break;
		
		case(TIM_CHANNEL_2):
		{
			TIM_Channel_Start(TIM3, TIM_CHANNEL_2);
		}
		break;
		
		case(TIM_CHANNEL_3):
		{
			TIM_Channel_Start(TIM3, TIM_CHANNEL_3);
		}
		break;
		
		case(TIM_CHANNEL_4):
		{
			TIM_Channel_Start(TIM3, TIM_CHANNEL_4);
		}
		break;
		
		default:
		break;	
		
	}
}


void PWM4_Start(uint32_t CHANNEL)
{
	TIM_Start(TIM4);
	
	switch(CHANNEL)
	{
		case(TIM_CHANNEL_1):
		{
			TIM_Channel_Start(TIM4, TIM_CHANNEL_1);
		}
		break;
		
		case(TIM_CHANNEL_2):
		{
			TIM_Channel_Start(TIM4, TIM_CHANNEL_2);
		}
		break;
		
		case(TIM_CHANNEL_3):
		{
			TIM_Channel_Start(TIM4, TIM_CHANNEL_3);
		}
		break;
		
		case(TIM_CHANNEL_4):
		{
			TIM_Channel_Start(TIM4, TIM_CHANNEL_4);
		}
		break;
		
		default:
		break;	
		
	}
}

//***************** STOP PWM ********************//

void PWM2_Stop(uint32_t CHANNEL)
{
	switch(CHANNEL)
	{
		case(TIM_CHANNEL_1):
		{
			TIM_Channel_Stop(TIM2, TIM_CHANNEL_1);
		}
		break;
		
		case(TIM_CHANNEL_2):
		{
			TIM_Channel_Stop(TIM2, TIM_CHANNEL_2);
		}
		break;
		
		case(TIM_CHANNEL_3):
		{
			TIM_Channel_Stop(TIM2, TIM_CHANNEL_3);
		}
		break;
		
		case(TIM_CHANNEL_4):
		{
			TIM_Channel_Stop(TIM2, TIM_CHANNEL_4);
		}
		break;
		
		default:
		break;		
	}
	
	TIM_Stop(TIM2);
}


void PWM3_Stop(uint32_t CHANNEL)
{
	switch(CHANNEL)
	{
		case(TIM_CHANNEL_1):
		{
			TIM_Channel_Stop(TIM3, TIM_CHANNEL_1);
		}
		break;
		
		case(TIM_CHANNEL_2):
		{
			TIM_Channel_Stop(TIM3, TIM_CHANNEL_2);
		}
		break;
		
		case(TIM_CHANNEL_3):
		{
			TIM_Channel_Stop(TIM3, TIM_CHANNEL_3);
		}
		break;
		
		case(TIM_CHANNEL_4):
		{
			TIM_Channel_Stop(TIM3, TIM_CHANNEL_4);
		}
		break;
		
		default:
		break;		
	}
	
	TIM_Stop(TIM3);
}


void PWM4_Stop(uint32_t CHANNEL)
{
	switch(CHANNEL)
	{
		case(TIM_CHANNEL_1):
		{
			TIM_Channel_Stop(TIM4, TIM_CHANNEL_1);
		}
		break;
		
		case(TIM_CHANNEL_2):
		{
			TIM_Channel_Stop(TIM4, TIM_CHANNEL_2);
		}
		break;
		
		case(TIM_CHANNEL_3):
		{
			TIM_Channel_Stop(TIM4, TIM_CHANNEL_3);
		}
		break;
		
		case(TIM_CHANNEL_4):
		{
			TIM_Channel_Stop(TIM4, TIM_CHANNEL_4);
		}
		break;
		
		default:
		break;		
	}
	
	TIM_Stop(TIM4);
}









