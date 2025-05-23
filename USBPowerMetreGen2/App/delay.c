#include "delay.h"

//ms级别延时
void Delay_ms(uint16_t nCount)
{
  while(nCount--)
  {
    Delay_us(1000);
  }
}

//us级别延时
void Delay_us(uint16_t nCount)
{
//  nCount *= 2;
  while(--nCount)
  {
    asm("nop");
    asm("nop");
    asm("nop");
    
  }
}