#ifndef INC_STM32F411CEUX_H_
#define INC_STM32F411CEUX_H_

#include "stdint.h"

#define __vo	volatile
	
	

//arm cortex m4 specific addresses

//NVIC ISER register addresses

#define NVIC_ISER0					((__vo uint32_t*) 0xE000E100)
#define NVIC_ISER1					((__vo uint32_t*) 0xE000E104)
#define NVIC_ISER2					((__vo uint32_t*) 0xE000E108)
#define NVIC_ISER3					((__vo uint32_t*) 0xE000E10C)

//NVIC_ICER register addresses

#define NVIC_ICER0					((__vo uint32_t*) 0xE000E180)
#define NVIC_ICER1					((__vo uint32_t*) 0xE000E184)
#define NVIC_ICER2					((__vo uint32_t*) 0xE000E188)
#define NVIC_ICER3					((__vo uint32_t*) 0xE000E18C)

//NVIC_Priority register addresses calculation
#define NVIC_PR_BASE_ADDR			((__vo uint32_t*) 0xE000E400)
#define NO_PR_BITS_IMPLEMENTED		4


#define FLASH_BASEADDR				0x08000000U
#define SRAM1_BASEADDR				0x20000000U		//128 Kbytes
#define SRAM2_BASEADDR				SRAM1_BASEADDR + 0x20000U	//1024 * 128kb = 131072 (this is 0x20000)
#define ROM							0x1FFF0000U
#define SRAM						SRAM1_BASEADDR

// APBx and AHBx BASEADDR addresses
#define APB1PERIPH_BASEADDR			0x40000000U
#define APB2PERIPH_BASEADDR			0x40010000U
#define AHB1PERIPH_BASEADDR			0x40020000U
#define AHB2PERIPH_BASEADDR			0x50000000U

//BASEADDR addresses of peripherals what are connected to ahb1 bus
//example: #define GPIOA_BASEADDR	(AHB1PERIPH_BASEADDR + OFFSET) //offset is 0x0000
#define GPIOA_BASEADDR				(AHB1PERIPH_BASEADDR + 0x0000)
#define GPIOB_BASEADDR				(AHB1PERIPH_BASEADDR + 0x0400)
#define GPIOC_BASEADDR				(AHB1PERIPH_BASEADDR + 0x0800)
#define GPIOD_BASEADDR				(AHB1PERIPH_BASEADDR + 0x0C00)
#define GPIOE_BASEADDR				(AHB1PERIPH_BASEADDR + 0x1000)
#define GPIOF_BASEADDR				(AHB1PERIPH_BASEADDR + 0x1400)
#define GPIOG_BASEADDR				(AHB1PERIPH_BASEADDR + 0x1800)
#define GPIOH_BASEADDR				(AHB1PERIPH_BASEADDR + 0x1C00)
#define GPIOI_BASEADDR				(AHB1PERIPH_BASEADDR + 0x2000)
#define GPIOJ_BASEADDR				(AHB1PERIPH_BASEADDR + 0x2400)
#define GPIOK_BASEADDR				(AHB1PERIPH_BASEADDR + 0x2800)

#define RCC_BASEADDR				(AHB1PERIPH_BASEADDR + 0x3800)

//BASEADDR addresses of peripherals what are hanging on APB1

#define I2C1_BASEADDR				(APB1PERIPH_BASEADDR + 0x5400)
#define I2C2_BASEADDR				(APB1PERIPH_BASEADDR + 0x5800)
#define I2C3_BASEADDR				(APB1PERIPH_BASEADDR + 0x5C00)

#define SPI2_BASEADDR				(APB1PERIPH_BASEADDR + 0x3800)
#define SPI3_BASEADDR				(APB1PERIPH_BASEADDR + 0x3C00)

#define USART2_BASEADDR				(APB1PERIPH_BASEADDR + 0x4400)
#define USART3_BASEADDR				(APB1PERIPH_BASEADDR + 0x4800)
#define UART4_BASEADDR				(APB1PERIPH_BASEADDR + 0x4C00)
#define UART5_BASEADDR				(APB1PERIPH_BASEADDR + 0x5000)

//BASEADDR addresses of peripherals what are hanging on APB2

