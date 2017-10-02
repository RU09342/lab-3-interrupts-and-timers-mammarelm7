# Lab 3: Button Interrupt
changes speed of blinking led based on button press, uses interrupts
slow = 1 press, medium = 2 presses, fast = 3 presses, cycles back

## MSP430F5529 
Button: P1.1

```c
/*
Matt Mammarelli
9/18/17
ECE 09342-2
*/

//MSP430F5529 Button interrupt
//changes speed of blinking led based on button press
//slow = 1 press, medium = 2 presses, fast = 3 presses, cycles back

#include <msp430.h>

int count=0; //number of times button is pressed
int j; //how many times led blinks

void main(void)
{
    //WDTCTL is watchdog timer control
    //WDTPW watchdog timer + password, is an interrupt
    //WDTHOLD watchdog timer +hold, if 1 watchdog timer is stopped
    // Stop watchdog timer
	WDTCTL = WDTPW | WDTHOLD;

	
	
    //resistor enabled, p1.1
    P1REN |= BIT1;

    //Sets Resistor to pullup, 1.0 is low, has to use = to initialize
    P1OUT = BIT1;

	//Enables port 1.0 as output, has to use = to initialize
	P1DIR = BIT0;


	P1IE |=BIT1; //enable interrupt on port 1.1
	P1IES |=BIT1; //sets as falling edge
	P1IFG &=~(BIT1);//clear interrupt flag

	//enter LPM4 mode and enable global interrupt
	_BIS_SR(LPM4_bits + GIE);

}

//Port 1 ISR
#pragma vector = PORT1_VECTOR
__interrupt void PORT_1(void) //double __
{

 //checks to see if p1.3 is low
        if (!((P1IN & BIT1) == BIT1)){
            count = count +1;

            //checks to see how many times button is pressed
            switch(count){
            case 1:


            for (j =0; j<=10; j++){

            volatile unsigned int i;
            //toggles p1.0 red led
            P1OUT ^= BIT0;

            //red led delay slow
            i = 50000;
            //will decrement i unless i = 0
            do i--;
            while(i != 0);
            }



            break;
            case 2:


            for (j =0; j<=10; j++){

            volatile unsigned int i;
            //toggles p1.0 red led
            P1OUT ^= BIT0;

            //red led delay medium
            i = 30000;
            //will decrement i unless i = 0
            do i--;
            while(i != 0);
            }


            break;

            case 3:
            for (j =0; j<=10; j++){

            volatile unsigned int i;
            //toggles p1.0 red led
            P1OUT ^= BIT0;

            //red led delay fast
            i = 10000;
            //will decrement i unless i = 0
            do i--;
            while(i != 0);
            }

            break;

            default:count=0; //resets count

        }

    }



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

//MSP430FR2311 Button Interrupt
//changes speed of blinking led based on button press
//slow = 1 press, medium = 2 presses, fast = 3 presses, cycles back


#include <msp430.h>

int count=0; //number of times button is pressed
int j; //how many times led blinks

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

    //enter LPM4 mode and enable global interrupt
    _BIS_SR(LPM4_bits + GIE);


}

//Port 1 ISR
#pragma vector = PORT1_VECTOR
__interrupt void PORT_1(void) //double __
{

        //checks to see if p1.1 is low
        if (!((P1IN & BIT1) == BIT1)){
            count = count +1;

            //checks to see how many times button is pressed
            switch(count){
            case 1:


            for (j =0; j<=10; j++){

            volatile unsigned int i;
            //toggles p1.0 red led
            P1OUT ^= BIT0;

            //red led delay slow
            i = 50000;
            //will decrement i unless i = 0
            do i--;
            while(i != 0);
            }



            break;
            case 2:


            for (j =0; j<=10; j++){

            volatile unsigned int i;
            //toggles p1.0 red led
            P1OUT ^= BIT0;

            //red led delay medium
            i = 30000;
            //will decrement i unless i = 0
            do i--;
            while(i != 0);
            }


            break;

            case 3:
            for (j =0; j<=10; j++){

            volatile unsigned int i;
            //toggles p1.0 red led
            P1OUT ^= BIT0;

            //red led delay fast
            i = 10000;
            //will decrement i unless i = 0
            do i--;
            while(i != 0);
            }

            break;

            default:count=0; //resets count

        }

    }

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

//MSP430FR5994 Button Interrupt
//changes speed of blinking led based on button press
//slow = 1 press, medium = 2 presses, fast = 3 presses, cycles back

#include <msp430.h>

int count=0; //number of times button is pressed
int j; //how many times led blinks

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
	
	

    //resistor enabled input P5.6
    P5REN |= BIT6;

    //Sets Resistor to pullup, 1.0 is low, has to use = to initialize
    P1OUT = BIT6;

    //Enables port 1.0 as output
    P1DIR = BIT0;



    P5IE |=BIT6; //enable interrupt on port 5.6
    P5IES |=BIT6; //sets as falling edge
    P5IFG &=~(BIT6);//clear interrupt flag

    //enter LPM4 mode and enable global interrupt
    _BIS_SR(LPM4_bits + GIE);

}

//Port 1 ISR
#pragma vector = PORT5_VECTOR
__interrupt void PORT_5(void) //double __
{

 //checks to see if p5.6 is low
        if (!((P5IN & BIT6) == BIT6)){
            count = count +1;

            //checks to see how many times button is pressed
            switch(count){
            case 1:


            for (j =0; j<=10; j++){

            volatile unsigned int i;
            //toggles p1.0 red led
            P1OUT ^= BIT0;

            //red led delay slow
            i = 50000;
            //will decrement i unless i = 0
            do i--;
            while(i != 0);
            }



            break;
            case 2:


            for (j =0; j<=10; j++){

            volatile unsigned int i;
            //toggles p1.0 red led
            P1OUT ^= BIT0;

            //red led delay medium
            i = 30000;
            //will decrement i unless i = 0
            do i--;
            while(i != 0);
            }


            break;

            case 3:
            for (j =0; j<=10; j++){

            volatile unsigned int i;
            //toggles p1.0 red led
            P1OUT ^= BIT0;

            //red led delay fast
            i = 10000;
            //will decrement i unless i = 0
            do i--;
            while(i != 0);
            }

            break;

            default:count=0; //resets count

        }

    }



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

//MSP430FR6989 Button Interrupt
//changes speed of blinking led based on button press
//slow = 1 press, medium = 2 presses, fast = 3 presses, cycles back

#include <msp430.h>

int count=0; //number of times button is pressed
int j; //how many times led blinks

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

    //Enables port 1.0 as output, has to use = to initialize
    P1DIR = BIT0;



    P1IE |=BIT1; //enable interrupt on port 1.1
    P1IES |=BIT1; //sets as falling edge
    P1IFG &=~(BIT1);//clear interrupt flag

    //enter LPM4 mode and enable global interrupt
    _BIS_SR(LPM4_bits + GIE);


}

//Port 1 ISR
#pragma vector = PORT1_VECTOR
__interrupt void PORT_1(void) //double __
{

 //checks to see if p1.1 is low
        if (!((P1IN & BIT1) == BIT1)){
            count = count +1;

            //checks to see how many times button is pressed
            switch(count){
            case 1:


            for (j =0; j<=10; j++){

            volatile unsigned int i;
            //toggles p1.0 red led
            P1OUT ^= BIT0;

            //red led delay slow
            i = 50000;
            //will decrement i unless i = 0
            do i--;
            while(i != 0);
            }



            break;
            case 2:


            for (j =0; j<=10; j++){

            volatile unsigned int i;
            //toggles p1.0 red led
            P1OUT ^= BIT0;

            //red led delay medium
            i = 30000;
            //will decrement i unless i = 0
            do i--;
            while(i != 0);
            }


            break;

            case 3:
            for (j =0; j<=10; j++){

            volatile unsigned int i;
            //toggles p1.0 red led
            P1OUT ^= BIT0;

            //red led delay fast
            i = 10000;
            //will decrement i unless i = 0
            do i--;
            while(i != 0);
            }

            break;

            default:count=0; //resets count

        }

    }



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

//MSP430G2553 Button Interrupt
//changes speed of blinking led based on button press
//slow = 1 press, medium = 2 presses, fast = 3 presses, cycles back

#include <msp430g2553.h>

int count=0; //number of times button is pressed
int j; //how many times led blinks

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

    //enter LPM4 mode and enable global interrupt
    _BIS_SR(LPM4_bits + GIE);

}
//Port 1 ISR
#pragma vector = PORT1_VECTOR
__interrupt void PORT_1(void) //double __
{

 //checks to see if p1.3 is low
        if (!((P1IN & BIT3) == BIT3)){
            count = count +1;

            //checks to see how many times button is pressed
            switch(count){
            case 1:


            for (j =0; j<=10; j++){

            volatile unsigned int i;
            //toggles p1.0 red led
            P1OUT ^= BIT0;

            //red led delay slow
            i = 50000;
            //will decrement i unless i = 0
            do i--;
            while(i != 0);
            }



            break;
            case 2:


            for (j =0; j<=10; j++){

            volatile unsigned int i;
            //toggles p1.0 red led
            P1OUT ^= BIT0;

            //red led delay medium
            i = 30000;
            //will decrement i unless i = 0
            do i--;
            while(i != 0);
            }


            break;

            case 3:
            for (j =0; j<=10; j++){

            volatile unsigned int i;
            //toggles p1.0 red led
            P1OUT ^= BIT0;

            //red led delay fast
            i = 10000;
            //will decrement i unless i = 0
            do i--;
            while(i != 0);
            }

            break;

            default:count=0; //resets count

        }

    }



}


```

