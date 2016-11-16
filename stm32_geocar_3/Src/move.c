#include "pwm.h"

/*****************************************\
This function allows to init the timers that 
generates pwm it has to be initiated before 
use of engines
\*****************************************/
void enginesInit(){
	PWM2_Init(TIM_CHANNEL_1, 1000);
	PWM2_Init(TIM_CHANNEL_2, 1000);
}

/***************************************\
This function allows to start generating 
pwm , sended to engines /!\ if dutycycle
is 0% , the engines will not move . 
\***************************************/
void enginesOn(){

	PWM2_Start(TIM_CHANNEL_1);
	PWM2_Start(TIM_CHANNEL_2);
}

/***************************************\
This function allows to stop engines
\***************************************/
void enginesOff(){
	
	PWM2_Stop(TIM_CHANNEL_1);
	PWM2_Stop(TIM_CHANNEL_2);
	
}

/***************************************\
This function allows to set engines speed
and direction.
\***************************************/
void setEnginesSpeeed(int speed, char direction){
        float dutyCycle ;
				enginesOff();
        if(speed > 6)
                dutyCycle = 50 ;
        else if(speed > 0)
                dutyCycle = ((float)speed/6)*50 ;
        else
                dutyCycle = 0 ;
				if(direction == 'f' ){
					PWM_Set_DutyCycle(TIM2, TIM_CHANNEL_1, (int) dutyCycle);
					PWM_Set_DutyCycle(TIM2, TIM_CHANNEL_2, 0);
			}
				else if(direction == 'b'){
					PWM_Set_DutyCycle(TIM2, TIM_CHANNEL_2, (int) dutyCycle);
					PWM_Set_DutyCycle(TIM2, TIM_CHANNEL_1, 0);
			  }
			enginesOn();
}




