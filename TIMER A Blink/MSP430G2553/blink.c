/*
Matt Mammarelli
9/18/17
ECE 09342-2
*/

//MSP430G2553 Timer A Blink
//used LMP0 instead of LMP4

#include <msp430.h>

double toTicks(double); //converts a frequency in Hz to ticks used in ccr register


void main(void)
{
    //WDTCTL is watchdog timer control
    //WDTPW watchdog timer + password, is an interrupt
    //WDTHOLD watchdog timer +hold, if 1 watchdog timer is stopped
    // Stop watchdog timer
    WDTCTL = WDTPW | WDTHOLD;

  

	//Enables port 1.0 and 1.6 as output, any bits that are 0 are treated as inputs
	P1DIR =BIT0|BIT6;



	//TA0CTL = Timer A0 Control
	//TASSEL_1 Timer_A clock source select = 01 ACLK 32k
	//MC_1 Up Mode
	TA0CTL=TASSEL_1+MC_1; //UP MODE


	TA0CCTL0 = 0x10; //Timer A0 in compare mode

	TA0CCR0=toTicks(10); //Timer A0 counts up to this, making it lower increases speed led blinks



	//enter LPM0 mode and enable global interrupt
	_BIS_SR(LPM0_bits + GIE);

}

//Port 1 ISR
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A(void) //double __
{

    P1OUT^=(BIT0|BIT6);


}

//converts frequency to ticks
double toTicks(double frequency){
    //f=ACLK/ticks
    //f=32k/ticks
    //ticks=32k/f
    return 32000/frequency;
}
