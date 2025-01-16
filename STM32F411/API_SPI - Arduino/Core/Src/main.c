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
    //SPIPins.GPIO_PinConfig.GPIO_PinNumber = 14;
    //GPIO_Init(&SPIPins);
    
    //SSEL NSS CS SS Slave select pin
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = 12;
    //SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT;
	
    //SPIPins.GPIO_PinConfig.GPIO_PinNumber = 12;
    GPIO_Init(&SPIPins);
}

void SPI2_Inits()
{
    SPI_Handle_t SPI2Handle;
    
    SPI2Handle.pSPIx = SPI2;
    SPI2Handle.SPIConf.DevMode = SPI_MASTER_MODE;
    SPI2Handle.SPIConf.BusConf = SPI_BUS_FD;
    SPI2Handle.SPIConf.SclkSpeed = SPI_CLK_DIV_8;
    SPI2Handle.SPIConf.CPHA = SPI_CPHA_LOW;
    SPI2Handle.SPIConf.CPOL = SPI_CPOL_LOW;
    SPI2Handle.SPIConf.DFF = SPI_DFF_8;
    SPI2Handle.SPIConf.SSM = SPI_SSM_DI; // DI means disable so we choose hardware slave management

    SPI_Init(&SPI2Handle);

}
void GPIO_ButtonInit(void)
{
	GPIO_Handle_t btn;
    
    btn.pGPIOx = GPIOA;
	btn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_2;
    btn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_INPUT;
    btn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PD;
    btn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	GPIO_Init(&btn);

}

int main()
{
  
    char user_data[] = "SPI (or Serial Peripheral Interface) is a protocol named by Motorola. With him you can control sensors, SD card and much more.";
	
	
	GPIO_ButtonInit();
    
    SPI2_GPIOInits();
    
    SPI2_Inits();
    
    //SPI_SSIConfig(SPI2, ENABLE); // we don't need because it make sense when ssm is enabled
	
	
	/*
	* making SSOE 1 does NSS OUTPUT enable
	* NSS poin is automatically controlled by hardware
	* it means when SPI will be enabled NSS will automatically pulled LOW
	* and when SPI will be disabled NSS pin will automatically pulled to HIGH
	*/
	
	SPI_SSOEConfig(SPI2, ENABLE);
	 
	uint8_t dataLen = strlen(user_data);
    uint8_t pindata = GPIO_ReadFromInputPin(GPIOA,2);
    while(1)
    {
		
		while(pindata == 0)
		{
			pindata = GPIO_ReadFromInputPin(GPIOA,2);		
		}
		delay(1000000);

		//enable the SPI2 peripheral
		SPI_PeripheralControl(SPI2,ENABLE);

		//first send length information
		uint8_t dataLen = strlen(user_data);
		SPI_SendData(SPI2,&dataLen,1);
		
		//to send data
		SPI_SendData(SPI2,(uint8_t*)user_data,strlen(user_data));

		//lets confirm SPI is not busy
		while( SPI_GetFlagStatus(SPI2,SPI_BUSY_FLAG) );

		//Disable the SPI2 peripheral
		SPI_PeripheralControl(SPI2,DISABLE);
		
		pindata = GPIO_ReadFromInputPin(GPIOA,2);
    }
   

}
   


