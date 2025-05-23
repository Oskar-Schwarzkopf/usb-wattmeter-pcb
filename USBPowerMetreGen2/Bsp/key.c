#include"key.h"
#include"delay.h"
void key_init(void)
{
  GPIO_Init(KEY1_PORT, KEY1_PINS, GPIO_MODE_IN_PU_NO_IT);  
  GPIO_Init(KEY2_PORT, KEY2_PINS, GPIO_MODE_IN_PU_NO_IT); 
}
uint8_t keyscan(void)
{
  static uint8_t key_lock=1;
  if(key_lock&&(READKEY1==0||READKEY2==0)){
    Delay_ms(10);
    key_lock=0;
    if(READKEY1==0)
      return KEY1;
    if(READKEY2==0)
      return KEY2;
  }
  if(key_lock==0&&(READKEY1&&READKEY2)){
    Delay_ms(10);
    if(READKEY1&&READKEY2)
      key_lock=1;
  }
  // if(READKEY1 == 0)
  // {
  //   Delay_ms(10);
  //   if(READKEY1 == 0)
  //   {
  //     return 0x01;
  //   }
  // }
  // else if(READKEY2 == 0)
  // {
  //   Delay_ms(10);
  //   if(READKEY2 == 0)
  //     return 0x02;
  // }
  // else if(READKEY3 == 0)
  // {
  //   Delay_ms(10);
  //   if(READKEY3 == 0)
  //     return 0x03;
  // }
  return 0;
}
