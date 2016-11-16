/**
  ******************************************************************************
  * File Name          : TIM.c
  * Description        : This file provides code for the configuration
  *                      of the TIM instances.
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "tim.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;

/* TIM2 init function */
TIM_Config TIM2_Init(int TIM2_PRESCALER, int TIM2_PERIOD, uint32_t TIM2_CHANNEL, int CHANNEL_PULSE)
{
  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_OC_InitTypeDef sConfigOC;
	
	TIM_Config TIM_Parameters;
	
	TIM_Parameters.TIM_Prescaler = TIM2_PRESCALER;
	TIM_Parameters.TIM_Period = TIM2_PERIOD;
	TIM_Parameters.TIM_Pulse = CHANNEL_PULSE;

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = TIM2_PRESCALER;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = TIM2_PERIOD;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }

  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	
	switch(TIM2_CHANNEL) {
		
		case(TIM_CHANNEL_1):
		{
			sConfigOC.Pulse = CHANNEL_PULSE;
	
			if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
			{
				Error_Handler();
			}	
			
			HAL_TIM_MspPostInit(&htim2, TIM_CHANNEL_1);
		}
		break;
		
		case(TIM_CHANNEL_2):
		{
			sConfigOC.Pulse = CHANNEL_PULSE;
	
			if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
			{
				Error_Handler();
			}
			
			HAL_TIM_MspPostInit(&htim2, TIM_CHANNEL_2);
		}
		break;
		
		case(TIM_CHANNEL_3):
		{
			sConfigOC.Pulse = CHANNEL_PULSE;
	
			if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
			{
				Error_Handler();
			}
			
			HAL_TIM_MspPostInit(&htim2, TIM_CHANNEL_3);
		}
		break;
		
		case(TIM_CHANNEL_4):
		{
			sConfigOC.Pulse = CHANNEL_PULSE;
			
			if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
			{
				Error_Handler();
			}
			
			HAL_TIM_MspPostInit(&htim2, TIM_CHANNEL_4);
		}
		break;
		
		default:
		break;
		
	}
	
	return TIM_Parameters;

}


/* TIM3 init function */
TIM_Config TIM3_Init(int TIM3_PRESCALER, int TIM3_PERIOD, uint32_t TIM3_CHANNEL, int CHANNEL_PULSE)
{
  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_OC_InitTypeDef sConfigOC;
	
	TIM_Config TIM_Parameters;
	
	TIM_Parameters.TIM_Prescaler = TIM3_PRESCALER;
	TIM_Parameters.TIM_Period = TIM3_PERIOD;
	TIM_Parameters.TIM_Pulse = CHANNEL_PULSE;

  htim3.Instance = TIM3;
  htim3.Init.Prescaler = TIM3_PRESCALER;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = TIM3_PERIOD;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }

  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	
	switch(TIM3_CHANNEL) {
		
		case(TIM_CHANNEL_1):
		{
			sConfigOC.Pulse = CHANNEL_PULSE;
	
			if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
			{
				Error_Handler();
			}	
			
			HAL_TIM_MspPostInit(&htim3, TIM_CHANNEL_1);
		}
		break;
		
		case(TIM_CHANNEL_2):
		{
			sConfigOC.Pulse = CHANNEL_PULSE;
	
			if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
			{
				Error_Handler();
			}
			
			HAL_TIM_MspPostInit(&htim3,  TIM_CHANNEL_2);
		}
		break;
		
		case(TIM_CHANNEL_3):
		{
			sConfigOC.Pulse = CHANNEL_PULSE;
	
			if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
			{
				Error_Handler();
			}
			
			HAL_TIM_MspPostInit(&htim3, TIM_CHANNEL_3);
		}
		break;
		
		
		case(TIM_CHANNEL_4):
		{
			sConfigOC.Pulse = CHANNEL_PULSE;
			
			if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
			{
				Error_Handler();
			}
			
			HAL_TIM_MspPostInit(&htim3, TIM_CHANNEL_4);
		}
		break;
		
		default:
		break;
		
	}
	
	return TIM_Parameters;
				
}


