#ifndef __pwm_H
#define __pwm_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "tim.h"
	 
#define SYSTEM_CLOCK_STM32 72000000

extern TIM_Config PWM2_Parameters;
extern TIM_Config PWM3_Parameters;
extern TIM_Config PWM4_Parameters;
	
	 
//FUNCTIONS
	 
//channel = TIM_CHANNEL_1, TIM_CHANNEL_2, TIM_CHANNEL_3 ou TIM_CHANNEL_4

//PWM associée au Timer 2 : la freq est fixe pour le TIM1
void PWM2_Init(uint32_t CHANNEL, int frequence_Hz);
//PWM associée au Timer 3
void PWM3_Init(uint32_t CHANNEL, int frequence_Hz);
//PWM associée au Timer 4
void PWM4_Init(uint32_t CHANNEL, int frequence_Hz);


//DutyCycle entre 0 et 100 ; TIMER = TIM2, TIM3 ou TIM4
void PWM_Set_DutyCycle(TIM_TypeDef* TIMER, uint32_t CHANNEL, int DutyCycle); 
	 
void PWM2_Start(uint32_t CHANNEL);	 
void PWM3_Start(uint32_t CHANNEL);	 
void PWM4_Start(uint32_t CHANNEL);	 
	 
void PWM2_Stop(uint32_t CHANNEL);	 
void PWM3_Stop(uint32_t CHANNEL);	 
void PWM4_Stop(uint32_t CHANNEL);	 
	 

	 
#ifdef __cplusplus
}
#endif
#endif /*__ pwm_H */
