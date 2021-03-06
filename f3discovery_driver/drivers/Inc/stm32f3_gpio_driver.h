/*
 * stm32f3_gpio_driver.h
 *
 *  Created on: Sep 9, 2021
 *      Author: robot
 */

#ifndef INC_STM32F3_GPIO_DRIVER_H_
#define INC_STM32F3_GPIO_DRIVER_H_

#include "stm32f3discovery.h"

typedef struct{
	uint8_t GPIO_PinNumber;
	uint8_t GPIO_PinMode;
	uint8_t GPIO_PinSpeed;
	uint8_t GPIO_PinPuPdControl;
	uint8_t GPIO_PinOPType;
	uint8_t GPIO_PinAltFunMode;
}GPIO_PinConfig_t;

typedef struct{
	GPIO_RegDef_t *pGPIOx; // this hold base address
	GPIO_PinConfig_t GPIO_PinConfig; // this hold gpio pin configuration setting
}GPIO_Handle_t;

// gpio pin possible mode
#define GPIO_MODE_IN			0
#define GPIO_MODE_OUT			1
#define GPIO_MODE_ALTFN			2
#define GPIO_MODE_ANALOG		3
#define GPIO_MODE_IT_FT			4
#define GPIO_MODE_IT_RT			5
#define GPIO_MODE_IT_RFT		6

// gpio possible output type
#define GPIO_OP_TYPE_PP			0
#define GPIO_OP_TYPE_OD			1

// gpio possible output speed
#define GPIO_SPEED_LOW			0
#define GPIO_SPEED_MEDIUM		1
#define GPIO_SPEED_FAST			2
#define GPIO_SPEED_HIGH			3

// gpio pull up pull down
#define GPIO_NO_PUPD			0
#define GPIO_PIN_PU  			1
#define GPIO_PIN_PD  			2

/*
 * @GPIO_PIN_NUMBERS
 * GPIO pin numbers
 */
#define GPIO_PIN_NO_0			0
#define GPIO_PIN_NO_1			1
#define GPIO_PIN_NO_2			2
#define GPIO_PIN_NO_3			3
#define GPIO_PIN_NO_4			4
#define GPIO_PIN_NO_5			5
#define GPIO_PIN_NO_6			6
#define GPIO_PIN_NO_7			7
#define GPIO_PIN_NO_8			8
#define GPIO_PIN_NO_9			9
#define GPIO_PIN_NO_10			10
#define GPIO_PIN_NO_11			11
#define GPIO_PIN_NO_12			12
#define GPIO_PIN_NO_13			13
#define GPIO_PIN_NO_14			14
#define GPIO_PIN_NO_15			15

// peripheral clock setup
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnOrDi);

// init and deinit
void GPIO_Init(GPIO_Handle_t *pGPIO_Handle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);

// data read write
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value);
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value);
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);

// interrupt
void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnOrDi);
void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnOrDi);
void GPIO_IRQHandling(uint8_t PinNumber);
void GPIO_IRQPriorityConfig(uint8_t IRQPriority);



#endif /* INC_STM32F3_GPIO_DRIVER_H_ */
