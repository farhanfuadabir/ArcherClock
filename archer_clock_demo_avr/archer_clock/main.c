/*
 * archer_clock.c
 *
 * Created: 8/13/2017 9:31:57 AM
 * Author : FUAD
 */ 
#define F_CPU				16000000UL
#define NumberofButtons		3

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "serial_lib.h"
#include "lcd_lib.h"
#include "Button_Debounce.h"

uint16_t timerLimit = 60;
uint8_t warningTime = 15;
uint8_t preparationTime	= 10;
uint8_t pressedFlag = 0;

int16_t timer = 0;
uint8_t preparationFlag = 1;

void xINT_init()
{
	MCUCR |= (1 << ISC11) | (1 << ISC10);
	GICR |= (1 << INT1);
}

void timerInit(void)
{
	TCCR1B |= (1 << WGM12);
	TIMSK |= (1 << OCIE1A);						// Enables Compare Match Interrupt
	TCCR1B |= (1 << CS12);
	OCR1A = 0xF423;								// Setting Compare Match value
}

void timerReset(void)
{
	TCCR1B &= ~(1 << CS12);
	TCNT1 = 0x00;
	TCCR1B |= (1 << CS12);
}

void timerStart(void)
{
	TCCR1B |= (1 << CS12);
	TCNT1 = 0x00;
}
void timerOFF(void)
{
	TCCR1B &= ~(1 << CS12);
	TCNT1 = 0x00;
}

void printTimer(void)
{
	Serial_sendString("\f");
	_delay_ms(100);	
	int minute = timer / 60;
	Serial_sendInt(minute, DEC);
	Serial_sendString(" : ");
	Serial_sendInt(timer - (minute * 60), DEC);
//	Serial_sendString("\n");
}

void printTimerLCD(void)
{
// 	LCDclr();
// 	_delay_ms(10);
	if (preparationFlag == 1)
	{
		LCDWriteStringXY(0, 0, "PREPARATION TIME");
	}
	else LCDWriteStringXY(3, 0, "MAIN TIME");
	_delay_ms(10);
	int minute = timer / 60;
	LCDWriteIntXY(4, 1, minute, 2);
	LCDWriteStringXY(7, 1, ":");
	LCDWriteIntXY(9, 1, timer - (minute * 60), 2);
}

void printLCDinitial(void)
{
	LCDWriteStringXY(2, 0, "ARCHER CLOCK");
}

void lightEffect(void)
{
	if(/*timer <= timerLimit &&*/ timer > warningTime)
	{
		PORTC &= ~(1 << PC5);
		PORTC &= ~(1 << PC4);
		PORTC |= (1 << PC3);
	}
	else if(timer <= warningTime && timer > 0)
	{
		PORTC &= ~(1 << PC5);
		PORTC |= (1 << PC4);
		PORTC &= ~(1 << PC3);
	}
	else if (timer < 1)
	{
		PORTC |= (1 << PC5);
		PORTC &= ~(1 << PC4);
		PORTC &= ~(1 << PC3);
	}
}

void preparationTimeLight(void)
{
	if (timer % 2 == 1)
	{
		PORTC &= ~(1 << PC4);
	}
	else PORTC |= (1 << PC4);	
}

