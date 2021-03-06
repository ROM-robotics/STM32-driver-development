/*
 * stm32f3discovery.h
 *
 *  Created on: Sep 8, 2021
 *      Author: robot
 */

#ifndef INC_STM32F3DISCOVERY_H_
#define INC_STM32F3DISCOVERY_H_

#include <stdint.h>

#define __vo						volatile

// PROcessor specific peripherals
#define NVIC_ISER0					(__vo uint32_t*)0xE000E100;
#define NVIC_ISER1					(__vo uint32_t*)0xE000E104;
#define NVIC_ISER2					(__vo uint32_t*)0xE000E108;
#define NVIC_ISER3					(__vo uint32_t*)0xE000E10C;

#define NVIC_ICER0					(__vo uint32_t*)0xE000E180;
#define NVIC_ICER1					(__vo uint32_t*)0xE000E184;
#define NVIC_ICER2					(__vo uint32_t*)0xE000E188;
#define NVIC_ICER3					(__vo uint32_t*)0xE000E18C;

#define NVIC_PR_BASEADDR			(__vo uint32_t*)0xE000E400;
#define NO_PR_BITS_IMPLEMENTED		4

//
#define FLASH_BASEADDR				0x08000000U
#define SRAM1_BASEADDR				0x20000000U
#define SRAM 						SRAM1_BASEADDR
#define ROM_BASEADDR				0x1FFFD800U       // SYSTEM MEMORY

// various bus domains
#define PERIPH_BASEADDR				0x40000000U
#define APB1PERIPH_BASEADDR			PERIPH_BASEADDR
#define APB2PERIPH_BASEADDR			0x40010000U
#define AHB1PERIPH_BASEADDR			0x40020000U
#define AHB2PERIPH_BASEADDR			0x48000000U

// AHB1 PERIPHERAL
#define RCC_BASEADDR				(AHB1PERIPH_BASEADDR+ 0x1000)
// AHB2 PERIPHERAL
#define GPIOA_BASEADDR				(AHB2PERIPH_BASEADDR+ 0x0000)
#define GPIOB_BASEADDR				(AHB2PERIPH_BASEADDR+ 0x0400)
#define GPIOC_BASEADDR				(AHB2PERIPH_BASEADDR+ 0x0800)
#define GPIOD_BASEADDR				(AHB2PERIPH_BASEADDR+ 0x0C00)
#define GPIOE_BASEADDR				(AHB2PERIPH_BASEADDR+ 0x1000)
#define GPIOF_BASEADDR				(AHB2PERIPH_BASEADDR+ 0x0400)

// APB1 PERIPHERAL
#define I2C1_BASEADDR				(APB1PERIPH_BASEADDR+ 0x5400)
#define I2C2_BASEADDR				(APB1PERIPH_BASEADDR+ 0x5800)

#define SPI2_BASEADDR				(APB1PERIPH_BASEADDR+ 0x3800)
#define SPI3_BASEADDR				(APB1PERIPH_BASEADDR+ 0x3C00)

#define USART2_BASEADDR				(APB1PERIPH_BASEADDR+ 0x4400)
#define USART3_BASEADDR				(APB1PERIPH_BASEADDR+ 0x4800)
#define UART4_BASEADDR				(APB1PERIPH_BASEADDR+ 0x4C00)
#define UART5_BASEADDR				(APB1PERIPH_BASEADDR+ 0x5000)

// APB2 PERIPHERAL
#define EXTI_BASEADDR				(APB2PERIPH_BASEADDR+ 0x0400)
#define SYSCFG_BASEADDR				(APB2PERIPH_BASEADDR+ 0x0000)

#define SPI1_BASEADDR				(APB2PERIPH_BASEADDR+ 0x3000)
#define SPI4_BASEADDR				(APB2PERIPH_BASEADDR+ 0x3C00)

#define USART1_BASEADDR				(APB2PERIPH_BASEADDR+ 0x3800)

