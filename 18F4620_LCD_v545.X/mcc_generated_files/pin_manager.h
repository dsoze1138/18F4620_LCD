/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.6
        Device            :  PIC18F4620
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.30 and above
        MPLAB 	          :  MPLAB X 5.40	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set RC2 procedures
#define RC2_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define RC2_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define RC2_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define RC2_GetValue()              PORTCbits.RC2
#define RC2_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define RC2_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)

// get/set TRIGGER aliases
#define TRIGGER_TRIS                 TRISCbits.TRISC5
#define TRIGGER_LAT                  LATCbits.LATC5
#define TRIGGER_PORT                 PORTCbits.RC5
#define TRIGGER_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define TRIGGER_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define TRIGGER_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define TRIGGER_GetValue()           PORTCbits.RC5
#define TRIGGER_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define TRIGGER_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)

// get/set LCD_D4 aliases
#define LCD_D4_TRIS                 TRISDbits.TRISD0
#define LCD_D4_LAT                  LATDbits.LATD0
#define LCD_D4_PORT                 PORTDbits.RD0
#define LCD_D4_SetHigh()            do { LATDbits.LATD0 = 1; } while(0)
#define LCD_D4_SetLow()             do { LATDbits.LATD0 = 0; } while(0)
#define LCD_D4_Toggle()             do { LATDbits.LATD0 = ~LATDbits.LATD0; } while(0)
#define LCD_D4_GetValue()           PORTDbits.RD0
#define LCD_D4_SetDigitalInput()    do { TRISDbits.TRISD0 = 1; } while(0)
#define LCD_D4_SetDigitalOutput()   do { TRISDbits.TRISD0 = 0; } while(0)

// get/set LCD_D5 aliases
#define LCD_D5_TRIS                 TRISDbits.TRISD1
#define LCD_D5_LAT                  LATDbits.LATD1
#define LCD_D5_PORT                 PORTDbits.RD1
#define LCD_D5_SetHigh()            do { LATDbits.LATD1 = 1; } while(0)
#define LCD_D5_SetLow()             do { LATDbits.LATD1 = 0; } while(0)
#define LCD_D5_Toggle()             do { LATDbits.LATD1 = ~LATDbits.LATD1; } while(0)
#define LCD_D5_GetValue()           PORTDbits.RD1
#define LCD_D5_SetDigitalInput()    do { TRISDbits.TRISD1 = 1; } while(0)
#define LCD_D5_SetDigitalOutput()   do { TRISDbits.TRISD1 = 0; } while(0)

// get/set LCD_D6 aliases
#define LCD_D6_TRIS                 TRISDbits.TRISD2
#define LCD_D6_LAT                  LATDbits.LATD2
#define LCD_D6_PORT                 PORTDbits.RD2
#define LCD_D6_SetHigh()            do { LATDbits.LATD2 = 1; } while(0)
#define LCD_D6_SetLow()             do { LATDbits.LATD2 = 0; } while(0)
#define LCD_D6_Toggle()             do { LATDbits.LATD2 = ~LATDbits.LATD2; } while(0)
#define LCD_D6_GetValue()           PORTDbits.RD2
#define LCD_D6_SetDigitalInput()    do { TRISDbits.TRISD2 = 1; } while(0)
#define LCD_D6_SetDigitalOutput()   do { TRISDbits.TRISD2 = 0; } while(0)

// get/set LCD_D7 aliases
#define LCD_D7_TRIS                 TRISDbits.TRISD3
#define LCD_D7_LAT                  LATDbits.LATD3
#define LCD_D7_PORT                 PORTDbits.RD3
#define LCD_D7_SetHigh()            do { LATDbits.LATD3 = 1; } while(0)
#define LCD_D7_SetLow()             do { LATDbits.LATD3 = 0; } while(0)
#define LCD_D7_Toggle()             do { LATDbits.LATD3 = ~LATDbits.LATD3; } while(0)
#define LCD_D7_GetValue()           PORTDbits.RD3
#define LCD_D7_SetDigitalInput()    do { TRISDbits.TRISD3 = 1; } while(0)
#define LCD_D7_SetDigitalOutput()   do { TRISDbits.TRISD3 = 0; } while(0)

// get/set LCD_RS aliases
#define LCD_RS_TRIS                 TRISDbits.TRISD4
#define LCD_RS_LAT                  LATDbits.LATD4
#define LCD_RS_PORT                 PORTDbits.RD4
#define LCD_RS_SetHigh()            do { LATDbits.LATD4 = 1; } while(0)
#define LCD_RS_SetLow()             do { LATDbits.LATD4 = 0; } while(0)
#define LCD_RS_Toggle()             do { LATDbits.LATD4 = ~LATDbits.LATD4; } while(0)
#define LCD_RS_GetValue()           PORTDbits.RD4
#define LCD_RS_SetDigitalInput()    do { TRISDbits.TRISD4 = 1; } while(0)
#define LCD_RS_SetDigitalOutput()   do { TRISDbits.TRISD4 = 0; } while(0)

// get/set LCD_RW aliases
#define LCD_RW_TRIS                 TRISDbits.TRISD5
#define LCD_RW_LAT                  LATDbits.LATD5
#define LCD_RW_PORT                 PORTDbits.RD5
#define LCD_RW_SetHigh()            do { LATDbits.LATD5 = 1; } while(0)
#define LCD_RW_SetLow()             do { LATDbits.LATD5 = 0; } while(0)
#define LCD_RW_Toggle()             do { LATDbits.LATD5 = ~LATDbits.LATD5; } while(0)
#define LCD_RW_GetValue()           PORTDbits.RD5
#define LCD_RW_SetDigitalInput()    do { TRISDbits.TRISD5 = 1; } while(0)
#define LCD_RW_SetDigitalOutput()   do { TRISDbits.TRISD5 = 0; } while(0)

// get/set LCD_E aliases
#define LCD_E_TRIS                 TRISDbits.TRISD6
#define LCD_E_LAT                  LATDbits.LATD6
#define LCD_E_PORT                 PORTDbits.RD6
#define LCD_E_SetHigh()            do { LATDbits.LATD6 = 1; } while(0)
#define LCD_E_SetLow()             do { LATDbits.LATD6 = 0; } while(0)
#define LCD_E_Toggle()             do { LATDbits.LATD6 = ~LATDbits.LATD6; } while(0)
#define LCD_E_GetValue()           PORTDbits.RD6
#define LCD_E_SetDigitalInput()    do { TRISDbits.TRISD6 = 1; } while(0)
#define LCD_E_SetDigitalOutput()   do { TRISDbits.TRISD6 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/