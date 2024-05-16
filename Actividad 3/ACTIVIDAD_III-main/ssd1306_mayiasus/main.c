/*
*/
#include "ssd1306.h"
#include "adc.h"
#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>	//conversion to ASCII
#include <avr/interrupt.h>
#define POT_PIN_ADC0 0
#define POT_PIN_ADC1 1
#define POT_PIN_ADC2 2
int main(void)
{

  init_ssd1306();
  SSD1306_ClearScreen ();
  int count = 0;
  for (count = 0; count <= 105; count++)
  {
	  SSD1306_SetPosition(33,0);
	  SSD1306_DrawString ("ACTIVIDAD III", NORMAL);
	  SSD1306_SetPosition (count, 15);
	  SSD1306_DrawString ("-", NORMAL);
	  _delay_ms(20);
	  SSD1306_ClearScreen();
  }  
  
  init_adc_withINT();

  while(1){
		  oled_adc_valor();
		  oled_adc_valor1();
		  oled_adc_valor2();
  }
  // return value
  return 0;
}