#define EXTI_BASEADDR				(APB2PERIPH_BASEADDR + 0x3C00)

#define SPI1_BASEADDR				(APB2PERIPH_BASEADDR + 0x3000)
#define SPI4_BASEADDR				(APB2PERIPH_BASEADDR + 0x3400)


#define USART1_BASEADDR				(APB2PERIPH_BASEADDR + 0x1000)
#define USART6_BASEADDR				(APB2PERIPH_BASEADDR + 0x1400)

#define SYSCFG_BASEADDR				(APB2PERIPH_BASEADDR + 0x3800)

//start peripheral registers defining using structures

typedef struct 
{
	__vo uint32_t	MODER;				//GPIO PORT MODE REG offset is 0x00
	__vo uint32_t	OTYPER;				//GPIO port output type register offset is 0x04
	__vo uint32_t	OSPEEDR;			//GPIO port output speed register offset is 0x08
	__vo uint32_t	PUPDR;				//GPIO port pull-up/pull-down register offset is 0x0C
	__vo uint32_t	IDR;				//GPIO port input data register offset is 0x10
	__vo uint32_t	ODR;				//GPIO port output data register offset is 0x14
	__vo uint32_t	BSRR;				//GPIO port bit set/reset register offset is 0x18
	__vo uint32_t	LCKR;				//GPIO port configuration lock register offset is 0x1C
	__vo uint32_t	AFR[2];				//GPIO alternate function low register offset is 0x20
										//GPIO alternate function high register offset is 0x24
}GPIO_RegDef_t;


// SYSCFG register structure
typedef struct
{
	__vo uint32_t MEMRMP;			// SYSCFG memory remap register					0x00
	__vo uint32_t PMC;				// peripheral mode configuration register		0x04
	//__vo uint32_t EXTICR1;			// external interrupt configuration register 1	0x08
	//__vo uint32_t EXTICR2;			// external interrupt configuration register 2	0x0C
	//__vo uint32_t EXTICR3;			// external interrupt configuration register 3	0x10
	//__vo uint32_t EXTICR4;			// external interrupt configuration register 4	0x14
	//instead for 4 variable I created array
	__vo uint32_t EXTICR[4];		// external interrupt configuration register [4]	0x08...0x14
	__vo uint32_t CMPCR;			// Compensation cell control register			0x18
	
}SYSCFG_RegDef_t;


// RCC register structure
typedef struct
{
	__vo uint32_t CR;			//RCC clock control register 			0x00
	__vo uint32_t PLLCFGR;			//RCC PLL configuration register		0x04
	__vo uint32_t CFGR;			//RCC clock configuration register		0x08
	__vo uint32_t CIR;			//RCC clock interrupt register			0x0C
	__vo uint32_t AHB1RSTR;			//RCC AHB1 peripheral reset register	0x10
	__vo uint32_t AHB2RSTR;			//RCC AHB1 peripheral reset register	0x14
	__vo uint32_t reserved1;		// reserved 0x18
	__vo uint32_t reserved2;		//reserved 0x1C
	__vo uint32_t APB1RSTR;			//RCC APB1 peripheral reset register	0x20
	__vo uint32_t APB2RSTR;			//RCC APB2 peripheral reset register	0x24
	__vo uint32_t reserved3;		//reserved 0x28
	__vo uint32_t reserved4;		//reserved 0x2C
	__vo uint32_t AHB1ENR;			//RCC AHB1 peripheral clock enable register 0x30
	__vo uint32_t AHB2ENR;			//RCC AHB2 peripheral clock enable register 0x34
	__vo uint32_t reserved5;		//reversed 0x38
	__vo uint32_t reserved6;		//reversed 0x3C
	__vo uint32_t APB1ENR;			//RCC APB1 peripheral clock enable register 0x40
	__vo uint32_t APB2ENR;			//RCC APB2 peripheral clock enable register 0x44
	__vo uint32_t reserved7;		//reversed 0x48
	__vo uint32_t reserved8;		//reversed 0x4C
	__vo uint32_t AHB1LPENR;		//RCC AHB1 peripheral clock enable in low power mode register 0x50
	__vo uint32_t AHB2LPENR;		//RCC AHB2 peripheral clock enable in low power mode register 0x54
	__vo uint32_t reserved9;		//reversed 0x58
	__vo uint32_t reserved10;		//reversed 0x5C
	__vo uint32_t APB1LPENR;		//RCC APB1 peripheral clock enable in low power mode register 0x60
	__vo uint32_t APB2LPENR;		//RCC APB2 peripheral clock enabled in low power mode register 0x64
	__vo uint32_t reserved11;		//reversed 0x68
	__vo uint32_t reserved12;		//reversed 0x6C
	__vo uint32_t BDCR;			//RCC Backup domain control register 0x70
	__vo uint32_t CSR;			//RCC clock control & status register 0x74	
	__vo uint32_t reserved13;		//reversed 0x78
	__vo uint32_t reserved14;		//reversed 0x7C	
	__vo uint32_t SSCGR;			//RCC spread spectrum clock generation register 0x80
	__vo uint32_t PLLI2SCFGR;		//RCC PLLI2S configuration register 0x84
	__vo uint32_t reserved15;		//reversed 0x88
	__vo uint32_t DCKCFGR;			//RCC Dedicated Clocks Configuration Register 0x8C
}RCC_RegDef_t;