// peripheral register definition register
typedef struct {
	__vo uint32_t MODER;
	__vo uint32_t OTYPER;
	__vo uint32_t OSPEEDR;
	__vo uint32_t PUPDR;
	__vo uint32_t IDR;
	__vo uint32_t ODR;
	__vo uint32_t BSRR;
	__vo uint32_t LCKR;
	__vo uint32_t AFR[2];
	__vo uint32_t BRR;
}GPIO_RegDef_t;

typedef struct {
	__vo uint32_t CR;
	__vo uint32_t CFGR;
	__vo uint32_t CIR;
	__vo uint32_t APB2RSTR;
	__vo uint32_t APB1RSTR;
	__vo uint32_t AHBENR;
	__vo uint32_t APB2ENR;
	__vo uint32_t APB1ENR;
	__vo uint32_t BDCR;
	__vo uint32_t CSR;
	__vo uint32_t AHBRSTR;
	__vo uint32_t CFGR2;
	__vo uint32_t CFGR3;
}RCC_RegDef_t;

typedef struct {
	__vo uint32_t IMR;
	__vo uint32_t EMR;
	__vo uint32_t RTSR;
	__vo uint32_t FTSR;
	__vo uint32_t SWIER;
	__vo uint32_t PR;
}EXTI_RegDef_t;

typedef struct {
	__vo uint32_t MEMRMP;
	__vo uint32_t PMC;
	__vo uint32_t EXTICR[4];
	uint32_t RESERVED1[1];
	__vo uint32_t CMPCR;
	uint32_t RESERVED2[2];
	__vo uint32_t CFGR;
}SYSCFG_RegDef_t;

// peripheral definition
#define GPIOA						((GPIO_RegDef_t*)GPIOA_BASEADDR )
#define GPIOB						((GPIO_RegDef_t*)GPIOB_BASEADDR )
#define GPIOC						((GPIO_RegDef_t*)GPIOC_BASEADDR )
#define GPIOD						((GPIO_RegDef_t*)GPIOD_BASEADDR )
#define GPIOE						((GPIO_RegDef_t*)GPIOE_BASEADDR )
#define GPIOF						((GPIO_RegDef_t*)GPIOF_BASEADDR )

#define RCC							((RCC_RegDef_t*)RCC_BASEADDR )
#define EXTI						((EXTI_RegDef_t*)EXTI_BASEADDR )
#define SYSCFG						((SYSCFG_RegDef_t*)SYSCFG_BASEADDR )

// clock enable for gpioX peripheral
#define GPIOA_PCLK_EN()				( RCC->AHBENR |= (1<<17) )
#define GPIOB_PCLK_EN()				( RCC->AHBENR |= (1<<18) )
#define GPIOC_PCLK_EN()				( RCC->AHBENR |= (1<<19) )
#define GPIOD_PCLK_EN()				( RCC->AHBENR |= (1<<20) )
#define GPIOE_PCLK_EN()				( RCC->AHBENR |= (1<<21) )
#define GPIOF_PCLK_EN()				( RCC->AHBENR |= (1<<22) )

// clock enable for I2C peripheral
#define I2C1_PCLK_EN()				( RCC->APB1ENR |= (1<<21) )
#define I2C2_PCLK_EN()				( RCC->APB1ENR |= (1<<22) )
// clock enable for SPI peripheral
#define SPI1_PCLK_EN()				( RCC->APB2ENR |= (1<<12) )
#define SPI2_PCLK_EN()				( RCC->APB1ENR |= (1<<14) )
#define SPI3_PCLK_EN()				( RCC->APB1ENR |= (1<<15) )
#define SPI4_PCLK_EN()				( RCC->APB2ENR |= (1<<15) )
// clock enable for USART peripheral
#define USART1_PCLK_EN()			( RCC->APB2ENR |= (1<<14) )
#define USART2_PCLK_EN()			( RCC->APB1ENR |= (1<<17) )
#define USART3_PCLK_EN()			( RCC->APB1ENR |= (1<<18) )
#define UART4_PCLK_EN()				( RCC->APB1ENR |= (1<<19) )
#define UART5_PCLK_EN()				( RCC->APB1ENR |= (1<<20) )

