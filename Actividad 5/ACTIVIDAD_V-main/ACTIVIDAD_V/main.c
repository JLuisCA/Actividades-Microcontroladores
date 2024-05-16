/*
 * ACTIVIDAD_V.c
 *
 * Created: 11/05/2024 09:12:22 p. m.
 * Author : tonoc
 */ 

#include "ssd1306.h"
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "usart.h"
#include "timers.h"
int main(void)
{

	init_ssd1306();
	SSD1306_ClearScreen ();
	int count = 0;
	for (count = 0; count <= 110; count++)
	{
		SSD1306_SetPosition(28,0);
		SSD1306_DrawString ("ACTIVIDAD V", NORMAL);
		SSD1306_SetPosition (count, 15);
		SSD1306_DrawString ("-", NORMAL);
		_delay_ms(20);
		SSD1306_ClearScreen();
	}
	init_usart(207);
	pwm_init();

	sei();
	while(1){
		SSD1306_SetPosition(0,11);
		SSD1306_DrawString("Esperando comando <3",NORMAL);
		}
	
	// return value
	return 0;
}
