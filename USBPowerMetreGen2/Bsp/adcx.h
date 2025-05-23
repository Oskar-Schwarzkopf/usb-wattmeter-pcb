#ifndef __ADC_H
#define __ADC_H		
#include"stm8s.h"
#include"stm8s_adc1.h"

#define UMES_PORT  (GPIOD)
#define UMES_PINS  (GPIO_PIN_6)
#define UMES_ADC_CHANNEL ADC1_CHANNEL_6

#define IMES1_PORT  (GPIOD)
#define IMES1_PINS  (GPIO_PIN_3)
#define IMES1_ADC_CHANNEL ADC1_CHANNEL_4

#define IMES2_PORT  (GPIOD)
#define IMES2_PINS  (GPIO_PIN_5)
#define IMES2_ADC_CHANNEL ADC1_CHANNEL_5

#define IMESREF_PORT  (GPIOD)
#define IMESREF_PINS  (GPIO_PIN_2)
#define IMESREF_ADC_CHANNEL ADC1_CHANNEL_3

void adc_init();
uint16_t umes_read();
uint16_t imes1_read();
uint16_t imes2_read();
uint16_t imesref_read();
float Get_U_Value();
float Get_I_Value();
#endif