#ifndef INC_SPI_STM32F411CEUX_H_
#define INC_SPI_STM32F411CEUX_H_

#include "stm32f411ceux.h"

//configuration structure of SPI
typedef struct
{
    uint8_t DevMode;
    uint8_t BusConf;
    uint8_t DFF;
    uint8_t CPHA;
    uint8_t CPOL;
    uint8_t SSM;
    uint8_t SclkSpeed;
    
}SPI_Config_t;

//handle structure for SPI
typedef struct 
{
    SPI_RegDef_t *pSPIx;
    SPI_Config_t SPIConf;
}SPI_Handle_t;


//peripheral clokc setup
void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnOrDi);


//init de-init
void SPI_Init(SPI_Handle_t *pSPIHandle);
void SPI_DeInit(SPI_RegDef_t *pSPIx);
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuff, uint8_t Len);
void SPI_Receive(SPI_RegDef_t *pSPIx, uint8_t *pTxBuff, uint8_t Len);
void SPI_IRQHandling(SPI_Handle_t *pHandle);
uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx , uint32_t FlagName);
void SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t EnOrDi);
void SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t EnOrDi);



#define SPI_MASTER_MODE                     1
#define SPI_SLAVE_MODE                      0

#define SPI_DFF_8                           0
#define SPI_DFF_16                          1

#define SPI_SSM_EN                          1
#define SPI_SSM_DI                          0

#define SPI_CLK_DIV_2                       0
#define SPI_CLK_DIV_4                       1
#define SPI_CLK_DIV_8                       2
#define SPI_CLK_DIV_16                      3
#define SPI_CLK_DIV_32                      4
#define SPI_CLK_DIV_64                      5
#define SPI_CLK_DIV_128                     6
#define SPI_CLK_DIV_256                     7

#define SPI_BUS_FD                          0
#define SPI_BUS_HD                          1
#define SPI_BUS_SIMPLEX_RX                  2
#define SPI_BUS_SIMPLEX_TX                  3

#define SPI_CPHA_HIGH                       0
#define SPI_CPHA_LOW                        0


#define SPI_CPOL_HIGH                       1
#define SPI_CPOL_LOW                        0

#define SPI_SS

/******************************************************************************************
 *Bit position definitions of SPI peripheral
 ******************************************************************************************/
/*
 * Bit position definitions SPI_CR1
 */
#define SPI_CR1_CPHA     				 0
#define SPI_CR1_CPOL      				 1
#define SPI_CR1_MSTR     				 2
#define SPI_CR1_BR   					 3
#define SPI_CR1_SPE     				 6
#define SPI_CR1_LSBFIRST   			 	 7
#define SPI_CR1_SSI     				 8
#define SPI_CR1_SSM      				 9
#define SPI_CR1_RXONLY      		 	        10
#define SPI_CR1_DFF     			 	11
#define SPI_CR1_CRCNEXT   			 	12
#define SPI_CR1_CRCEN   			 	13
#define SPI_CR1_BIDIOE     			 	14
#define SPI_CR1_BIDIMODE      			        15
     
/*
 * Bit position definitions SPI_CR2
 */
#define SPI_CR2_RXDMAEN		 			0
#define SPI_CR2_TXDMAEN				 	1
#define SPI_CR2_SSOE				 	2
#define SPI_CR2_FRF						4
#define SPI_CR2_ERRIE					5
#define SPI_CR2_RXNEIE				 	6
#define SPI_CR2_TXEIE					7


/*
 * Bit position definitions SPI_SR
 */
#define SPI_SR_RXNE					0
#define SPI_SR_TXE				        1
#define SPI_SR_CHSIDE				 	2
#define SPI_SR_UDR					3
#define SPI_SR_CRCERR				 	4
#define SPI_SR_MODF					5
#define SPI_SR_OVR					6
#define SPI_SR_BSY					7
#define SPI_SR_FRE					8
     
/*
 * SPI related status flags definitions
 */
#define SPI_TXE_FLAG    ( 1 << SPI_SR_TXE)
#define SPI_RXNE_FLAG   ( 1 << SPI_SR_RXNE)
#define SPI_BUSY_FLAG   ( 1 << SPI_SR_BSY)

#endif
