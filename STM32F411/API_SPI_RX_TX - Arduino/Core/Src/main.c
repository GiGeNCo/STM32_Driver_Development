#include "stm32f411ceux.h"
#include "string.h"

#define CMD_LED_CTRL			0x50
#define CMD_SENSOR_READ			0x51
#define CMD_LED_READ			0x52
#define CMD_PRINT				0x53
#define CMD_ID_READ				0x54

#define LED_ON					1
#define LED_OFF					0

#define PIN_A0					0		//Arduino analog PINx
#define PIN_A1					1
#define PIN_A2					2
#define PIN_A3					3
#define PIN_A4					4
#define PIN_A5					5

#define LED_PIN					13


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
    //SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT;
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
uint8_t SPI_VerifyResponse(uint8_t ackbyte)
{
	if (ackbyte == 0xF5)
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}
int main()
{
  
    //char user_data[] = "SPI is a protocol named by Motorola. With him you can control sensors, SD card and much more.";
	//uint8_t dataLen = strlen(user_data);
	uint8_t dummy_write = 0xf0;
	uint8_t dummy_read;
	
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
	 
	
    uint8_t pindata = GPIO_ReadFromInputPin(GPIOA,2);
	uint8_t cmdcode = CMD_LED_CTRL;
	uint8_t ackbyte;
	uint8_t args[2];
	//enable the SPI2 peripheral
	SPI_PeripheralControl(SPI2,ENABLE);
	SPI_SendData(SPI2,&cmdcode,1);
	SPI_PeripheralControl(SPI2,ENABLE);
    while(1)
    {
		
		
		while(!GPIO_ReadFromInputPin(GPIOA,2));
		delay(500000);
		
		cmdcode = CMD_LED_CTRL;
		
		//enable the SPI2 peripheral
		SPI_PeripheralControl(SPI2,ENABLE);
		
		// 1 CMD_LED_CTRL   <  pin n(1)    <value 1>   >
		
		SPI_SendData(SPI2,&cmdcode,1);
		
		
		//do dummy read to clear off the RXNE
		SPI_Receive(SPI2,&dummy_read,1);
		
		//send some dummy bits (1 byte) to fetch the response from the slave
		SPI_SendData(SPI2,&dummy_write,1);
		// read the received ack - 
		SPI_Receive(SPI2,&ackbyte,1);
		
		if (SPI_VerifyResponse(ackbyte))
		{
			//send arguments
			args[0] = LED_PIN;
			args[1] = LED_ON;
			
			//send arguments
			SPI_SendData(SPI2,args,2);
			
			// dummy read
			SPI_Receive(SPI2,args,2);
		}
		
		// 2. send command
		
		
		while(SPI_GetFlagStatus(SPI2,SPI_BUSY_FLAG));
		//Disable the SPI2 peripheral
		SPI_PeripheralControl(SPI2,DISABLE);
		
		
		
		
		
		
		
		
    }
   

}
   
/*

		//first send length information
		SPI_SendData(SPI2,&dataLen,1);
		//lets confirm SPI is not busy
		while( SPI_GetFlagStatus(SPI2,SPI_BUSY_FLAG) );
		
		//to send data
		SPI_SendData(SPI2,(uint8_t*)user_data,strlen(user_data));
		
		//lets confirm SPI is not busy
		while( SPI_GetFlagStatus(SPI2,SPI_BUSY_FLAG) );

		//Disable the SPI2 peripheral
		SPI_PeripheralControl(SPI2,DISABLE);
		
		pindata = GPIO_ReadFromInputPin(GPIOA,2);



*/

