/*
 * adc.c
 *
 * Created: 
 *  Author: jlb
 */ 
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>	//conversion to ASCII
#include <avr/interrupt.h>
#include "ssd1306.h"
#include <util/delay.h>
#define POT_PIN_ADC0 0
#define POT_PIN_ADC1 1
#define POT_PIN_ADC2 2

void init_adc_withoutINT(void)
{
	ADMUX=(1<<REFS0);	//selects Vref 
						//(AVCC with external capacitor at AREF pin)
						//Entrada AVcc= 5v y Aref= con un capacitor a GND
						//Internamente: Vref=0-5v
	ADCSRA = (1<<ADEN);//enable ADC
	ADCSRA = (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);	//Prescaler div factor =128
												//fo=1,000,000/128 ~ 7Khz
}

uint16_t read_adc0(void)
{
	ADMUX = (ADMUX & 0xF8)|POT_PIN_ADC0;				//Selects ADC channel (0-5)
	ADCSRA|=(1<<ADSC);				//start conversion
	while(!(ADCSRA & (1<<ADIF)));	//wait for conversion complete
	ADCSRA|=(1<<ADIF);				//clear flag for next conversion
	return(ADC);					//return sample value
}

uint16_t read_adc1(void)
{
	ADMUX = (ADMUX & 0xF8)|POT_PIN_ADC1;				//Selects ADC channel (0-5)
	ADCSRA|=(1<<ADSC);				//start conversion
	while(!(ADCSRA & (1<<ADIF)));	//wait for conversion complete
	ADCSRA|=(1<<ADIF);				//clear flag for next conversion
	return(ADC);					//return sample value
}

uint16_t read_adc2(void)
{
	ADMUX = (ADMUX & 0xF8)|POT_PIN_ADC2;				//Selects ADC channel (0-5)
	ADCSRA|=(1<<ADSC);				//start conversion
	while(!(ADCSRA & (1<<ADIF)));	//wait for conversion complete
	ADCSRA|=(1<<ADIF);				//clear flag for next conversion
	return(ADC);					//return sample value
}

void init_adc_withINT(void)
{
	ADCSRA |=(1 << ADEN);	//enable adc
	ADCSRA |=(1 << ADPS2)|(1 << ADPS1)|(1 << ADPS0); // activate prescaler fo=16,000,000Hz/128~125KHz
	//ADMUX |=(0 << ADLAR);	//left justified (ADCH bit9-2, ADCL bit1-0)
	//ADMUX |=(1 << MUX1);	//Selects ADC channel (0-5)
	ADMUX |=(1 << REFS0);	//Selects Vref(pag 257)//AVcc= 5v & Aref= with capacitor to GND
	ADCSRA |= 1 << ADIE;	//enable ADC interrupts
	ADCSRA |= 1 << ADSC;	//start conversion
}
//void init_adc_withINT_1(void)
//{
	//ADCSRA |=(1 << ADEN);	//enable adc
	//ADCSRA |=(1 << ADPS2)|(1 << ADPS1)|(1 << ADPS0); // activate prescaler fo=16,000,000Hz/128~125KHz
	//ADMUX |=(1 << ADLAR);	//left justified (ADCH bit9-2, ADCL bit1-0)
	//ADMUX |=(1 << MUX1);	//Selects ADC channel (0-5)
	//ADMUX |=(1 << REFS0);	//Selects Vref(pag 257)//AVcc= 5v & Aref= with capacitor to GND
	//ADCSRA |= 1 << ADIE;	//enable ADC interrupts
	//ADCSRA |= 1 << ADSC;	//start conversion
//}
void int_str(uint16_t valor,char*str)
{
	sprintf(str,"%d",valor);
}
void oled_adc_valor(void){
	SSD1306_SetPosition (0,10);//col,row
	SSD1306_DrawString ("CAD 0", NORMAL);
char buffer[5];
uint16_t adc_valor=read_adc0();
itoa(adc_valor,buffer,10);
SSD1306_SetPosition(0,11);
SSD1306_DrawString(buffer,NORMAL);
SSD1306_ClearScreen();
_delay_us(300);
SSD1306_SetPosition(adc_valor,13);
SSD1306_DrawString("|",NORMAL);
}

void oled_adc_valor1(void){
	SSD1306_SetPosition (40,10);//col,row
	SSD1306_DrawString ("CAD 1", NORMAL);
	char buffer[5];
	uint16_t adc_valor1=read_adc1();
	itoa(adc_valor1,buffer,10);
	SSD1306_SetPosition(40,11);
	SSD1306_DrawString(buffer,NORMAL);
	SSD1306_ClearScreen();
	_delay_us(280);
	SSD1306_SetPosition(adc_valor1,14);
	SSD1306_DrawString("o",NORMAL);
}
void oled_adc_valor2(void){
		SSD1306_SetPosition (80,10);//col,row
		SSD1306_DrawString ("CAD 2", NORMAL);
	char buffer[5];
	uint16_t adc_valor2=read_adc2();
	itoa(adc_valor2,buffer,10);
	SSD1306_SetPosition(82,11);
	SSD1306_DrawString(buffer,NORMAL);
	SSD1306_ClearScreen();
	_delay_us(260);
	SSD1306_SetPosition(adc_valor2,15);
	SSD1306_DrawString("*",NORMAL);
}