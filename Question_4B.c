#define F_CPU 16000000UL


#include <avr/io.h>
#include <avr/delay.h>


void adcInit()
{
    ADMUX=0;
    ADCSRA=0;
    ADMUX=(1<<REFS0);                         /* For Aref=AVcc */
    ADCSRA=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1);
}


uint16_t readAdc(uint8_t ch)
{
    /* Select ADC Channel */ /* ch must be 0-7 */
    ADMUX&=0b11111000;
    ch=ch&0b00000111;
    ADMUX|=ch;

    /* Start Single conversion */
    ADCSRA|=(1<<ADSC);

    /* Wait for conversion to complete */
    while(!(ADCSRA & (1<<ADIF)));


    ADCSRA|=(1<<ADIF);

    return(ADC);
}














#define TRANSMIT_ONLY 1
#define RECEIVE_ONLY 2
#define TRANSMIT_RECEIVE 0




/* This function is used to read the available data from UART. This function will wait until data is available */
char uartReadChar()
{
    /* Wait until data is available */

    while(!(UCSR0A & (1<<RXC0)));

    /* Now UART has got data from the host device and is available in the buffer */

    return UDR0;
}


/* This fuction writes the given data to the UART channel which is then transmitted via the TX line */
void uartWriteChar(char data)
{


    /* Wait until the transmitter is ready */

    while(!(UCSR0A & (1<<UDRE0)));

    /* Now write the data to the UART buffer */

    UDR0=data;

}


/* This function is used to initialize the UART at a given baudrate */
void uartInit(uint16_t baud_rate, uint8_t mode)

        /*
           baud_rate = speed of communication

           mode = TRANSMIT_ONLY for transmission only
                = RECEIVE_ONLY for receiving only
                = TRANSMIT_RECEIVE for both transmission and receiving
        */
{
   /* Set baud rate */

   uint16_t ubrr_value=((F_CPU/(baud_rate*16UL))-1);

   UBRR0L = ubrr_value;
   UBRR0H = (ubrr_value>>8);

   /*

   Set Frame Format

   >> Asynchronous mode
   >> No Parity
   >> 1 StopBit
   >> No Flow control
   >> char size 8

   */

   UCSR0C=(1<<USBS0)|(3<<UCSZ00);





   /* Enable The receiver or/and transmitter according to "mode" */

    switch(mode)
    {
        case 1:
            UCSR0B=(1<<TXEN0);
            DDRD |= 0x02;
            break;
        case 2:
            UCSR0B=(1<<RXEN0);
            DDRD &= (~0x01);
            break;
        default:
            UCSR0B=(1<<RXEN0)|(1<<TXEN0);
            DDRD |= 0x02;
            DDRD &= (~0x01);
            break;
    }



}


















void init()

{

    uartInit(9600, TRANSMIT_ONLY);

    adcInit();

    _delay_ms(100);

}


void main()
{
    init();

    uint16_t adcValue;

    while(1)
    {
        adcValue = readAdc(0);    //Taking ADC Input


        uartWriteChar((adcValue&0x00FF));//Sending the LSB first

        uartWriteChar(((adcValue>>8)&0x00FF));//Sending the MSB next



        _delay_ms(100);

    }
}
