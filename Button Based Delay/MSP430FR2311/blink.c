/*
Matt Mammarelli
9/18/17
ECE 09342-2
*/

//MSP430FR2311 Timer B Blink
//Doesn't see timer A so used Timer B
//changes speed of blinking led based on how long you hold it
//short press = faster blinking, long press = slower blinking
//doesn't work as reliably as others


#include <msp430.h>


double toTicks(double); //converts a frequency in Hz to ticks used in ccr register

void main(void) {

    //WDTCTL is watchdog timer control
    //WDTPW watchdog timer + password, is an interrupt
    //WDTHOLD watchdog timer +hold, if 1 watchdog timer is stopped
    // Stop watchdog timer
    WDTCTL = WDTPW | WDTHOLD;

    // Disable the GPIO power-on default high-impedance mode
    // to activate previously configured port settings
    //PM5CTL0 = Power mode 5 control register 0
    //LOCKLPM5 = Locks I/O pin, bit is reset by a power cycle
    //~LOCKLPM5=8'b0 and by anding PM5CTL0 it clears the register
    PM5CTL0 &= ~LOCKLPM5;


        //resistor enabled
        P1REN |= BIT1;

        //Sets Resistor to pullup, 1.0 is low, has to use = to initialize
        P1OUT = BIT1;

        //Enables port 1.0 as output
        P1DIR = BIT0;

        P1IE |=BIT1; //enable interrupt on port 1.1
        P1IES |=BIT1; //sets as falling edge
        P1IFG &=~(BIT1);//clear interrupt flag



        //TA0CTL = Timer A0 Control
        //TASSEL_1 Timer_A clock source select = 01 ACLK 32k
        //MC_1 Up Mode

        TB0CTL = TBSSEL_1 + MC_1;

        //Timer A0 in compare mode
        TB0CCTL0 = 0x0010;

        //initial rate the led blinks, 10Hz
        TB0CCR0 = toTicks(10);

        //enter LPM4 mode and enable global interrupt
        _BIS_SR(LPM4_bits + GIE);


}

//timer b interrupt
#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer_B(void) //double __
{


        P1OUT^=0x01;


}


//button interrupt, ta0ccr0 will count from 0 to the final value when button is released
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void) {

    TB0CCR0 = 0; //initializes

    //checks for button input
    while(!((P1IN & BIT1) == BIT1)){
        TB0CCR0 = TB0CCR0 + 1; //increments the ccr
    }

    //clears interrupt flag to exit interrupt
    P1IFG &= ~BIT1;
}


//converts frequency to ticks
double toTicks(double frequency){
    //f=ACLK/ticks
    //f=32k/ticks
    //ticks=32k/f
    return 32000/frequency;
}


