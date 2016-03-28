// Question 4a.
#define F_CPU 16000000UL // setting the inbuilt clock at 16MHz
#include <avr/io.h>
#include <avr/delay.h>
void init()
{
	DDRC &= ~(1<<0);// Pin C0 takes input of switch
	DDRB |= (1<<0); // Pin B0 indicates LED status
	PORTC |= (1<<0); // pull-up resistor activated for Pin C0. it has been done just to be on the safe side, to counter the situation when the switch can be in a floating state.
	_delay_ms(100);
}
int main(void)
{
	init();
	while(1) // infinite loop
	{
		if(((PINC & (1<<0))!=0)) // i.e, if switch is ON, LED will glow

			PORTB |= (1<<0);
		else
			PORTB &=~(1<<0);
	}
}
