# Lab 3: Timer A Blink
The speed of two leds were controlled with Timer A using interrupts. 

## Code Differences
For the MSP430FR2311 you have to use Timer B since Timer A is not recognized.
For the MSP430G2553 you have to use LPM0 instead of LPM4


## MSP430F5529 
Button: P1.1

```c
/*
Matt Mammarelli
9/18/17
ECE 09342-2
*/

//MSP430F5529 Timer A Blink


#include <msp430.h>

double toTicks(double); //converts frequency to ticks for ccr

void main(void)
{
    //WDTCTL is watchdog timer control
    //WDTPW watchdog timer + password, is an interrupt
    //WDTHOLD watchdog timer +hold, if 1 watchdog timer is stopped
    // Stop watchdog timer
	WDTCTL = WDTPW | WDTHOLD;

	
	


	//Enables port 1.0 as output, has to use = to initialize
	P1DIR = BIT0;

	P4DIR = BIT7;//Enables P4.7 output

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

    P1OUT^=BIT0;
    P4OUT^=BIT7;

}


//converts frequency to ticks
double toTicks(double frequency){
    //f=ACLK/ticks
    //f=32k/ticks
    //ticks=32k/f
    return 32000/frequency;
}



```

## MSP430FR2311 
Button: P1.1

```c
/*
Matt Mammarelli
9/18/17
ECE 09342-2
*/

//MSP430FR2311 Timer B Blink
//Doesn't see timer A so used Timer B


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


    //Enables port 1.0 as output
    P1DIR = BIT0;
    //Enables port 2.0 as output
    P2DIR = BIT0;


	//TB0CTL = Timer B0 Control
    //TBSSEL_1 Timer_B clock source select = 01 ACLK 32k
    //MC_1 Up Mode
    TB0CTL=TBSSEL_1+MC_1; //UP MODE


    TB0CCTL0 = 0x10; //Timer B0 in compare mode

    TB0CCR0=toTicks(10.5); //Timer B0 counts up to this, making it lower increases speed led blinks


    //enter LPM4 mode and enable global interrupt
    _BIS_SR(LPM4_bits + GIE);


}

//Port 1 ISR
#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer_B(void) //double __
{

       P1OUT^=0x01;

       P2OUT^=0x01;


}

//converts frequency to ticks
double toTicks(double frequency){
    //f=ACLK/ticks
    //f=32k/ticks
    //ticks=32k/f
    return 32000/frequency;
}



```

## MSP430FR5994 
Button: P5.6

```c
/*
Matt Mammarelli
9/18/17
ECE 09342-2
*/

//MSP430FR5994 Timer A Blink


#include <msp430.h>

double toTicks(double); //converts frequency to ticks for ccr

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
	
	


    //Enables port 1.0 as output
    P1DIR = BIT0|BIT1;





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
__interrupt void Timer_A(void) //double __
{

    P1OUT^=(BIT0|BIT1);


}

//converts frequency to ticks
double toTicks(double frequency){
    //f=ACLK/ticks
    //f=32k/ticks
    //ticks=32k/f
    return 32000/frequency;
}


```

## MSP430FR6989 
Button: P1.1

```c
/*
Matt Mammarelli
9/18/17
ECE 09342-2
*/

//MSP430FR6989 Timer A Blink


#include <msp430.h>

double toTicks(double); //converts frequency to ticks for ccr

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


    //Enables port 1.0 as output, has to use = to initialize
    P1DIR = BIT0;
    //Enables port 9.7 as output, has to use = to initialize
    P9DIR = BIT7;



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
__interrupt void Timer_A(void) //double __
{

    P1OUT^=BIT0;
    P9OUT^=BIT7;


}

//converts frequency to ticks
double toTicks(double frequency){
    //f=ACLK/ticks
    //f=32k/ticks
    //ticks=32k/f
    return 32000/frequency;
}


```

## MSP430G2553 
Button: P1.3 

```c
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


```