/* TIM4 init function */
TIM_Config TIM4_Init(int TIM4_PRESCALER, int TIM4_PERIOD, uint32_t TIM4_CHANNEL, int CHANNEL_PULSE)
{
  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_OC_InitTypeDef sConfigOC;
	
	TIM_Config TIM_Parameters;
	
	TIM_Parameters.TIM_Prescaler = TIM4_PRESCALER;
	TIM_Parameters.TIM_Period = TIM4_PERIOD;
	TIM_Parameters.TIM_Pulse = CHANNEL_PULSE;

  htim4.Instance = TIM4;
  htim4.Init.Prescaler = TIM4_PRESCALER;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = TIM4_PERIOD;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_TIM_PWM_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }

  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	
	switch(TIM4_CHANNEL) {
		
		case(TIM_CHANNEL_1):
		{
			sConfigOC.Pulse = CHANNEL_PULSE;
	
			if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
			{
				Error_Handler();
			}	
			
			HAL_TIM_MspPostInit(&htim4, TIM_CHANNEL_1);
		}
		break;
		
		case(TIM_CHANNEL_2):
		{
			sConfigOC.Pulse = CHANNEL_PULSE;
	
			if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
			{
				Error_Handler();
			}
			
			HAL_TIM_MspPostInit(&htim4, TIM_CHANNEL_2);
		}
		break;
		
		case(TIM_CHANNEL_3):
		{
			sConfigOC.Pulse = CHANNEL_PULSE;
	
			if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
			{
				Error_Handler();
			}
			
			HAL_TIM_MspPostInit(&htim4, TIM_CHANNEL_3);
		}
		break;
		
		case(TIM_CHANNEL_4):
		{
			sConfigOC.Pulse = CHANNEL_PULSE;
			
			if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
			{
				Error_Handler();
			}
			
			HAL_TIM_MspPostInit(&htim4, TIM_CHANNEL_4);
		}
		break;
		
		default:
		break;
		
	}
	
	return TIM_Parameters;
			
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM2)
  {
  /* USER CODE BEGIN TIM2_MspInit 0 */

  /* USER CODE END TIM2_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_TIM2_CLK_ENABLE();

    /* Peripheral interrupt init */
    HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM2_IRQn);
  /* USER CODE BEGIN TIM2_MspInit 1 */

  /* USER CODE END TIM2_MspInit 1 */
  }
  else if(tim_baseHandle->Instance==TIM3)
  {
  /* USER CODE BEGIN TIM3_MspInit 0 */

  /* USER CODE END TIM3_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_TIM3_CLK_ENABLE();

    /* Peripheral interrupt init */
    HAL_NVIC_SetPriority(TIM3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM3_IRQn);
  /* USER CODE BEGIN TIM3_MspInit 1 */

  /* USER CODE END TIM3_MspInit 1 */
  }
  else if(tim_baseHandle->Instance==TIM4)
  {
  /* USER CODE BEGIN TIM4_MspInit 0 */

  /* USER CODE END TIM4_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_TIM4_CLK_ENABLE();

    /* Peripheral interrupt init */
    HAL_NVIC_SetPriority(TIM4_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM4_IRQn);
  /* USER CODE BEGIN TIM4_MspInit 1 */

  /* USER CODE END TIM4_MspInit 1 */
  }
}


void HAL_TIM_MspPostInit(TIM_HandleTypeDef* timHandle, uint32_t TIM_CHANNEL)
{

  GPIO_InitTypeDef GPIO_InitStruct;
	
  if(timHandle->Instance==TIM2)
  {
  /* USER CODE BEGIN TIM2_MspPostInit 0 */

  /* USER CODE END TIM2_MspPostInit 0 */
    /**TIM2 GPIO Configuration    
    PA0-WKUP     ------> TIM2_CH1
    PA1     ------> TIM2_CH2
    PB10     ------> TIM2_CH3
    PB11     ------> TIM2_CH4 
    */
		
		switch(TIM_CHANNEL){
			
			case(TIM_CHANNEL_1):
			{
				GPIO_InitStruct.Pin = GPIO_PIN_0;
				GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
				GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
				HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
			}
			break;
			
			case(TIM_CHANNEL_2):
			{
				GPIO_InitStruct.Pin = GPIO_PIN_1;
				GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
				GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
				HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);	
			}
			
			case(TIM_CHANNEL_3):
			{
				GPIO_InitStruct.Pin = GPIO_PIN_10;
				GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
				GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
				HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
			}
			break;
			
			case(TIM_CHANNEL_4):
			{
				GPIO_InitStruct.Pin = GPIO_PIN_11;
				GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
				GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
				HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
			}
			break;
			
			default:
			break;
		}

    __HAL_AFIO_REMAP_TIM2_PARTIAL_2();

  /* USER CODE BEGIN TIM2_MspPostInit 1 */

  /* USER CODE END TIM2_MspPostInit 1 */
  }
  else if(timHandle->Instance==TIM3)
  {
  /* USER CODE BEGIN TIM3_MspPostInit 0 */

  /* USER CODE END TIM3_MspPostInit 0 */
  
    /**TIM3 GPIO Configuration    
    PA6     ------> TIM3_CH1
    PA7     ------> TIM3_CH2
    PB0     ------> TIM3_CH3
    PB1     ------> TIM3_CH4 
    */
		
		switch(TIM_CHANNEL){
			
			case(TIM_CHANNEL_1):
			{
				GPIO_InitStruct.Pin = GPIO_PIN_6;
				GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
				GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
				HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
			}
			break;
			
			case(TIM_CHANNEL_2):
			{
				GPIO_InitStruct.Pin = GPIO_PIN_7;
				GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
				GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
				HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);	
			}
			
			case(TIM_CHANNEL_3):
			{
				GPIO_InitStruct.Pin = GPIO_PIN_0;
				GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
				GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
				HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
			}
			break;
			
			case(TIM_CHANNEL_4):
			{
				GPIO_InitStruct.Pin = GPIO_PIN_1;
				GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
				GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
				HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
			}
			break;
			
			default:
			break;
		}
    
  /* USER CODE BEGIN TIM3_MspPostInit 1 */

  /* USER CODE END TIM3_MspPostInit 1 */
  }
  else if(timHandle->Instance==TIM4)
  {
  /* USER CODE BEGIN TIM4_MspPostInit 0 */

  /* USER CODE END TIM4_MspPostInit 0 */
  
    /**TIM4 GPIO Configuration    
    PB6     ------> TIM4_CH1
    PB7     ------> TIM4_CH2
    PB8     ------> TIM4_CH3
    PB9     ------> TIM4_CH4 
    */
		
		switch(TIM_CHANNEL){
			
			case(TIM_CHANNEL_1):
			{
				GPIO_InitStruct.Pin = GPIO_PIN_6;
				GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
				GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
				HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
			}
			break;
			
			case(TIM_CHANNEL_2):
			{
				GPIO_InitStruct.Pin = GPIO_PIN_7;
				GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
				GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
				HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);	
			}
			
			case(TIM_CHANNEL_3):
			{
				GPIO_InitStruct.Pin = GPIO_PIN_8;
				GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
				GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
				HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
			}
			break;
			
			case(TIM_CHANNEL_4):
			{
				GPIO_InitStruct.Pin = GPIO_PIN_9;
				GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
				GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
				HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
			}
			break;
			
			default:
			break;
		}
  
  /* USER CODE BEGIN TIM4_MspPostInit 1 */

  /* USER CODE END TIM4_MspPostInit 1 */
  }

}



