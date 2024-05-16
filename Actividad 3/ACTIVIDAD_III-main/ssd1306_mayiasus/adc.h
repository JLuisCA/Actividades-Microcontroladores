/*
 * adc.h
 *
 * Created: 
 *  Author: jlb
 */ 


#ifndef adc_H_
#define adc_H_
void init_adc_withINT(void);
void init_adc_withoutINT(void);
uint16_t read_adc0(void);
uint16_t read_adc1(void);
uint16_t read_adc2(void);
void oled_adc_valor(void);
void oled_adc_valor1(void);
void oled_adc_valor2(void);
#endif /* adc_H_ */