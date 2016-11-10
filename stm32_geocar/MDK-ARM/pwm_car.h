#ifndef __pwm_car_H
#define __pwm_car_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"


#define PRESCALER 0
#define PWM_RESOLUTION 65535
#define PWM_ PULSE 1000
	
	 
	 
void PWM_TIM_Init(Timer, Channel, freq_pwm); 
	 
void PWM_GPIO_Init(Timer)

void PWM_Set_Duty_Cycle(Timer, Channel, Duty); //dyty entre 0.0 et 1.0
	 
void PWM_Enable(Timer)
	
void PWM_Disable(Timer)
	


	 
	 
	 
#ifdef __cplusplus
}
#endif
#endif /*__pwm_car_H */

/**
  * @}
  */

/**
  * @}
  */