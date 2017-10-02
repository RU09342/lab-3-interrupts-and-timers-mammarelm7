#ifndef CONFIG_H_
#define CONFIG_H_

#ifdef __MSP430F5529__
    #define REDLED     BIT0
	#define REDLEDP		P1DIR
    #define REDLEDO     P1OUT
	#define GREENLED   BIT7
	#define GREENLEDP	P4DIR
    #define GREENLEDO     P4OUT
   
#endif

#ifdef __MSP430FR2311__
    #define REDLED     BIT0
	#define REDLEDP		P1DIR
    #define REDLEDO     P1OUT
    #define GREENLED   BIT0
	#define GREENLEDP	P2DIR
    #define GREENLEDO     P2OUT
  
#endif

#ifdef __MSP430FR5994__
    #define REDLED     BIT0
	#define REDLEDP		P1DIR
    #define REDLEDO     P1OUT
    #define GREENLED   BIT1
	#define GREENLEDP	P1DIR
    #define GREENLEDO     P1OUT
   
#endif

#ifdef __MSP430FR6989__
    #define REDLED     BIT0
	#define REDLEDP		P1DIR
    #define REDLEDO     P1OUT
    #define GREENLED   BIT7
	#define GREENLEDP	P9DIR
    #define GREENLEDO     P9OUT
 
#endif

#ifdef __MSP430G2553__
    #define REDLED     BIT0
	#define REDLEDP		P1DIR
    #define REDLEDO     P1OUT
    #define GREENLED   BIT6
	#define GREENLEDP	P1DIR
    #define GREENLEDO     P1OUT
   
#endif





#endif //end of config
