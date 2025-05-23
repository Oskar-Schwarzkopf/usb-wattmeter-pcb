//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//
//
//
//
//******************************************************************************/。

#ifndef __RUNLED_H
#define __RUNLED_H			  	 
#include "stm8s.h"

/****************按键1*********************/
#define RUNLED_PORT  (GPIOC)
#define RUNLED_PINS  (GPIO_PIN_6)
#define ERRLED_PORT  (GPIOC)
#define ERRLED_PINS  (GPIO_PIN_7)

#define RUNLEDFLASH GPIO_WriteReverse(RUNLED_PORT, RUNLED_PINS)
#define RUNLEDOFF GPIO_WriteHigh(RUNLED_PORT, RUNLED_PINS)
#define ERRLEDFLASH GPIO_WriteReverse(ERRLED_PORT, ERRLED_PINS)
#define ERRLEDOFF GPIO_WriteHigh(ERRLED_PORT, ERRLED_PINS)

void runled_init(void);

#endif

	 



