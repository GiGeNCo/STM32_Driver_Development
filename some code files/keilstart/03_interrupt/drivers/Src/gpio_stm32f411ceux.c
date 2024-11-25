#include "gpio_stm32f411ceux.h"



/********************************************************
  * @fn                 - GPIO_Init
  *
  * @brief              - this func initialize user gpio config
  *
  * @param [in]         - *pGPIOx structure(GPIO_RegDef_t) where is  GPIO Registers
  * @param [in]         - EnOrDi Enable or disable clock
  * @param [in]         - 
  *
  * @return             - none
  *
  * @note               - none
********************************************************/
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnOrDi)
{
	if(EnOrDi == ENABLE)
	{
		if(pGPIOx == GPIOA)
		{
			GPIOA_PCLK_EN();
		}
		else if(pGPIOx == GPIOB)
		{
			GPIOB_PCLK_EN();
		}
		else if(pGPIOx == GPIOC)
		{
			GPIOC_PCLK_EN();
		}
		else if(pGPIOx == GPIOD)
		{
			GPIOD_PCLK_EN();
		}
		else if(pGPIOx == GPIOE)
		{
			GPIOE_PCLK_EN();
		}
		else if(pGPIOx == GPIOF)
		{
			GPIOF_PCLK_EN();
		}
		else if(pGPIOx == GPIOG)
		{
			GPIOG_PCLK_EN();
		}
		else if(pGPIOx == GPIOH)
		{
			GPIOH_PCLK_EN();
		}
		else if(pGPIOx == GPIOI)
		{
			GPIOI_PCLK_EN();
		}
		else if(pGPIOx == GPIOJ)
		{
			GPIOJ_PCLK_EN();
		}
		else if(pGPIOx == GPIOK)
		{
			GPIOK_PCLK_EN();
		}
	}


}

/********************************************************
  * @fn                 - GPIO_Init
  *
  * @brief              - this func initialize user gpio config
  *
  * @param [in]         - *pGPIOHandle structure where is 2 more structure inside 1 *pGPIOx GPIO Registers
						- and *GPIO_PinConfig where would be user settings (configuration) about pin
  * @param [in]         - 
  * @param [in]         - 
  *
  * @return             - none
  *
  * @note               - none
********************************************************/
void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
	uint32_t temp = 0;
	//1. configure the mode of gpio pin
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG)
	{
		temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
		pGPIOHandle->pGPIOx->MODER &= ~(3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); // clear
		pGPIOHandle->pGPIOx->MODER |= temp;
		temp = 0;
	}
	else
	{
		if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_IT_FT)
		{
			// 1 configure FTSR, faling triger selection register. falling edge trigerring FTSR. 
			EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			//clear the corresponding RTSR bit
			EXTI->RTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}
		else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_IT_RT)
		{
			// 1 configure RTSR rising triger selection register . rising triger selection register RTSR.
			EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			//clear the corresponding FTSR bit
			EXTI->FTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}
		else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_IT_RT)
		{
			// 1 configure both RTSR and FTSR
			EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}
		
		// 2 configure the gpio port selection in SYSCFG_EXTICR.
		// stm32f4xx GPIO EXTI line can configure on SYSCFG register.
		// stm32f1xx GPIO EXTI line can configure on GPIO_ALTFUNC register
		uint8_t temp1,temp2;
		temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 4;
		temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 4;
		SYSCFG_PCLK_EN();
		uint8_t portcode = GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOx);
		SYSCFG->EXTICR[temp1] |= portcode << (temp2 * 4);
		
		
		// 3 enable the EXTI interrupt delivery using IMR
		EXTI->IMR |= 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber;
	}
	
	//2. configure speed
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->OSPEEDR &= ~(3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); // clear
	pGPIOHandle->pGPIOx->OSPEEDR |= temp;
	temp = 0;
	//3. configure pull up pull down
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->PUPDR &= ~(3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); // clear
	pGPIOHandle->pGPIOx->PUPDR |= temp;
	temp = 0;
	//4. configure output type
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType <<  pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->OTYPER &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); // clear
	pGPIOHandle->pGPIOx->OTYPER |= temp;
	temp = 0;
	//5. configure the alternate function
	if (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode == GPIO_MODE_ATLF)
	{
		uint32_t temp1 = 0, temp2 = 0;
		temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8;
		temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8;
		
		pGPIOHandle->pGPIOx->AFR[temp1] &= ~(0xF << (4 * temp2));		//clear
		pGPIOHandle->pGPIOx->AFR[temp1] |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << (4 * temp2));
		
	}	
}
/********************************************************
  * @fn                 - GPIO_DeInit
  *
  * @brief              - this func reset  gpio config
  *
  * @param [in]         - 
  * @param [in]         - 
  * @param [in]         - 
  *
  * @return             - none
  *
  * @note               - none
********************************************************/
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
{
	if(pGPIOx == GPIOA)
		{
			GPIOA_REG_RESET();
		}
		else if(pGPIOx == GPIOB)
		{
			GPIOB_REG_RESET();
		}
		else if(pGPIOx == GPIOC)
		{
			GPIOC_REG_RESET();
		}
		else if(pGPIOx == GPIOD)
		{
			GPIOD_REG_RESET();
		}
		else if(pGPIOx == GPIOE)
		{
			GPIOE_REG_RESET();
		}
		else if(pGPIOx == GPIOF)
		{
			GPIOF_REG_RESET();
		}
		else if(pGPIOx == GPIOG)
		{
			GPIOG_REG_RESET();
		}
		else if(pGPIOx == GPIOH)
		{
			GPIOH_REG_RESET();
		}
		else if(pGPIOx == GPIOI)
		{
			GPIOI_REG_RESET();
		}
		else if(pGPIOx == GPIOJ)
		{
			GPIOJ_REG_RESET();
		}
		else if(pGPIOx == GPIOK)
		{
			GPIOK_REG_RESET();
		}


}

