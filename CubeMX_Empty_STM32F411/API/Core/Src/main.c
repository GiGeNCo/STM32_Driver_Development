/*
#include <stdint.h>


// Base addresses for the STM32F411
#define RCC_BASE       0x40023800
#define GPIOA_BASE     0x40020000
#define GPIOC_BASE     0x40020800
#define SYSCFG_BASE    0x40013800
#define EXTI_BASE      0x40013C00
#define NVIC_BASE      0xE000E100

// RCC registers
#define RCC_AHB1ENR    (*(volatile uint32_t *)(RCC_BASE + 0x30))
#define RCC_APB2ENR    (*(volatile uint32_t *)(RCC_BASE + 0x44))

// GPIOA registers
#define GPIOA_MODER    (*(volatile uint32_t *)(GPIOA_BASE + 0x00))
#define GPIOA_PUPDR    (*(volatile uint32_t *)(GPIOA_BASE + 0x0C))

// GPIOC registers
#define GPIOC_MODER    (*(volatile uint32_t *)(GPIOC_BASE + 0x00))
#define GPIOC_ODR      (*(volatile uint32_t *)(GPIOC_BASE + 0x14))

// SYSCFG registers
#define SYSCFG_EXTICR  (*(volatile uint32_t *)(SYSCFG_BASE + 0x08))

// EXTI registers
#define EXTI_IMR       (*(volatile uint32_t *)(EXTI_BASE + 0x00))
#define EXTI_FTSR      (*(volatile uint32_t *)(EXTI_BASE + 0x0C))
#define EXTI_RTSR      (*(volatile uint32_t *)(EXTI_BASE + 0x08))
#define EXTI_PR        (*(volatile uint32_t *)(EXTI_BASE + 0x14))

// NVIC registers
#define NVIC_ISER0     (*(volatile uint32_t *)(NVIC_BASE + 0x00))

// Define the IRQ number for EXTI0
#define EXTI0_IRQn     6

// Enable clock for GPIOA, GPIOC, and SYSCFG
void enable_clocks() {
    // Enable clock for GPIOA
    RCC_AHB1ENR |= (1 << 0);  // GPIOAEN
    
    // Enable clock for GPIOC
    RCC_AHB1ENR |= (1 << 2);  // GPIOCEN
    
    // Enable clock for SYSCFG (for EXTI configuration)
    RCC_APB2ENR |= (1 << 14); // SYSCFGEN
}

// Configure GPIOA0 as input for the button
void configure_gpioA0() {
    // Set PA0 as input (00 in MODER)
    GPIOA_MODER &= ~(0x3 << 0);  // Clear mode for pin 0
    
    // Enable pull-up on PA0 (01 in PUPDR)
    GPIOA_PUPDR |= (0x1 << 0);   // Set pull-up for pin 0
}

// Configure GPIOC13 as output for the LED
void configure_gpioC13() {
    // Set PC13 as output (01 in MODER)
    GPIOC_MODER &= ~(0x3 << 26);  // Clear mode for pin 13
    GPIOC_MODER |= (0x1 << 26);   // Set pin 13 to output mode
}

// Configure EXTI for PA0
void configure_exti() {
    
    // Connect EXTI0 to PA0 (EXTICR1 for EXTI0)
    SYSCFG_EXTICR &= ~(0xF << 0);  // Clear EXTI0 configuration
    SYSCFG_EXTICR |= (0x0 << 0);   // Map PA0 to EXTI0
    
    // Enable interrupt on EXTI0 (unmask interrupt line)
    EXTI_IMR |= (1 << 0);
    
    // Configure falling edge trigger (FTSR)
    EXTI_FTSR |= (1 << 0);
    
    // Ensure rising edge trigger is disabled
    EXTI_RTSR &= ~(1 << 0);
    
    // Clear any pending interrupt on EXTI0 by setting the bit in EXTI_PR
    EXTI_PR |= (1 << 0);
}

// Enable NVIC interrupt for EXTI0
void enable_nvic() {
    // Enable EXTI0 interrupt in NVIC
    NVIC_ISER0 |= (1 << EXTI0_IRQn);
}


void delay(uint32_t t)
{
	uint32_t i = 0;
	while(i < t)
	{
		i++;
	}
}

// The main function to configure the system
int main() {
    EXTI_PR |= (1 << 0);
    enable_clocks();     // Enable clocks for GPIOA, GPIOC, and SYSCFG
    EXTI_PR |= (1 << 0);
    configure_gpioA0();  // Configure PA0 as input for the button
    configure_gpioC13(); // Configure PC13 as output for the LED
    EXTI_PR |= (1 << 0);
    configure_exti();    // Configure EXTI for PA0 (button)
    enable_nvic();       // Enable EXTI0 interrupt in NVIC

    // Main loop (waiting for interrupt)
    while (1) {
        // Optional: Turn off the LED if it's on (can be used for testing)
        GPIOC_ODR |= (1 << 13);  // Turn off LED
        delay(200000);
    }
}

// EXTI0 interrupt handler (ISR)
void EXTI0_IRQHandler(void) {
    // Check if the interrupt is from EXTI0
    if (EXTI_PR & (1 << 0)) {
        // Clear the interrupt flag for EXTI0
        EXTI_PR |= (1 << 0);
        
        for (uint8_t i = 0; i < 10; i++)
        {
            // Toggle the LED connected to PC13
            GPIOC_ODR ^= (1 << 13);  // Toggle LED state
            delay(1000000);
        
        }

        
    }
}


*/


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


int main()
{

    
	GPIO_Handle_t GpioLed, GpioButton;
	//memset(&GpioLed,0,sizeof(GpioLed));
	//memset(&GpioButton,0,sizeof(GpioButton));
	
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
	while(1)
	{
		//if(GPIO_ReadFromInputPin(GPIOA,0) == LOW )
		{
			delay(200000);
			//GPIO_ToggleOutputPin(GPIOC,GPIO_PIN_NO_13);
			
		}
		
	}

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
   

