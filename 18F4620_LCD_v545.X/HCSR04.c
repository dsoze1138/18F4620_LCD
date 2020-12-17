/*
 * File:    HCSR04.c
 * Date:    2020-12-17
 * Author:  dan1138
 * Target:  PIC18F4620
 * Compiler: XC8 v2.31
 * IDE: MPLABX v5.45
 * 
 * Description:
 * 
 *                         PIC18F4620
 *                 +----------:_:----------+
 *       VPP ->  1 : RE3/MCLR/VPP  PGD/RB7 : 40 <> PGD
 *           <>  2 : RA0/AN0       PGC/RB6 : 39 <> PGC
 *           <>  3 : RA1           PGM/RB5 : 38 <>
 *           <>  4 : RA2               RB4 : 37 <>
 *           <>  5 : RA3               RB3 : 36 <> LED_D5
 *           <>  6 : RA4          INT2/RB2 : 35 <> LED_D4
 *           <>  7 : RA5          INT1/RB1 : 34 <> LED_D3
 *           <>  8 : RE0          INT0/RB0 : 33 <> LED_D2
 *           <>  9 : RE1               VDD : 32 <- PWR
 *           <> 10 : RE2               VSS : 31 <- GND
 *       PWR -> 11 : VDD               RD7 : 30 <> 
 *       GND -> 12 : VSS               RD6 : 29 -> LCD_E
 *           <> 13 : RA7/OSC1          RD5 : 28 -> LCD_RW
 *           <> 14 : RA6/OSC2          RD4 : 27 -> LCD_RS
 *           <> 15 : RC0/SOSCO   RX/DT/RC7 : 26 <> 
 *           <> 16 : RC1/SOSCI   TX/CK/RC6 : 25 <> 
 *      ECHO -> 17 : RC2/CCP1          RC5 : 24 -> TRIGGER
 *           <> 18 : RC3/SCL       SDA/RC4 : 23 <> 
 *    LCD_D4 <> 19 : RD0               RD3 : 22 <> LCD_D7
 *    LCD_D5 <> 20 : RD1               RD2 : 21 <> LCD_D6
 *                 +-----------------------:
 *                          DIP-40
 */

#include "mcc_generated_files/mcc.h"
#include <stdio.h>
#include "HCSR04.h"
#include "lcd.h"

/*
 * Demo global data
 */
typedef enum { eInit, eIdle, eRange } eHCSR04_State_t;
static volatile eHCSR04_State_t HCSR04_State;
static volatile uint16_t TimeOfFlight;
/*
 * We use TIMER0 to start the transducer ping every 60 milliseconds
 */
static void HCSR04_TMR0_Handler(void)
{
    if (HCSR04_State == eIdle)
    {
        PIE1bits.CCP1IE = 0;
        /* do one 10 us pulse */
        TRIGGER_SetHigh();
        __delay_us(10);
        TRIGGER_SetLow();
        CCP1CON = 0x05;
        PIR1bits.CCP1IF = 0;
        PIE1bits.CCP1IE = 1;
    }
}
/*
 *  We use CCP1 in capture mode to catch the High-to-Low edge of the 
 *  ECHO pulse from the transducer.
 */
void ECCP1_CallBack(uint16_t capturedValue)
{
    static uint16_t LeadingEdge;
    
    PIE1bits.CCP1IE = 0;
    if(CCP1CON == 0x05)
    {
        LeadingEdge = capturedValue;
        CCP1CON = 0x04;
        PIR1bits.CCP1IF = 0;
        PIE1bits.CCP1IE = 1;
    }
    else
    {
        if (HCSR04_State != eRange)
        {
            TimeOfFlight = capturedValue - LeadingEdge;
            HCSR04_State = eRange;
        }
    }
}
/*
 * hook for printf
 */
void putch(char Data)
{
    LCD_WriteData(Data);
}
/*
 * Initialize the application 
 */
void HCSR04_Init(void)
{
    TRISDbits.TRISD7 = 0;   /* Turn on the PICDEM2+ LCD module */
    LATDbits.LATD7 = 1;  
    LCD_Init();

    TMR0_SetInterruptHandler(HCSR04_TMR0_Handler);
    HCSR04_State = eInit;
}
/*
 * State machine to drive range finding demo
 */
void HCSR04_StartDemo(void)
{
    uint32_t Distance;
    
    switch(HCSR04_State)
    {
        case eInit: /* Initial state, occurs once */
            PIE1bits.CCP1IE = 0;
            LCD_SetPosition(LINE_ONE);
            printf("18F4620 Start v1");
            HCSR04_State++;
            break;

        case eIdle: /* Idle state, wait for interrupt to start range finding */
            break;

        case eRange: /* Process captured ECHO pulse */
            Distance = TimeOfFlight; /* units are 1us per count */
            Distance *= 343;         /* speed of sound in air, units micrometers per microsecond */
            Distance += 1;           /* round up */
            Distance /= 2;           //* convert time of flight to distance in micrometers */
            LCD_SetPosition(LINE_TWO);
            printf("%1.2f meters",(float)(Distance)/1E6);
            HCSR04_State = eIdle;
            break;

        default: /* when state is unknown return to idle state */
            HCSR04_State = eIdle;
            break;
    }
}