#include "stm32f3_gpio_driver.h"

// peripheral clock setup
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnOrDi)
{
	if( EnOrDi == ENABLE )
	{
		if( pGPIOx == GPIOA )
		{
			GPIOA_PCLK_EN();
		}
		else if( pGPIOx == GPIOB )
		{
			GPIOB_PCLK_EN();
		}
		else if( pGPIOx == GPIOC )
		{
			GPIOC_PCLK_EN();
		}
		else if( pGPIOx == GPIOD )
		{
			GPIOD_PCLK_EN();
		}
		else if( pGPIOx == GPIOE )
		{
			GPIOE_PCLK_EN();
		}
		else if( pGPIOx == GPIOF )
		{
			GPIOF_PCLK_EN();
		}
	}
	else
	{
		if( pGPIOx == GPIOA )
		{
			GPIOA_PCLK_DI();
		}
		else if( pGPIOx == GPIOB )
		{
			GPIOB_PCLK_DI();
		}
		else if( pGPIOx == GPIOC )
		{
			GPIOC_PCLK_DI();
		}
		else if( pGPIOx == GPIOD )
		{
			GPIOD_PCLK_DI();
		}
		else if( pGPIOx == GPIOE )
		{
			GPIOE_PCLK_DI();
		}
		else if( pGPIOx == GPIOF )
		{
			GPIOF_PCLK_DI();
		}
	}
}

// init and deinit
void GPIO_Init(GPIO_Handle_t *pGPIO_Handle)
{
	uint32_t temp = 0;
	// configure mode
	if( pGPIO_Handle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG )
	{
		temp = pGPIO_Handle->GPIO_PinConfig.GPIO_PinMode << (2 * pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber);
		pGPIO_Handle->pGPIOx->MODER &= ~(0x3 << pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber);
		pGPIO_Handle->pGPIOx->MODER |= temp;
	}
	else  // interrupt mode
	{
		if( pGPIO_Handle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_IT_FT )
		{
			// 1 .configure the FTSR
			EXTI->FTSR |= (1 << pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->RTSR &= ~(1 << pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber);
		}
		else if( pGPIO_Handle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_IT_RT )
		{
			// 1. configure the RTSR
			EXTI->FTSR &= ~(1 << pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->RTSR |= (1 << pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber);
		}
		else if( pGPIO_Handle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_IT_RFT )
		{
			// 1. configure the FTSR and RTST
			EXTI->FTSR |= (1 << pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->RTSR |= (1 << pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber);
		}
		// 2. configure the GPIO port selection in SYSCFG_EXTICR
		uint8_t temp1 = pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber / 4;
		uint8_t temp2 = pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber % 4;
		uint8_t portcode = GPIO_BASEADDR_TO_CODE(pGPIO_Handle->pGPIOx);
		SYSCFG_PCLK_EN();
		SYSCFG->EXTICR[temp1] = portcode << ( temp2 * 4);
		// 3. enable the EXTI interrupt delivery using IMR
		EXTI->IMR |= 1 << pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber;
	}
	temp = 0;
	// configure speed
	temp = pGPIO_Handle->GPIO_PinConfig.GPIO_PinSpeed << (2 * pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIO_Handle->pGPIOx->OSPEEDR &= ~(0x3 << pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIO_Handle->pGPIOx->OSPEEDR |= temp;

	temp = 0;
	// configure pull up pull down
	temp = pGPIO_Handle->GPIO_PinConfig.GPIO_PinPuPdControl << (2 * pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIO_Handle->pGPIOx->PUPDR &= ~(0x3 << pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIO_Handle->pGPIOx->PUPDR |= temp;

	temp = 0;
	// configure output type
	temp = pGPIO_Handle->GPIO_PinConfig.GPIO_PinOPType << pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber;
	pGPIO_Handle->pGPIOx->OTYPER &= ~(0x1 << pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIO_Handle->pGPIOx->OTYPER |= temp;

	// configure alternative if require
	if( pGPIO_Handle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN )
	{
		// configure the alternative function register
		uint32_t temp1, temp2;
		temp1 = pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber/8;
		temp2 = pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber%8;
		pGPIO_Handle->pGPIOx->AFR[temp1] &= ~( 0xF << (4*temp2));
		pGPIO_Handle->pGPIOx->AFR[temp1] |= pGPIO_Handle->GPIO_PinConfig.GPIO_PinAltFunMode << (4*temp2);
	}
}
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
{

	if( pGPIOx == GPIOA )
	{
		GPIOA_PCLK_EN();
	}
	else if( pGPIOx == GPIOB )
	{
		GPIOB_PCLK_EN();
	}
	else if( pGPIOx == GPIOC )
	{
		GPIOC_PCLK_EN();
	}
	else if( pGPIOx == GPIOD )
	{
		GPIOD_PCLK_EN();
	}
	else if( pGPIOx == GPIOE )
	{
		GPIOE_PCLK_EN();
	}
	else if( pGPIOx == GPIOF )
	{
		GPIOF_PCLK_EN();
	}
}

// data read write
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	uint8_t value;
	value = (uint8_t) ( (pGPIOx->IDR >> PinNumber) & 0x00000001 );
	return value;
}

uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
{
	uint16_t value;
	value = (uint16_t) (pGPIOx->IDR);
	return value;
}

void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value)
{
	if(Value == GPIO_PIN_SET)
	{
		pGPIOx->ODR |= (1<<PinNumber);
	}
	else
	{
		pGPIOx->ODR &= ~(1<<PinNumber);
	}
}

void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value)
{
	pGPIOx->ODR = Value;
}
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	pGPIOx->ODR ^= (1<<PinNumber);
}

// interrupt
void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnOrDi)
{
	if(EnOrDi==ENABLE)
	{
		if( IRQNumber <=31 )
		{
			// program ISER0
			*NVIC_ISER0 |= ( 1 << IRQNumber );
		}else if ( IRQNumber >31 && IRQNumber < 64)
		{
			// program ISER1
			*NVIC_ISER1 |= ( 1 << (IRQNumbe%32) );
		}else if ( IRQNumber >64 && IRQNumber < 96)
		{
			// program ISER2
			*NVIC_ISER2 |= ( 1 << (IRQNumbe%32) );
		}
	}
	else
	{
		if( IRQNumber <=31 )
		{
			// program ICER0
			*NVIC_ICER0 |= ( 1 << IRQNumber );
		}else if ( IRQNumber >31 && IRQNumber < 64)
		{
			// program ICER1
			*NVIC_ICER1 |= ( 1 << (IRQNumbe%32) );
		}else if ( IRQNumber >64 && IRQNumber < 96)
		{
			// program ICER2
			*NVIC_ICER2 |= ( 1 << (IRQNumbe%32) );
		}
	}
}
void GPIO_IRQHandling(uint8_t PinNumber)
{
	if( EXTI->PR & (1<<PinNumber) )
	{
		EXTI->PR |= ( 1<<PinNumber );
	}
}
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority)
{
	// find ipr register
	uint8_t iprx = IRQNumber / 4;
	uint8_t iprx_section = IRQNumber % 4;

	uint8_t shift_amount = ( 8 * iprx_section ) + ( 8 - NO_PR_BITS_IMPLEMENTED );
	*(NVIC_PR_BASEADDR + (iprx*4) ) |= ( IRQPriority << shift_amount );

}