// EXTI register structure
typedef struct
{
	__vo uint32_t IMR;				//Interrupt mask register						0x00
	__vo uint32_t EMR;				//Event mask register 							0x04
	__vo uint32_t RTSR;				//Rising trigger selection register 			0x08
	__vo uint32_t FTSR;				//Falling trigger selection register 			0x0C
	__vo uint32_t SWIER;			        //Software interrupt event register 			0x10
	__vo uint32_t PR;				//Pending register 								0x14	
}EXTI_RegDef_t;

// SPI Register structure
typedef struct
{
    __vo uint32_t CR1;                          //SPI Control register 1
    __vo uint32_t CR2;                          //SPI control register 2
    __vo uint32_t SR;                           //SPI Status register
    __vo uint32_t DR;                           //SPI data register
    __vo uint32_t CRCPR;                        //SPI CRC polynomial register
    __vo uint32_t RXCRCR;                       //SPI RX CRC register
    __vo uint32_t TXCRCR;                       //SPI TX CRC register
    __vo uint32_t I2SCFGR;                      //SPI_I2S configuration register
    __vo uint32_t I2SPR;                        //SPI_I2S prescaler register
}SPI_RegDef_t;

//peripheral deffinations

#define GPIOA	((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB	((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC	((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD	((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE	((GPIO_RegDef_t*)GPIOE_BASEADDR)
#define GPIOF	((GPIO_RegDef_t*)GPIOF_BASEADDR)
#define GPIOG	((GPIO_RegDef_t*)GPIOG_BASEADDR)
#define GPIOH	((GPIO_RegDef_t*)GPIOH_BASEADDR)
#define GPIOI	((GPIO_RegDef_t*)GPIOI_BASEADDR)
#define GPIOJ	((GPIO_RegDef_t*)GPIOJ_BASEADDR)
#define GPIOK	((GPIO_RegDef_t*)GPIOK_BASEADDR)

#define RCC 	((RCC_RegDef_t*)RCC_BASEADDR)

#define EXTI	((EXTI_RegDef_t*) EXTI_BASEADDR)

#define SYSCFG	((SYSCFG_RegDef_t*) SYSCFG_BASEADDR)

#define SPI1    ((SPI_RegDef_t *)SPI1_BASEADDR)
#define SPI2    ((SPI_RegDef_t *)SPI2_BASEADDR)
#define SPI3    ((SPI_RegDef_t *)SPI3_BASEADDR)

//clock enable macros for GPIOx peripherals

