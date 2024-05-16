/*
*/
#include "ssd1306.h"
#include "adc.h"
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "usart.h"
int main(void)
{

  init_ssd1306();
  SSD1306_ClearScreen ();
  int count = 0;
  for (count = 0; count <= 110; count++)
  {
	  SSD1306_SetPosition(28,0);
	  SSD1306_DrawString ("ACTIVIDAD IV", NORMAL);
	  SSD1306_SetPosition (count, 15);
	  SSD1306_DrawString ("-", NORMAL);
	  _delay_ms(20);
	  SSD1306_ClearScreen();
  }  
  init_adc_withINT();
  init_usart(207);
DDRB|= (1 << DDB5) | (1 << DDB4) | (1 << DDB3);
PORTB|= (1<< PORTB5)| (1<<PORTB4) | (1 << PORTB3);

  while(1){
		  
		   sei();
		   oled_adc_valor();
  }
 
			// return value
			return 0;
   

 
  }
