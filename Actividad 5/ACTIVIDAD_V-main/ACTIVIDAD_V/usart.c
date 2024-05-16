/*
 * usart.c
 *
 *  Author: jlb
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "usart.h"
#include "ports.h"
#include "ssd1306.h"
#include "timers.h"

//global variables
volatile char usart_received_char;
void process_command(char command);
ISR (USART_RX_vect){
 usart_received_char=UDR0;
 process_command(usart_received_char);
	_delay_ms(2000);
 }

unsigned char usart_receive( void )
{
  while (!(UCSR0A & (1 << RXC0))); // wait for data (RXC=1)
  return UDR0;
}

void usart_transmit( unsigned char data )
{
  while (!(UCSR0A & (1 << UDRE0)));  // wait for transmitter buffer empty(UDRE=1)
  UDR0 = data; // when buffer empty, write data to UDR
}

void usart_transmit_string( char s[] )
{	
	int i = 0;
  while (i < 64)
  {
	  if (s[i] == '\0') break;
	  usart_transmit(s[i++]);
  }
}

void init_usart(unsigned int baudrate)
{
	UCSR0C &= (~(1<<UMSEL00) & ~(1<<UMSEL01)); // bit UMSEL = 0 asyncronous mode	
	UCSR0A = (1<<U2X0); // bit U2X = 1 double speed
	//Baudrate:fosc=16Mhz,U2Xn=1,BaudRate=9600, then UBRR= 207 (DS pag.199)
	UBRR0H = (unsigned char) (baudrate>>8); // write(MSB)
	UBRR0L = (unsigned char) (baudrate);	//write(LSB)
	UCSR0C = ((1<<UCSZ00) | (1<<UCSZ01)); //8 bits data lenght
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);	//enable transmitter & receiver
	//UCSRC = (1<<USBS);	//2 stop bits
	UCSR0B |= (1<<RXCIE0);	//enable reception complete (RXCIE0=1) interrupts
}

void process_command(char command) {
	switch (command) {
		 case 'r': // Comando para encender el LED rojo
		 set_red_intensity(0);
		 set_green_intensity(255);
		 set_blue_intensity(255);
		 usart_transmit_string("Rojo encendido\n");
		 SSD1306_SetPosition(0,10);
		 SSD1306_ClearScreen();
		 SSD1306_DrawString("COLOR ROJO",NORMAL);
		 break;
		 case 'v': // Comando para encender el LED verde
		 set_red_intensity(255);
		 set_green_intensity(0);
		 set_blue_intensity(255);
		 usart_transmit_string("Verde encendido\n");
		  SSD1306_SetPosition(0,10);
		  SSD1306_ClearScreen();
		  SSD1306_DrawString("COLOR VERDE",NORMAL);
		 break;
		 case 'a': // Comando para encender el LED azul
		 set_red_intensity(255);
		 set_green_intensity(255);
		 set_blue_intensity(0);
		 usart_transmit_string("Azul encendido\n");
		  SSD1306_SetPosition(0,10);
		  SSD1306_ClearScreen();
		  SSD1306_DrawString("COLOR AZUL",NORMAL);
		 break;
		  case 'A': // Comando para encender el LED amarrillo
		 set_red_intensity(0);
		 set_green_intensity(0);
		 set_blue_intensity(255);
		 usart_transmit_string("Amarrillo encendido\n");
		 SSD1306_SetPosition(0,10);
		 SSD1306_ClearScreen();
		 SSD1306_DrawString("COLOR AMARILLO",NORMAL);
		 break;
		 case 'c': // Comando para encender el LED cyan
		 set_red_intensity(255);
		 set_green_intensity(0);
		 set_blue_intensity(0);
		 usart_transmit_string("Cyan encendido\n");
		 SSD1306_SetPosition(0,10);
		 SSD1306_ClearScreen();
		 SSD1306_DrawString("COLOR CYAN",NORMAL);
		 break;
		 case 'm': // Comando para encender el LED magenta
		 set_red_intensity(0);
		 set_green_intensity(255);
		 set_blue_intensity(0);
		 usart_transmit_string("Magenta encendido\n");
		 SSD1306_SetPosition(0,10);
		 SSD1306_ClearScreen();
		 SSD1306_DrawString("COLOR MAGENTA",NORMAL);
		 break;
		 case 'n': // Comando para encender el LED naranja
		 set_red_intensity(0);
		 set_green_intensity(180);
		 set_blue_intensity(255);
		 usart_transmit_string("Naranja encendido\n");
		 SSD1306_SetPosition(0,10);
		 SSD1306_ClearScreen();
		 SSD1306_DrawString("COLOR NARANJA",NORMAL);
		 break;
		 case 'R': // Comando para encender el LED rosa
		 set_red_intensity(0);
		 set_green_intensity(235);
		 set_blue_intensity(108);
		 usart_transmit_string("Rosa encendido\n");
		 SSD1306_SetPosition(0,10);
		 SSD1306_ClearScreen();
		 SSD1306_DrawString("COLOR ROSA",NORMAL);
		 break;
		 case 'p': // Comando para encender el LED purpura
		 set_red_intensity(117);
		 set_green_intensity(212);
		 set_blue_intensity(29);
		 usart_transmit_string("Purpura encendido\n");
		 SSD1306_SetPosition(0,10);
		 SSD1306_ClearScreen();
		 SSD1306_DrawString("COLOR PURPURA",NORMAL);
		 break;
		  case 'V': // Comando para encender el LED 
		  set_red_intensity(103);
		  set_green_intensity(4);
		  set_blue_intensity(103);
		  usart_transmit_string("Lima encendido\n");
		  SSD1306_SetPosition(0,10);
		  SSD1306_ClearScreen();
		  SSD1306_DrawString("COLOR LIMA",NORMAL);
		  break;
		 case 'o': // Comando para apagar el LED
		 	set_red_intensity(255);
		 	set_green_intensity(255);
		 	set_blue_intensity(255);
		 SSD1306_SetPosition(0,10);
		 SSD1306_ClearScreen();
		 SSD1306_DrawString("SIN COLOR",NORMAL);
		 break;
		default:
		break;
	}
}