/********************************************************
  * @fn                 - GPIOI_nit
  *
  * @brief              - this func read from input pin
  *
  * @param [in]         - *pGPIOx structure(GPIO_RegDef_t) where is  GPIO Registers
  * @param [in]         - PinNumber user selected pin
  * @param [in]         - 
  *
  * @return             - return uint8_t data from Pin 1 or 0
  *
  * @note               - none
********************************************************/
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	uint8_t value;
	value = (uint8_t)((pGPIOx->IDR >> PinNumber) & 0x00000001);
	return value;
}


/********************************************************
  * @fn                 - GPIOI_nit
  *
  * @brief              - this func read from input port
  *
  * @param [in]         - *pGPIOx (*pGPIORegDef_t) structure where is  GPIO Registers
  * @param [in]         - PinNumber user selected pin
  * @param [in]         - 
  *
  * @return             - return uint16_t data from Port
  *
  * @note               - none
********************************************************/

uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
{
	uint16_t value;
	value = (uint16_t)pGPIOx->IDR;
	return value;

}

/********************************************************
  * @fn                 - GPIO_writeTo output pin
  *
  * @brief              - this func initialize write to pin
  *
  * @param [in]         - *pGPIOx (*pGPIORegDef_t) structure where is  GPIO Registers
  * @param [in]         - PinNumber user selected pin
  * @param [in]         - Value user value
  *
  * @return             - none
  *
  * @note               - none
********************************************************/

void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value)
{
	if(Value == GPIO_PIN_SET)
	{
		//write 1 to output data register at the bit field correspondig to the pin number
		pGPIOx->ODR |= (1 << PinNumber);
	}
	else
	{
		pGPIOx->ODR &= ~(1 << PinNumber);
	}

}
/********************************************************
  * @fn                 - GPIO_writeTo output port
  *
  * @brief              - this func write to port
  *
  * @param [in]         - *pGPIOx (*pGPIORegDef_t) structure where is  GPIO Registers
  * @param [in]         - Value user value
  * @param [in]         - 
  *
  * @return             - none
  *
  * @note               - none
********************************************************/

