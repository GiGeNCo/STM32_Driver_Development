#include "spi_stm32f411ceux.h"

/********************************************************
  * @fn                 - GPIO RCC enable func
  *
  * @brief              - this func enable or disable peripheral on RCC
  *
  * @param [in]         - *pGPIOx structure(GPIO_RegDef_t) where is  GPIO Registers
  * @param [in]         - EnOrDi Enable or disable clock
  * @param [in]         - 
  *
  * @return             - none
  *
  * @note               - none
********************************************************/
void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnOrDi)
{
	if(EnOrDi == ENABLE)
	{
		if(pSPIx == SPI1)
		{
                     SPI1_PCLK_EN();
		}
		else if(pSPIx == SPI2)
		{
                    SPI2_PCLK_EN();
		}else if(pSPIx == SPI3)
                {
                    SPI2_PCLK_EN();
                }
        }
        
}


/********************************************************
  * @fn                 - SPI_Init
  *
  * @brief              - this func initialize user SPI config
  *
  * @param [in]         - *pSPIHandle structure where is 2 more structure inside 1 *pSPIx GPIO Registers
			- and *SPI_Config where would be user settings (configuration)
  * @param [in]         - 
  * @param [in]         - 
  *
  * @return             - none
  *
  * @note               - none
********************************************************/
void SPI_Init(SPI_Handle_t *pSPIHandle)
{
    // 1 enable clock
    SPI_PeriClockControl(pSPIHandle->pSPIx, ENABLE);
    
    uint32_t temp = 0;
    //device mode
    temp |= pSPIHandle->SPIConf.DevMode << SPI_CR1_MSTR;
    //configure device mode
    //temp |= pSPIHandle->SPIConf.DevMode << 2;
    
    //configure bus config
    if(pSPIHandle->SPIConf.BusConf == SPI_BUS_FD)
    {
        //BIDIMODE should be cleared
        temp &= ~(1 << 15);
    }
    else if(pSPIHandle->SPIConf.BusConf == SPI_BUS_HD)
    {
        //BIDIMODE should be set
        temp |= (1 << 15);
    }
    else if(pSPIHandle->SPIConf.BusConf == SPI_BUS_SIMPLEX_RX)
    {
        //BIDI MODE should be cleared
        temp &= ~(1 << 15);
        //RXONLY mode should be set
        temp |= (1 << 10);
    }
    else if(pSPIHandle->SPIConf.BusConf == SPI_BUS_SIMPLEX_TX)
    {
        //BIDI MODE should be cleared
        //tempreg &= ~(1 << 15);
        //TXONLY mode should be set
        //tempreg |= (1 << 15);
    }
    
    //configure the SPI Serial clock speed (baud rate)
    temp |= pSPIHandle->SPIConf.SclkSpeed << 3;
    
    //configure the DFF
    temp |= pSPIHandle->SPIConf.DFF << 11;
    
    //configure the cpol
    temp |= pSPIHandle->SPIConf.CPOL << 1;
    
    
    //configure the chpa
    temp |= pSPIHandle->SPIConf.CPHA << 0;
    
    //configure the SSM
    temp |= pSPIHandle->SPIConf.SSM << 9;
    
    pSPIHandle->pSPIx->CR1 = temp;
    
    //pSPIHandle->pSPIx->CR1 |= (1 << 6);
	
}


void SPI_DeInit(SPI_RegDef_t *pSPIx)
{
    

}




// spi get flag status 
uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx , uint32_t FlagName)
{
	if(pSPIx->SR & FlagName)
	{
		return 1;
	}
	return 0;
}

//send data
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuff, uint8_t Len)
{
    while (Len > 0)
    {
        
        while (SPI_GetFlagStatus(pSPIx,SPI_TXE_FLAG) == 0);
        
        //check dff bit
        if(pSPIx->CR1 & (1 << SPI_CR1_DFF))
        {
            // 16 bit dff
            pSPIx->DR = *((uint16_t *)pTxBuff);
            Len --;
            Len --;
            (uint16_t*)pTxBuff ++;
        }
        else
        {
             // 8 bit dff
            pSPIx->DR = *pTxBuff;
            Len --;
            pTxBuff++;
        }
    
    }

}

//receive data
void SPI_Receive(SPI_RegDef_t *pSPIx, uint8_t *pRxBuff, uint8_t Len)
{
	while (Len > 0)
    {
        // 1. wait until RXNE is set
        while (SPI_GetFlagStatus(pSPIx,SPI_RXNE_FLAG) == 0);
        
        // 2. check dff bit
        if(pSPIx->CR1 & (1 << SPI_CR1_DFF))
        {
            // 16 bit dff
			//load the data from data register to rx 
            *((uint16_t *)pRxBuff) = pSPIx->DR ;
            Len --;
            Len --;
            (uint16_t*)pRxBuff ++;
        }
        else
        {
            // 8 bit dff
            *pRxBuff = pSPIx->DR;
            Len --;
            pRxBuff++;
        }
    
    }
    
}

//IRQ conf ISR Handling
void SPI_IRQHandling(SPI_Handle_t *pHandle)
{
    
}

//Spi peripheral enable or disable function
void SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t EnOrDi)
{
    if(EnOrDi == ENABLE)
    {
        pSPIx->CR1 |= (1 << SPI_CR1_SPE);
    }
    else 
    {
        pSPIx->CR1 &= ~(1 << SPI_CR1_SPE);
    }


}


//ssi enable
void SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t EnOrDi)
{
    if(EnOrDi == ENABLE)
    {
        pSPIx->CR1 |= (1 << SPI_CR1_SSI);
    }
    else 
    {
        pSPIx->CR1 &= ~(1 << SPI_CR1_SSI);
    }
}


//ssOE enable
void SPI_SSOEConfig(SPI_RegDef_t *pSPIx, uint8_t EnOrDi)
{
    if(EnOrDi == ENABLE)
    {
        pSPIx->CR2 |= (1 << SPI_CR2_SSOE);
    }
    else 
    {
        pSPIx->CR2 &= ~(1 << SPI_CR2_SSOE);
    }
}
