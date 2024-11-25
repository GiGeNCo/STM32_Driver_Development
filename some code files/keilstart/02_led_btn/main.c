#include "stm32f411ceux.h"


void delay(uint32_t t)
{
	uint32_t i = 0;
	while(i < t)
	{
		i++;
	}
}

int main()
   {
	GPIO_Handle_t GpioLed, GpioButton;
	
	GpioLed.pGPIOx = GPIOC;
	GpioLed.GPIO_PinConfig->GPIO_PinNumber = 13;
	GpioLed.GPIO_PinConfig->GPIO_PinMode = GPIO_MODE_OUTPUT;
	GpioLed.GPIO_PinConfig->GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioLed.GPIO_PinConfig->GPIO_PinOPType = GPIO_OP_TYPE_PP;    
	GpioLed.GPIO_PinConfig->GPIO_PinPuPdControl = GPIO_PU;
	
	
	GPIO_PeriClockControl(GPIOC,ENABLE);
	GPIO_Init(&GpioLed);
	   
	GpioButton.pGPIOx = GPIOA;
	GpioButton.GPIO_PinConfig->GPIO_PinNumber = 0;
	GpioButton.GPIO_PinConfig->GPIO_PinMode = GPIO_MODE_INPUT;
	GpioButton.GPIO_PinConfig->GPIO_PinSpeed = GPIO_SPEED_FAST;
	//GpioButton.GPIO_PinConfig->GPIO_PinOPType = GPIO_OP_TYPE_PP;    
	GpioButton.GPIO_PinConfig->GPIO_PinPuPdControl = GPIO_PU;
	
	
	GPIO_PeriClockControl(GPIOA,ENABLE);
	GPIO_Init(&GpioButton);
	//I need this command below because built in button is connected on GND and A0 so, PA0's IDR must be 1 because when user press the button 
	//value change to low. so PA0 IDR register would be 0 when button would be pressed.
	//uncomment if you are not use GPIO_PIN_PU. because PU mode send high on PA0, and when you press, it will to GND
	//GPIOA->IDR |= (1 << 0);

	while(1)
	{
		if(GPIO_ReadFromInputPin(GPIOA,0) == LOW )
		{
			delay(200000);
			GPIO_ToggleOutputPin(GPIOC,GPIO_PIN_NO_13);
			
		}
		
	}


}