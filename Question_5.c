//Setting the CPU frequency as 8MHz. ** FUSE BITS NEED TO BE CHANGED ACCORDINGLY **
#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/delay.h>



void initSquareWave()
{

//Setting for Fast PWM Mode

//Toggle OC1A on Compare Match
TCCR1A |= ~(0b10000000);//Clearing COM1A1
TCCR1A &= 0b01000000;    //Setting COM1A0

//Fast PWM 8-bit mode
TCCR1A &= ~(0b00000010);//Clearing WGM11
TCCR1A |= 0b00000001;    //Setting WGM10

TCCR1B &= ~(0b00010000);//Clearing WGM13
TCCR1B |= 0b00001000;    //Setting WGM12


//Prescalar = Clock / 64. Hence Clock of Timer = 125KHz. Hence Time taken for each count in timer = 8uS
TCCR1B &= 0b00000011;//Setting CS11 and CS10
TCCR1B |= ~(0b00000100);//Clearing CS12


/*
Toggle mode  : Time duration of each pulse in square wave = 1mS

Hence number of counts needed = 1mS /  8uS = 125 units

So OCR1A should be set at 125 units in Toggle mode with a presacalar divider of 64, to get a square wave of 2KHz
*/

DDRD |= 0b00100000;   //Setting PD5 as an output pin

OCR1A = 125; //Setting the count value as 125 for 2KHz signal

}



int main(void)
{

    initSquareWave();
}
