#include"stm8s_clk.h"
#include "sys_init.h"
#include "key.h"
#include"oled.h"
#include"stm8s_adc1.h"
#include"adcx.h"
#include"runled.h"
void SysCLK_init(void){
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
}
void Device_init(void)
{
    key_init();
    OLED_Init();
    runled_init();
    adc_init();
}