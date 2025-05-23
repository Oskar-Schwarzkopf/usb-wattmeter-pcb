#include"adcx.h"
#include"key.h"
#include"oled.h"
#include"runled.h"
#include"sys_init.h"
#include"delay.h"
#include"disp.h"
#include"stm8s.h"
int main(){
    // GPIO_Init(GPIOC, GPIO_PIN_6, GPIO_MODE_OUT_PP_LOW_SLOW);
    // GPIO_Init(GPIOC, GPIO_PIN_7, GPIO_MODE_OUT_PP_LOW_SLOW);
    // while(1){
    //     GPIO_WriteReverse(GPIOC,GPIO_PIN_6);
    //     GPIO_WriteReverse(GPIOC,GPIO_PIN_7);
    //     Delay_ms(200);
    // }
    uint8_t key,disp_state=0,disp_cnt=0;
    SysCLK_init();
    Device_init();
    Disp_init();
    Disp_Welcome();
    // while(1){
    //     RUNLEDFLASH;
    //     Delay_ms(200);
    // }
    while(1){
        key=keyscan();
        if(key){
            // if(disp_state==0)
            //     disp_state=1;
            RUNLEDFLASH;
            Delay_ms(40);
            RUNLEDFLASH;
        }
        if(key==KEY2){
            disp_state++;
            if(disp_state==5)
                disp_state=1;
        }else if(key==KEY3){
            disp_state--;
            if(disp_state==0)
                disp_state=4;
        }
        disp_cnt++;
        if(disp_cnt>=50){
            if(disp_state==1){
                Disp_Digit_Mode();
            }else if(disp_state==2){
                Disp_Power_Mode();
            }else if(disp_state==3){
                Disp_U_Mode();
            }else if(disp_state==4){
                Disp_I_Mode();
            }
            disp_cnt=0;
        }
        Delay_ms(20);
    }
}
#ifdef USE_FULL_ASSERT

void assert_failed(u8* file, u32 line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
    
  }
}
#endif

/*
欢迎界面1、数字模式2、功率图表模式3、电压图表模式4、电流图表模式5，按键1控制放大、缩小

这个的性能足够读出纹波吗？不行吧。
0缩放时间尺度为30s，1缩放时间尺度5s
128
ram 1kb
放弃缩放功能
有待改进的：按键逻辑、部分刷新、放弃U\I曲线、错误的电流测量、低通滤波、电流测量芯片的供电电压的改动，错误的按键连接方式。
1.65v-5A
0.495v-1.5A
3.3v-放大约6.6倍。
*/