void settings(void)
{
	if (pressedFlag == 1)
	{
		LCDclr();
		_delay_ms(10);
		LCDWriteStringXY(1, 0, "SETTINGS MODE");
		_delay_ms(1500);
		
		LCDclr();
		_delay_ms(10);
		LCDWriteStringXY(0, 0, "PREPARATION TIME");
		LCDWriteIntXY(4, 1, preparationTime / 60, 2);
		LCDWriteStringXY(7, 1, ":");
		LCDWriteIntXY(9, 1, preparationTime - (preparationTime / 60 * 60), 2);
		_delay_ms(10);
		
		while (pressedFlag == 1)
		{
			if (ButtonCheck(1, PINB, PB1, 400))
			{
				if (preparationTime < 600) preparationTime++;
				LCDWriteIntXY(4, 1, preparationTime / 60, 2);
				LCDWriteStringXY(7, 1, ":");
				LCDWriteIntXY(9, 1, preparationTime - (preparationTime / 60 * 60), 2);
//				_delay_ms(10);
			}
			if (ButtonCheck(0, PINB, PB0, 400))
			{
				if (preparationTime > 0) preparationTime--;
				LCDWriteIntXY(4, 1, preparationTime / 60, 2);
				LCDWriteStringXY(7, 1, ":");
				LCDWriteIntXY(9, 1, preparationTime - (preparationTime / 60 * 60), 2);
//				_delay_ms(10);
			}
			if (ButtonCheck(2, PIND, PD3, 400))
			{
				pressedFlag++;
			}
		}
	}
	
	if (pressedFlag == 2)
	{
		LCDclr();
		_delay_ms(10);
		LCDWriteStringXY(3, 0, "TIME LIMIT");
		LCDWriteIntXY(4, 1, timerLimit / 60, 2);
		LCDWriteStringXY(7, 1, ":");
		LCDWriteIntXY(9, 1, timerLimit - (timerLimit / 60 * 60), 2);
		_delay_ms(10);
			
		while (pressedFlag == 2)
		{
			if (ButtonCheck(1, PINB, PB1, 400))
			{
				if (timerLimit < 600) timerLimit++;
				LCDWriteIntXY(4, 1, timerLimit / 60, 2);
				LCDWriteStringXY(7, 1, ":");
				LCDWriteIntXY(9, 1, timerLimit - (timerLimit / 60 * 60), 2);
				_delay_ms(10);
			}
			if (ButtonCheck(0, PINB, PB0, 400))
			{
				if (timerLimit > 0) timerLimit--;
				LCDWriteIntXY(4, 1, timerLimit / 60, 2);
				LCDWriteStringXY(7, 1, ":");
				LCDWriteIntXY(9, 1, timerLimit - (timerLimit / 60 * 60), 2);
				_delay_ms(10);
			}
			if (ButtonCheck(2, PIND, PD3, 400))
			{
				pressedFlag++;
			}

		}
	}
	
	if (pressedFlag == 3)
	{
		LCDclr();
		_delay_ms(10);
		LCDWriteStringXY(2, 0, "WARNING TIME");
		LCDWriteIntXY(4, 1, warningTime / 60, 2);
		LCDWriteStringXY(7, 1, ":");
		LCDWriteIntXY(9, 1, warningTime - (warningTime / 60 * 60), 2);
		_delay_ms(10);
		
		while (pressedFlag == 3)
		{
			if (ButtonCheck(1, PINB, PB1, 400))
			{
				if (warningTime < 600) warningTime++;
				LCDWriteIntXY(4, 1, warningTime / 60, 2);
				LCDWriteStringXY(7, 1, ":");
				LCDWriteIntXY(9, 1, warningTime - (warningTime / 60 * 60), 2);
				_delay_ms(10);
			}
			if (ButtonCheck(0, PINB, PB0, 400))
			{
				if (warningTime > 0) warningTime--;
				LCDWriteIntXY(4, 1, warningTime / 60, 2);
				LCDWriteStringXY(7, 1, ":");
				LCDWriteIntXY(9, 1, warningTime - (warningTime / 60 * 60), 2);
				_delay_ms(10);
			}
			if (ButtonCheck(2, PIND, PD3, 400))
			{
				pressedFlag++;
			}
		}
	}
	
	LCDclr();
	_delay_ms(10);
	LCDWriteStringXY(3, 0, "TIMER RESET");
	_delay_ms(1500);
}

int main(void)
{
	timer = preparationTime;
	LCDinit();
	LCDclr();
	printLCDinitial();
	_delay_ms(1000);

	
	UART_init();
//	xINT_init();
	timerInit();
	sei();
	
	uint8_t prev_TCNT = 0;
	uint8_t pauseFlag = 0;

    DDRC = 0xFF;
	DDRB &= ~((1 << PB0) | (1 << PB1));
	DDRD &= ~(1 << PD3);

	
	PORTC = 0x00;
	
    while (1) 
    {
		if (ButtonCheck(2, PIND, PD3, 400))
		{
			pressedFlag++;
			timerOFF();
			settings();
			if (pressedFlag > 3)
			{
				pressedFlag = 0;
				timer = preparationTime;
				timerStart();
				_delay_ms(500);
			}
		}
		
// 		if(Serial_receive() == 'A')
// 		{
// 			if (pauseFlag == 0)
// 			{
// 				pauseFlag = 1;
// 				prev_TCNT = TCNT1;
// 				timerOFF();
// 			}
// 			else if (pauseFlag == 1)
// 			{
// 				pauseFlag = 0;
// 				timerStart();
// 				TCNT1 = prev_TCNT;
// 			}
// 		}
// 
// 		else if(Serial_receive() == 'B')
// 		{
// 			timerOFF();
// 			_delay_ms(100);
// 			timer = timerLimit;
// 			timerStart();
// 			_delay_ms(500);
// 			
// 			preparationTime();
// 		}
// 		
    }
}

ISR(TIMER1_COMPA_vect)
{
	printTimerLCD();
	
	if (preparationFlag == 1)
	{
		preparationTimeLight();
	}
	else lightEffect();
	
	timer--;
	
	if (timer < 0 && preparationFlag == 1)
	{
		preparationFlag = 0;
		timerOFF();
		LCDclr();
		_delay_ms(100);
		timer = timerLimit;
		timerStart();
	}
	else if (timer < 0 && preparationFlag == 0)
	{ 
		timer = timerLimit;
		timerOFF();
	}
}

