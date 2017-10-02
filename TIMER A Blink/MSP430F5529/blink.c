/*
Matt Mammarelli
9/18/17
ECE 09342-2
*/

//MSP430F5529 Timer A Blink


#include <msp430.h>
#include "config.h"

double toTicks(double); //converts frequency to ticks for ccr

void main(void)
{
    //WDTCTL is watchdog timer control
    //WDTPW watchdog timer + password, is an interrupt
    //WDTHOLD watchdog timer +hold, if 1 watchdog timer is stopped
    // Stop watchdog timer
	WDTCTL = WDTPW | WDTHOLD;

	
	


	//Enables port 1.0 as output, has to use = to initialize
	REDLEDP = REDLED;

	GREENLEDP = GREENLED;//Enables P4.7 output

	//TA0CTL = Timer A0 Control
	//TASSEL_1 Timer_A clock source select = 01 ACLK 32k
	//MC_1 Up Mode
	TA0CTL=TASSEL_1+MC_1; //UP MODE


	TA0CCTL0 = 0x10; //Timer A0 in compare mode

	TA0CCR0=toTicks(10); //Timer A0 counts up to this, making it lower increases speed led blinks



	//enter LPM4 mode and enable global interrupt
	_BIS_SR(LPM4_bits + GIE);

}

//Port 1 ISR
#pragma vector = TIMER0_A0_VECTOR
__interrupt void TimerA(void) //double __
{

    REDLEDP^=REDLED;
    GREENLEDP^=GREENLED;

}


//converts frequency to ticks
double toTicks(double frequency){
    //f=ACLK/ticks
    //f=32k/ticks
    //ticks=32k/f
    return 32000/frequency;
}


