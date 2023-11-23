#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "TWI.h"
#include "LCD_I2C.h"
int NewState,OldState,upState,dowState;
int n=1,m=2;
char Unit[][32] =
				 {
					"Unit 1",
					"Unit 2",
					"Unit 3",
					"Unit 4",
					"Unit 5",
					"Unit 6"					
				 };
ISR(TIMER1_COMPA_vect)
{
	NewState=PINA&0b00000011;
	if (NewState!=OldState)
	{
		switch(OldState)
		{
			case 2:
			{
				if(NewState == 3) upState++;
				if(NewState == 0)dowState++;
				break;
			}
			case 0:
			{
				if(NewState == 2) upState++;
				if(NewState == 1) dowState++;
				break;
			}
			case 1:
			{
				if(NewState == 0) upState++;
				if(NewState == 3) dowState++;
				break;
			}
			case 3:
			{
				if(NewState == 1) upState++;
				if(NewState == 2) dowState++;
				break;
			}
		}
		OldState=NewState;
	}
			if (upState >= 4)
			{
				lcd_clear();
				lcd_putstring(Unit[n++]);
					if (n==7)
					{
						n=6;
					}
				lcd_gotoxy(0,1);
				_delay_ms(100);
				lcd_putstring(Unit[n++]);
					if (n==7)
					{
						n=6;
					}
				upState = 0;
			}
			if (dowState >= 4)
			{
				lcd_clear();
				lcd_putstring(Unit[n--]);
					if (n==0)
					{
						n=1;
					} 
				lcd_gotoxy(0,1);
				_delay_ms(100);
				lcd_putstring(Unit[n--]);
					if (n==0)
					{
						n=1;
					} 
				dowState = 0;
			}
}

int main(void)
{
	I2C_Init();
	lcd_init();
	PORTA=0x03;
	DDRA=0x00;
	PORTB=0x00;
	DDRB=0xFF;
	TCCR1A=0x00;
	TCCR1B=0x0A;
	TCNT1H=0x00;
	TCNT1L=0x00;
	ICR1H=0x00;
	ICR1L=0x00;
	OCR1AH=0x03;
	OCR1AL=0xE8;
	OCR1BH=0x00;
	OCR1BL=0x00;
	TIMSK=0x10;	
	sei();
	lcd_putstring(Unit[0]);
	lcd_gotoxy(0,1);
	lcd_putstring(Unit[1]);
	while(1)
	{
	}
}