#define GPIOA_PCLK_EN()		(RCC->AHB1ENR |= (1 << 0))
#define GPIOB_PCLK_EN()		(RCC->AHB1ENR |= (1 << 1))
#define GPIOC_PCLK_EN()		(RCC->AHB1ENR |= (1 << 2))
#define GPIOD_PCLK_EN()		(RCC->AHB1ENR |= (1 << 3))
#define GPIOE_PCLK_EN()		(RCC->AHB1ENR |= (1 << 4))
#define GPIOF_PCLK_EN()		(RCC->AHB1ENR |= (1 << 5))
#define GPIOG_PCLK_EN()		(RCC->AHB1ENR |= (1 << 6))
#define GPIOH_PCLK_EN()		(RCC->AHB1ENR |= (1 << 7))
#define GPIOI_PCLK_EN()		(RCC->AHB1ENR |= (1 << 8))
#define GPIOJ_PCLK_EN()		(RCC->AHB1ENR |= (1 << 9))
#define GPIOK_PCLK_EN()		(RCC->AHB1ENR |= (1 << 10))

//clock enable macros for I2Cx peripherals

#define I2C1_PCLK_EN()		(RCC->APB1ENR |= (1 << 21))
#define I2C2_PCLK_EN()		(RCC->APB1ENR |= (1 << 22))
#define I2C3_PCLK_EN()		(RCC->APB1ENR |= (1 << 23))

//clock enable macros for SPIx peripherals

#define SPI1_PCLK_EN()		(RCC->APB2ENR |= (1 << 12))
#define SPI2_PCLK_EN()		(RCC->APB1ENR |= (1 << 14))
#define SPI3_PCLK_EN()		(RCC->APB1ENR |= (1 << 15))


//clock enable macros for UARTx peripherals
#define USART1_PCLK_EN()	(RCC->APB2ENR |= (1 << 4))
#define USART2_PCLK_EN()	(RCC->APB1ENR |= (1 << 17))
#define USART3_PCLK_EN()	(RCC->APB1ENR |= (1 << 18))
#define UART4_PCLK_EN()		(RCC->APB1ENR |= (1 << 19))
#define UART5_PCLK_EN()		(RCC->APB1ENR |= (1 << 20))
#define USART6_PCLK_EN()	(RCC->APB2ENR |= (1 << 5))

//clock enable macros for SPIx peripherals

#define SYSCFG_PCLK_EN()	(RCC->APB2ENR |= (1 << 14))


//clock disable macros for GPIOx

#define GPIOA_PCLK_DI()		(RCC->AHB1ENR &= ~(1 << 0))
#define GPIOB_PCLK_DI()		(RCC->AHB1ENR &= ~(1 << 1))
#define GPIOC_PCLK_DI()		(RCC->AHB1ENR &= ~(1 << 2))
#define GPIOD_PCLK_DI()		(RCC->AHB1ENR &= ~(1 << 3))
#define GPIOE_PCLK_DI()		(RCC->AHB1ENR &= ~(1 << 4))
#define GPIOF_PCLK_DI()		(RCC->AHB1ENR &= ~(1 << 5))
#define GPIOG_PCLK_DI()		(RCC->AHB1ENR &= ~(1 << 6))
#define GPIOH_PCLK_DI()		(RCC->AHB1ENR &= ~(1 << 7))
#define GPIOI_PCLK_DI()		(RCC->AHB1ENR &= ~(1 << 8))
#define GPIOJ_PCLK_DI()		(RCC->AHB1ENR &= ~(1 << 9))
#define GPIOK_PCLK_DI()		(RCC->AHB1ENR &= ~(1 << 10))

//clock disable macros for I2Cx peripherals

#define I2C1_PCLK_DI()		(RCC->APB1ENR &= ~(1 << 21))
#define I2C2_PCLK_DI()		(RCC->APB1ENR &= ~(1 << 22))
#define I2C3_PCLK_DI()		(RCC->APB1ENR &= ~(1 << 23))

//clock disable macros for SPIx peripherals

#define SPI1_PCLK_DI()		(RCC->APB2ENR &= ~(1 << 12))
#define SPI2_PCLK_DI()		(RCC->APB1ENR &= ~(1 << 14))
#define SPI3_PCLK_DI()		(RCC->APB1ENR &= ~(1 << 15))