void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t VALUE)
{
	pGPIOx->ODR = VALUE;
}
/********************************************************
  * @fn                 - GPIO_toggle pin
  *
  * @brief              - this func toggle pin
  *
  * @param [in]         - *pGPIOx (*pGPIORegDef_t) structure where is  GPIO Registers
  * @param [in]         - PinNumber user selected pint to toggle
  * @param [in]         - 
  *
  * @return             - none
  *
  * @note               - none
********************************************************/


void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	pGPIOx->ODR ^= (1 << PinNumber);
}


/********************************************************
  * @fn                 - GPIO_IRQ Config
  *
  * @brief              - this func configure IRQ
  *
  * @param [in]         - IRQNumber select IRQ number
  * @param [in]         - select IRQPriority
  * @param [in]         - EnOrDi enable or disable IRQ
  *
  * @return             - none
  *
  * @note               - none
********************************************************/

void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnOrDi)
{
	if(EnOrDi == ENABLE)
	{
		if(IRQNumber <= 31)								//0-31
		{
			// program ISER0 register
			*NVIC_ISER0 |= (1 << IRQNumber);
			*(uint32_t *)0xE000E100 |= (1 << 6);
		}
		else if (IRQNumber > 31 && IRQNumber < 64)		//32-63
		{
			// program ISER1 register
			*NVIC_ISER1 |= (1<<(IRQNumber%32));
			*(uint32_t *)0xE000E104 |= (1<<(IRQNumber%32));
		}
		else if (IRQNumber > 64 && IRQNumber < 96)		//64-95
		{
			// program ISER2 register
			*NVIC_ISER2 |= (1<<(IRQNumber%32));
		}
	}
	else 
	{
		if(IRQNumber <= 31)								//0-31
		{
			// program ICER0 register
			*NVIC_ICER0 |= (1 << IRQNumber);
		}
		else if (IRQNumber > 31 && IRQNumber < 64)		//32-63
		{
			// program ICER1 register
			*NVIC_ICER1 |= (1<<(IRQNumber%32));
		}
		else if (IRQNumber > 64 && IRQNumber < 96)		//64-95
		{
			// program ICER2 register
			*NVIC_ICER2 |= (1<<(IRQNumber%32));
		}
	}

}

/********************************************************
  * @fn                 - GPIO_IRQ Handling
  *
  * @brief              - this func HANDLE IRQ
  *
  * @param [in]         - PinNumber where to happen interrupt
  * @param [in]         - 
  * @param [in]         - 
  *
  * @return             - none
  *
  * @note               - none
********************************************************/
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority)
{
	// 1. find out the IPR register
	uint8_t iprx = IRQNumber / 4;
	uint8_t iprx_select = IRQNumber % 4;
	
	uint8_t shift_amount = (8 * iprx_select) + ( 8 * NO_PR_BITS_IMPLEMENTED);
	
	*(NVIC_PR_BASE_ADDR + (iprx * 4))	|= (IRQPriority << shift_amount);
	//*(NVIC_PR_BASE_ADDR + (iprx * 4))	|= (IRQPriority <<(8*iprx_select));

	}

/********************************************************
  * @fn                 - GPIO_IRQ Handling
  *
  * @brief              - this func HANDLE IRQ
  *
  * @param [in]         - PinNumber where to happen interrupt
  * @param [in]         - 
  * @param [in]         - 
  *
  * @return             - none
  *
  * @note               - none
********************************************************/
void GPIO_IRQHandling(uint8_t PinNumber)
{
	//clear the EXTI pr register corresponding to the pin number
	if(EXTI->PR & (1 << PinNumber))
	{
		//clear
		EXTI->PR |= ( 1 << PinNumber);
	}

}
