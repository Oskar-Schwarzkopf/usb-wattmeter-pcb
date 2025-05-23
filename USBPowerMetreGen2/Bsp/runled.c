//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//
//
//
//
//******************************************************************************/。

#include "runled.h"

void runled_init(void)
{
  GPIO_Init(RUNLED_PORT, RUNLED_PINS, GPIO_MODE_OUT_PP_LOW_SLOW);
  RUNLEDOFF;
  GPIO_Init(ERRLED_PORT, ERRLED_PINS, GPIO_MODE_OUT_PP_LOW_SLOW);
  ERRLEDOFF;
}


