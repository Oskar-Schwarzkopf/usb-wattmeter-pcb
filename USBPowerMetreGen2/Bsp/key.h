#ifndef __KEY_H
#define __KEY_H			  	 
#include "stm8s.h"

#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据
#define OLED_MODE 0

/****************按键1*********************/
#define KEY1_PORT  (GPIOC)
#define KEY1_PINS  (GPIO_PIN_4)
#define KEY1 1

/****************按键2*********************/
#define KEY2_PORT  (GPIOC)
#define KEY2_PINS  (GPIO_PIN_5)
#define KEY2 2

#define READKEY1 GPIO_ReadInputPin(KEY1_PORT, KEY1_PINS)
#define READKEY2 GPIO_ReadInputPin(KEY2_PORT, KEY2_PINS)  

void key_init(void);
uint8_t keyscan(void);

#endif

	 