//clock disable macros for UARTx peripherals
#define USART1_PCLK_DI()	(RCC->APB2ENR &= ~(1 << 4))
#define USART2_PCLK_DI()	(RCC->APB1ENR &= ~(1 << 17))
#define USART3_PCLK_DI()	(RCC->APB1ENR &= ~(1 << 18))
#define UART4_PCLK_DI()		(RCC->APB1ENR &= ~(1 << 19))
#define UART5_PCLK_DI()		(RCC->APB1ENR &= ~(1 << 20))
#define USART6_PCLK_DI()	(RCC->APB2ENR &= ~(1 << 5))

//clock disable macros for SPIx peripherals

#define SYSCFG_PCLK_DI()	(RCC->APB2ENR &= ~(1 << 14))

//macros to reset GPIOx peripheral
#define GPIOA_REG_RESET()	do{ (RCC->AHB1RSTR |= (1 << 0)); (RCC->AHB1RSTR &= ~(1 << 0)); } while(0)
#define GPIOB_REG_RESET()	do{ (RCC->AHB1RSTR |= (1 << 1)); (RCC->AHB1RSTR &= ~(1 << 1)); } while(0)
#define GPIOC_REG_RESET()	do{ (RCC->AHB1RSTR |= (1 << 2)); (RCC->AHB1RSTR &= ~(1 << 2)); } while(0)
#define GPIOD_REG_RESET()       do{ (RCC->AHB1RSTR |= (1 << 3)); (RCC->AHB1RSTR &= ~(1 << 3)); } while(0)
#define GPIOE_REG_RESET()       do{ (RCC->AHB1RSTR |= (1 << 4)); (RCC->AHB1RSTR &= ~(1 << 4)); } while(0)
#define GPIOF_REG_RESET()       do{ (RCC->AHB1RSTR |= (1 << 5)); (RCC->AHB1RSTR &= ~(1 << 5)); } while(0)
#define GPIOG_REG_RESET()       do{ (RCC->AHB1RSTR |= (1 << 6)); (RCC->AHB1RSTR &= ~(1 << 6)); } while(0)
#define GPIOH_REG_RESET()       do{ (RCC->AHB1RSTR |= (1 << 7)); (RCC->AHB1RSTR &= ~(1 << 7)); } while(0)
#define GPIOI_REG_RESET()       do{ (RCC->AHB1RSTR |= (1 << 8)); (RCC->AHB1RSTR &= ~(1 << 8)); } while(0)
#define GPIOJ_REG_RESET()	do{ (RCC->AHB1RSTR |= (1 << 9)); (RCC->AHB1RSTR &= ~(1 << 9)); } while(0)
#define GPIOK_REG_RESET()	do{ (RCC->AHB1RSTR |= (1 <<10)); (RCC->AHB1RSTR &= ~(1 <<10)); } while(0)

//return port code for given GPIOx bassse addr. it need for EXTICRx bit naming
#define GPIO_BASEADDR_TO_CODE(x)	(	(x == GPIOA) ? 0 :\
						(x == GPIOB) ? 1 :\
						(x == GPIOC) ? 2 :\
						(x == GPIOD) ? 3 :\
						(x == GPIOE) ? 4 :\
						(x == GPIOF) ? 5 :\
						(x == GPIOG) ? 6 :\
						(x == GPIOH) ? 7 :\
						(x == GPIOI) ? 8 :\
						(x == GPIOJ) ? 9 :\
						(x == GPIOK) ? 10:0     )


// IRQ (Interrupt Request) numbers of stm32f411ceux
//if you use another cpu you have to update values
// at firts I only define EXTI possitions

#define	IRQ_NO_EXTI0				6
#define	IRQ_NO_EXTI1				7
#define	IRQ_NO_EXTI2				8
#define	IRQ_NO_EXTI3				9
#define	IRQ_NO_EXTI4				10
#define	IRQ_NO_EXTI9_5				23
#define	IRQ_NO_EXTI15_10			40

//NVIC IRQ PRIO
#define NVIC_IRQ_PRIO0				0
#define NVIC_IRQ_PRIO15				15


//some generig macros

#define ENABLE				        1
#define DISABLE				        0
#define SET					1
#define RESET				        0
#define GPIO_PIN_SET		                1
#define GPIO_PIN_RESET		                0
#define HIGH				        1
#define LOW					0


#include "gpio_stm32f411ceux.h"
#include "spi_stm32f411ceux.h"

#endif