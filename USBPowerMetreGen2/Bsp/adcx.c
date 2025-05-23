#include"adcx.h"
#include"stm8s.h"
#include"stm8s_adc1.h"
#include"runled.h"
float ulat,ilat;
uint8_t uflag=1,iflag=1;
void adc_init(){
    GPIO_Init(UMES_PORT, UMES_PINS, GPIO_MODE_IN_PU_NO_IT);
    GPIO_Init(IMES1_PORT, IMES1_PINS, GPIO_MODE_IN_PU_NO_IT);
    GPIO_Init(IMES2_PORT, IMES2_PINS, GPIO_MODE_IN_PU_NO_IT);
    GPIO_Init(IMESREF_PORT, IMESREF_PINS, GPIO_MODE_IN_PU_NO_IT);
}

uint16_t umes_read(){
    ADC1_Init(ADC1_CONVERSIONMODE_SINGLE,
        UMES_ADC_CHANNEL,
        ADC1_PRESSEL_FCPU_D8,
        ADC1_EXTTRIG_TIM,
        DISABLE,
        ADC1_ALIGN_RIGHT,
        UMES_ADC_CHANNEL,
        DISABLE);
    return ADC1_GetConversionValue();
}
uint16_t imes1_read(){
    ADC1_Init(ADC1_CONVERSIONMODE_SINGLE,
        IMES1_ADC_CHANNEL,
        ADC1_PRESSEL_FCPU_D8,
        ADC1_EXTTRIG_TIM,
        DISABLE,
        ADC1_ALIGN_RIGHT,
        IMES1_ADC_CHANNEL,
        DISABLE);
    return ADC1_GetConversionValue();
}
uint16_t imes2_read(){
    ADC1_Init(ADC1_CONVERSIONMODE_SINGLE,
        IMES2_ADC_CHANNEL,
        ADC1_PRESSEL_FCPU_D8,
        ADC1_EXTTRIG_TIM,
        DISABLE,
        ADC1_ALIGN_RIGHT,
        IMES2_ADC_CHANNEL,
        DISABLE);
    return ADC1_GetConversionValue();
}
uint16_t imesref_read(){
    ADC1_Init(ADC1_CONVERSIONMODE_SINGLE,
        IMESREF_ADC_CHANNEL,
        ADC1_PRESSEL_FCPU_D8,
        ADC1_EXTTRIG_TIM,
        DISABLE,
        ADC1_ALIGN_RIGHT,
        IMESREF_ADC_CHANNEL,
        DISABLE);
    return ADC1_GetConversionValue();
}
float Get_U_Value(){
    // static float U_Temp[4];
    // U_Temp[0]=umes_read()*3.3*2/1024;
    // U_Temp[1]=umes_read()*3.3*2/1024;
    // U_Temp[2]=umes_read()*3.3*2/1024;
    // U_Temp[3]=umes_read()*3.3*2/1024;
    if(uflag){
        ulat=umes_read()*3.3*2/1024;
        uflag=0;
    }else 
        ulat=ulat*0.5+umes_read()*3.3*2/1024*0.5;
    return ulat;
}
float Get_I_Value(){
    // return (float)(imes2_read()-imesref_read())/1024*3.3/0.264;
    static float itmp;
    if(imes1_read()>=1020){//如果放大后的量程满了
        itmp=(float)(imes2_read()-imesref_read())/1024*3.3/0.264;
    }else {
        itmp=(float)imes1_read()/1024*3.3/0.264/6.6;
    }
    // itmp=(float)(imes2_read()-imesref_read())/1024*3.3/0.264;
    if(iflag){
        ilat=itmp;
        iflag=0;
    }else ilat=ilat*0.9+itmp*0.1;
    return ilat;
    // return ((float)(imes2_read()-imesref_read())/1024*3.3/0.264+(float)(imes2_read()-imesref_read())/1024*3.3/0.264+(float)(imes2_read()-imesref_read())/1024*3.3/0.264)/3;
}
//10位精度，512-1.65V-5A
/*
*/