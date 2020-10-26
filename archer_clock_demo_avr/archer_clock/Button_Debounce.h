#define Button_Debounce
#include <avr/io.h>

char ButtonCheck(int Button_Number, unsigned char PORTofButton, unsigned char PORT_Bit,int threshold);

//main program below:

char Pressed[NumberofButtons];
int Pressed_Confidence_Level[NumberofButtons];			    //Measure button press confidence
int Released_Confidence_Level[NumberofButtons];				//Measure button release confidence

/*
~"Button_Number" denotes which number of button to examine i.e. 1st or 2nd or 3rd. 
 "Button_Number" starts from 0 as the "NumberofButtons" is an array. It will be Written as "X" X = 0, 1, 2, ....
~"PORTofButton" denotes which PORT the button is on i.e. PORTA or PORTB or PORTC. It will be Written as "PORTX" X = A, B, C, D.
~"PORT_Bit" denotes the pin number of the certain PORT i.e. A0, B2. It will be Written as "X" X = 0, 1, 2, ....
~"threshold" denotes the number of continuous 1s or 0s to be considered for correcting button bounce. 
 It will be Written as "X" X = 200, 300, 500, .... 400 or 500 is fine. 
*/

char ButtonCheck(int Button_Number, unsigned char PORTofButton, unsigned char PORT_Bit, int threshold)
{
	if (bit_is_set(PORTofButton, PORT_Bit))
	{
		Pressed_Confidence_Level[Button_Number] ++;					//Increase Pressed-Confidence
		Released_Confidence_Level[Button_Number] = 0;				//Reset Released-Confidence since there is a button pressed
		if (Pressed_Confidence_Level[Button_Number] >threshold)		//Indicator of good button press
		{
			if (Pressed[Button_Number] == 0)
				{
				Pressed[Button_Number] = 1;
				return 1;
				}
				//Zero it so a new pressed condition can be evaluated
			Pressed_Confidence_Level[Button_Number] = 0;
		}
	}
	else
	{
		Released_Confidence_Level[Button_Number] ++; //Increase Released-Confidence
		Pressed_Confidence_Level[Button_Number] = 0; //Reset Pressed-Confidence since the button is released
		if (Released_Confidence_Level[Button_Number] >threshold)
			{
			Pressed[Button_Number] = 0;
			Released_Confidence_Level[Button_Number] = 0;
			}
	}
	return 0;
}