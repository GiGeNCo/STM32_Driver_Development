#include "stm32f411ceux.h"
#include "string.h"
void delay(uint32_t t)
{
	uint32_t i = 0;
	while(i < t)
	{
		i++;
	}
}
/*

        PB15 is SPI2 MOSI
        PB14 is SPI2 MISO
        PB13 is SPI2 SCLK
        PB12 is SPI2 SSEL

*/
void SPI2_GPIOInits(void)
{
    
    GPIO_Handle_t SPIPins;
    
    SPIPins.pGPIOx = GPIOB;
    SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ATLF;
    SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
	SPIPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

    //SCLK
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = 13;
    GPIO_Init(&SPIPins);
    
    //MOSI
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = 15;
    GPIO_Init(&SPIPins);
    
    //MISO
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = 14;
    GPIO_Init(&SPIPins);
    
    //SSEL NSS CS SS Slave select pin
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = 12;
    SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT;
	
	
    //SPIPins.GPIO_PinConfig.GPIO_PinNumber = 12;
    GPIO_Init(&SPIPins);
}

void SPI2_Inits()
{
    SPI_Handle_t SPI2Handle;
    
    SPI2Handle.pSPIx = SPI2;
    SPI2Handle.SPIConf.DevMode = SPI_MASTER_MODE;
    SPI2Handle.SPIConf.BusConf = SPI_BUS_FD;
    SPI2Handle.SPIConf.SclkSpeed = SPI_CLK_DIV_2;
    SPI2Handle.SPIConf.CPHA = SPI_CPHA_LOW;
    SPI2Handle.SPIConf.CPOL = SPI_CPOL_LOW;
    SPI2Handle.SPIConf.DFF = SPI_DFF_8;
    SPI2Handle.SPIConf.SSM = SPI_SSM_EN;
	
    SPI_Init(&SPI2Handle);

}


int main()
{
    
    SPI2_GPIOInits();
    
    SPI2_Inits();
    
    SPI_SSIConfig(SPI2, ENABLE);
	
	
    //deselect slave
    //GPIO_WriteToOutputPin(GPIOB,12,1);
	
    
    char user_data[] = "Hello SPI";
    
	
	
	for(uint8_t i = 0; i < 5; i++)
	{
	  
	  	//enable SPI
	 	SPI_PeripheralControl(SPI2, ENABLE);
		//delay(100);
		//select slave 
	  	GPIO_WriteToOutputPin(GPIOB,12,0);
		//delay(10);
	  	SPI_PeripheralControl(SPI2,DISABLE); 
		//delay(10);
	  	//deselect slave
	  	GPIO_WriteToOutputPin(GPIOB,12,1);
		
		//enable SPI
	 	SPI_PeripheralControl(SPI2, ENABLE);
		//delay(100);
		//select slave 
	  	GPIO_WriteToOutputPin(GPIOB,12,0);
	  	//send data
	  	SPI_SendData(SPI2,(uint8_t *)user_data,strlen(user_data));
	  	//lets confirm SPI is not busy
	  	while( SPI_GetFlagStatus(SPI2,SPI_BUSY_FLAG) );
	  	//Disable the SPI2 peripheral
	  	SPI_PeripheralControl(SPI2,DISABLE); 
		//delay(10);
	  	//deselect slave
	  	GPIO_WriteToOutputPin(GPIOB,12,1);
	  	//delay(10);
	}
	
	
    
    
    
    while(1)
    {
        

    }
    
    /*
    SPI_Handle_t spi1;
    
    spi1.pSPIx = SPI1;
    spi1.SPIConf.DevMode = SPI_MASTER_MODE;
    spi1.SPIConf.DFF = SPI_DFF_8;
    spi1.SPIConf.SSM = SPI_SSM_EN;
    spi1.SPIConf.SclkSpeed = SPI_CLK_DIV_2;
    spi1.SPIConf.BusConf = SPI_BUS_FD;
    
    SPI_Init(&spi1);
    
    */
    
    /*
	GPIO_Handle_t GpioLed, GpioButton;

	GpioLed.pGPIOx = GPIOC;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = 13;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;    
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PU;
	
	
	GPIO_PeriClockControl(GPIOC,ENABLE);
	GPIO_Init(&GpioLed);
	
       
	GpioButton.pGPIOx = GPIOB;
	GpioButton.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_1;
	GpioButton.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;			// 4 is GPIO_MODE_IT_FT
	GpioButton.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	//GpioButton.GPIO_PinConfig->GPIO_PinOPType = GPIO_OP_TYPE_PP;    
	GpioButton.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PU;
	
	
	GPIO_PeriClockControl(GPIOB,ENABLE);
	GPIO_Init(&GpioButton);	
        
	//I need this command below because built in button is connected on GND and A0 so, PA0's IDR must be 1 because when user press the button 
	//value change to low. so PA0 IDR register would be 0 when button would be pressed.
	//uncomment if you are not use GPIO_PIN_PU. because PU mode send high on PA0, and when you press, it will to GND
	//GPIOA->IDR |= (1 << 0);
	
	
	//interrupt configuration, pin mode must be interrupt
	if(GpioButton.GPIO_PinConfig.GPIO_PinMode > GPIO_MODE_ANALOG)
	{
		GPIO_IRQPriorityConfig(IRQ_NO_EXTI1,3); //second parameter is NVIC IRQ PRIO (from 0 to 15) - NVIC_IRQ_PRIO0
		GPIO_IRQInterruptConfig(IRQ_NO_EXTI1,ENABLE);
	}

*/

}
   
void EXTI1_IRQHandler(void) {
    // Check if the interrupt is from EXTI0
    //if (EXTI_PR & (1 << 0)) {
        // Clear the interrupt flag for pin
        GPIO_IRQHandling(1);
        for (uint8_t i = 0; i < 5; i++)
        {
            // Toggle the LED connected to PC13
            GPIO_ToggleOutputPin(GPIOC,GPIO_PIN_NO_13);  // Toggle LED state
            delay(1000000);
        
        }

        
    //}
}
   

