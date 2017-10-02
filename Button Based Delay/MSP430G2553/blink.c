/*
Matt Mammarelli
9/18/17
ECE 09342-2
*/

//MSP430G2553 Button Based Delay
//used LMP0 instead of LMP4
//changes speed of blinking led based on how long you hold it
//short press = faster blinking, long press = slower blinking

#include <msp430.h>

double toTicks(double); //converts a frequency in Hz to ticks used in ccr register


void main(void)
{
    //WDTCTL is watchdog timer control
    //WDTPW watchdog timer + password, is an interrupt
    //WDTHOLD watchdog timer +hold, if 1 watchdog timer is stopped
    // Stop watchdog timer
    WDTCTL = WDTPW | WDTHOLD;

  
       //resistor enabled, input 1.3
       P1REN |= BIT3;

       //Sets Resistor to pullup, 1.0 is low, has to use = to initialize
       P1OUT = BIT3;

       //Enables port 1.0 as output, any bits that are 0 are treated as inputs
       P1DIR =BIT0;



       P1IE |=BIT3; //enable interrupt on port 1.3
       P1IES |=BIT3; //sets as falling edge
       P1IFG &=~(BIT3);//clear interrupt flag


       //TA0CTL = Timer A0 Control
        //TASSEL_1 Timer_A clock source select = 01 ACLK 32k
        //MC_1 Up Mode

        TA0CTL = TASSEL_1 + MC_1;

        //Timer A0 in compare mode
        TA0CCTL0 = 0x0010;

        //initial rate the led blinks, 10Hz
        TA0CCR0 = toTicks(10);

       //enter LPM0 mode and enable global interrupt
       _BIS_SR(LPM0_bits + GIE);

}

//timer A interrupt
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A(void) //double __
{

    P1OUT^=BIT0;


}

//button interrupt, ta0ccr0 will count from 0 to the final value when button is released
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void) {

    TA0CCR0 = 0; //initializes

    //checks for button input
    while(!((P1IN & BIT3) == BIT3)){
        TA0CCR0 = TA0CCR0 + 1; //increments the ccr
    }

    //clears interrupt flag to exit interrupt
    P1IFG &= ~BIT3;
}

//converts frequency to ticks
double toTicks(double frequency){
    //f=ACLK/ticks
    //f=32k/ticks
    //ticks=32k/f
    return 32000/frequency;
}
