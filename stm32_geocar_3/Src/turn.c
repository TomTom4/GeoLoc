#include "pwm.h"

#define DUTYCYCLE 20

/*****************************************\
This function allows to init the timers that 
generates pwm it has to be initiated before 
use of direction 
\*****************************************/
void directionInit(){
	PWM2_Init(TIM_CHANNEL_3, 1000);
	PWM2_Init(TIM_CHANNEL_4, 1000);
}
/***************************************\
This function allows to start generating 
pwm
\***************************************/
void directionOn(){
	PWM2_Start(TIM_CHANNEL_3);
	PWM2_Start(TIM_CHANNEL_4);
}
/***************************************\
This function allows to stop generating 
pwm
\***************************************/
void directionOff(){
	PWM2_Stop(TIM_CHANNEL_3);
	PWM2_Stop(TIM_CHANNEL_4);
}	 

/***************************************\
This function allows to set direction 
when pwm is generated /!\ if their is no
pwm, the direction system is off.
\***************************************/
void setDirection(char direction){
	directionOff();
	if(direction == 'l'){
		PWM_Set_DutyCycle(TIM2, TIM_CHANNEL_3,DUTYCYCLE);
		PWM_Set_DutyCycle(TIM2, TIM_CHANNEL_4,0);
	}
	else if(direction == 'r'){
		PWM_Set_DutyCycle(TIM2, TIM_CHANNEL_3,0);
		PWM_Set_DutyCycle(TIM2, TIM_CHANNEL_4,DUTYCYCLE);
	}
	directionOn(); 
	
}