// clock enable macro for syscfg peripheral
#define SYSCFG_PCLK_EN()			( RCC->APB2ENR |= (1<<0)  )
// clock disable for gpioX peripheral
#define GPIOA_PCLK_DI()				( RCC->AHBENR &= ~(1<<17) )
#define GPIOB_PCLK_DI()				( RCC->AHBENR &= ~(1<<18) )
#define GPIOC_PCLK_DI()				( RCC->AHBENR &= ~(1<<19) )
#define GPIOD_PCLK_DI()				( RCC->AHBENR &= ~(1<<20) )
#define GPIOE_PCLK_DI()				( RCC->AHBENR &= ~(1<<21) )
#define GPIOF_PCLK_DI()				( RCC->AHBENR &= ~(1<<22) )

// clock disable for I2C peripheral
#define I2C1_PCLK_DI()				( RCC->APB1ENR &= ~(1<<21) )
#define I2C2_PCLK_DI()				( RCC->APB1ENR &= ~(1<<22) )
// clock disable for SPI peripheral
#define SPI1_PCLK_DI()				( RCC->APB2ENR &= ~(1<<12) )
#define SPI2_PCLK_DI()				( RCC->APB1ENR &= ~(1<<14) )
#define SPI3_PCLK_DI()				( RCC->APB1ENR &= ~(1<<15) )
#define SPI4_PCLK_DI()				( RCC->APB2ENR &= ~(1<<15) )
// clock disable for USART peripheral
#define USART1_PCLK_DI()			( RCC->APB2ENR &= ~(1<<14) )
#define USART2_PCLK_DI()			( RCC->APB1ENR &= ~(1<<17) )
#define USART3_PCLK_DI()			( RCC->APB1ENR &= ~(1<<18) )
#define UART4_PCLK_DI()				( RCC->APB1ENR &= ~(1<<19) )
#define UART5_PCLK_DI()				( RCC->APB1ENR &= ~(1<<20) )

// gpio reset
#define GPIOA_REG_RESET()			do{( RCC->AHBRSTR |= (1<<17) );  ~( RCC->AHBRSTR &= (1<<17) );}while(0)
#define GPIOB_REG_RESET()			do{( RCC->AHBRSTR |= (1<<18) );  ~( RCC->AHBRSTR &= (1<<18) );}while(0)
#define GPIOC_REG_RESET()			do{( RCC->AHBRSTR |= (1<<19) );  ~( RCC->AHBRSTR &= (1<<19) );}while(0)
#define GPIOD_REG_RESET()			do{( RCC->AHBRSTR |= (1<<20) );  ~( RCC->AHBRSTR &= (1<<20) );}while(0)
#define GPIOE_REG_RESET()			do{( RCC->AHBRSTR |= (1<<21) );  ~( RCC->AHBRSTR &= (1<<21) );}while(0)
#define GPIOF_REG_RESET()			do{( RCC->AHBRSTR |= (1<<22) );  ~( RCC->AHBRSTR &= (1<<22) );}while(0)

#define GPIO_BASEADDR_TO_CODE(x)    ( (x == GPIOA) ? 0 : \
									  (x == GPIOB) ? 1 : \
									  (x == GPIOC) ? 2 : \
									  (x == GPIOD) ? 3 : \
									  (x == GPIOE) ? 4 : \
									  (x == GPIOF) ? 5 :0 )

// IRQ NUMBERS
#define IRQ_NO_EXTI0				6
#define IRQ_NO_EXTI1				7
#define IRQ_NO_EXTI2				8
#define IRQ_NO_EXTI3				9
#define IRQ_NO_EXTI4				10
#define IRQ_NO_EXTI9_5				23
#define IRQ_NO_EXTI15_10			40

// somge generic macro
#define ENABLE 						1
#define DISABLE 					0
#define SET 						ENABLE
#define RESET						DISABLE
#define GPIO_PIN_SET				SET
#define GPIO_PIN_RESET				RESET




#include "stm32f3_gpio_driver.h"


#endif /* INC_STM32F3DISCOVERY_H_ */