void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM2)
  {
  /* USER CODE BEGIN TIM2_MspDeInit 0 */

  /* USER CODE END TIM2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM2_CLK_DISABLE();

    /* Peripheral interrupt Deinit*/
    HAL_NVIC_DisableIRQ(TIM2_IRQn);

  /* USER CODE BEGIN TIM2_MspDeInit 1 */

  /* USER CODE END TIM2_MspDeInit 1 */
  }
  else if(tim_baseHandle->Instance==TIM3)
  {
  /* USER CODE BEGIN TIM3_MspDeInit 0 */

  /* USER CODE END TIM3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM3_CLK_DISABLE();

    /* Peripheral interrupt Deinit*/
    HAL_NVIC_DisableIRQ(TIM3_IRQn);

  /* USER CODE BEGIN TIM3_MspDeInit 1 */

  /* USER CODE END TIM3_MspDeInit 1 */
  }
  else if(tim_baseHandle->Instance==TIM4)
  {
  /* USER CODE BEGIN TIM4_MspDeInit 0 */

  /* USER CODE END TIM4_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM4_CLK_DISABLE();

    /* Peripheral interrupt Deinit*/
    HAL_NVIC_DisableIRQ(TIM4_IRQn);

  /* USER CODE BEGIN TIM4_MspDeInit 1 */

  /* USER CODE END TIM4_MspDeInit 1 */
  }
} 






void TIM_Start(TIM_TypeDef* TIMER)
{
	if (TIMER == TIM2){
		HAL_TIM_Base_Start(&htim2);
	}
	
	else if (TIMER == TIM3){
		HAL_TIM_Base_Start(&htim3);
	}
	
	else if (TIMER == TIM4){
		HAL_TIM_Base_Start(&htim4);
	}
}




void TIM_Stop(TIM_TypeDef* TIMER)
{
	if (TIMER == TIM2){
		HAL_TIM_Base_Stop(&htim2);
	}
	
	else if (TIMER == TIM3){
		HAL_TIM_Base_Stop(&htim3);
	}
	
	else if (TIMER == TIM4){
		HAL_TIM_Base_Stop(&htim4);
	}
}





void TIM_Channel_Start(TIM_TypeDef* TIMER, uint32_t TIM_CHANNEL)
{
	if (TIMER == TIM2){
		HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL);
	}
	
	else if (TIMER == TIM3){
		HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL);
	}
	
	else if (TIMER == TIM4){
		HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL);
	}
}




void TIM_Channel_Stop(TIM_TypeDef* TIMER, uint32_t TIM_CHANNEL)
{
	if (TIMER == TIM2){
		HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL);
	}
	
	else if (TIMER == TIM3){
		HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL);
	}
	
	else if (TIMER == TIM4){
		HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL);
	}
}


/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
