/*
 * File:   lcd.c
 * Author: dan1138
 *
 */

#include "mcc_generated_files/mcc.h"
#include "lcd.h"

#if (LCD_DATA_BITS == 0x0F)
  #define LCD_DATA_ON_LOW_4_BITS
#else
  #if (LCD_DATA_BITS == 0xF0)
    #define LCD_DATA_ON_HIGH_4_BITS
  #else
    #error LCD interface supports 4-bit mode only on high or low 4-bits of one port
  #endif
#endif

static unsigned char LCD_BusyBit;

static const unsigned char CGRAM_Table[] =
{
    0b10000000, /* CGRAM character 1 */
    0b10000100,
    0b10000010,
    0b10001111,
    0b10000010,
    0b10000100,
    0b10000000,
    0b10011111,

    0b10001110, /* CGRAM character 2 */
    0b10010001,
    0b10010000,
    0b10010000,
    0b10010001,
    0b10001110,
    0b10000000,
    0b10011111,

    0b10001110, /* CGRAM character 3 */
    0b10010001,
    0b10010000,
    0b10010011,
    0b10010001,
    0b10001110,
    0b10000000,
    0b10011111,

    0b10000000, /* CGRAM character 4 */
    0b10001110,
    0b10001010,
    0b10001010,
    0b10001110,
    0b10000000,
    0b10000000,
    0b10011111,

    0b10011110, /* CGRAM character 5 */
    0b10010001,
    0b10010001,
    0b10011110,
    0b10010010,
    0b10010001,
    0b10000000,
    0b10011111,

    0b10001110, /* CGRAM character 6 */
    0b10010001,
    0b10010001,
    0b10011111,
    0b10010001,
    0b10010001,
    0b10000000,
    0b10011111,

    0b10010001, /* CGRAM character 7 */
    0b10011011,
    0b10010101,
    0b10010101,
    0b10010001,
    0b10010001,
    0b10000000,
    0b10011111,

    0b10000000, /* CGRAM character 8 */
    0b10000100,
    0b10001000,
    0b10011110,
    0b10001000,
    0b10000100,
    0b10000000,
    0b10011111,
};

static void LCD_E_Pulse(void)
{
    E_PIN = 1;
    __delay_us(4);
    E_PIN = 0;
    __delay_us(4);
}

static void LCD_DelayPOR(void)
{
    __delay_ms(15);
}

static void LCD_Delay(void)
{
    __delay_ms(5);
}

static unsigned char LCD_GetByte(void)
{
    unsigned char LCD_Data;

    LCD_PORT_DIR |= LCD_DATA_BITS; /* make LCD data bits inputs */
    RW_PIN = 1;

    E_PIN = 1;
    __delay_us(4);
    LCD_Data = (unsigned char)(LCD_PORT_IN & LCD_DATA_BITS);
    E_PIN = 0;
    __delay_us(4);

    LCD_Data = (unsigned char)((LCD_Data >> 4) | (LCD_Data << 4));

    E_PIN = 1;
    __delay_us(4);
    LCD_Data |= (unsigned char)(LCD_PORT_IN & LCD_DATA_BITS);
    E_PIN = 0;
    __delay_us(4);

#ifdef LCD_DATA_ON_HIGH_4_BITS
    LCD_Data = (unsigned char)((LCD_Data >> 4) | (LCD_Data << 4));
#endif
    return LCD_Data;
}

static void LCD_PutByte(unsigned char LCD_Data)
{
    LCD_PORT_DIR &= ~LCD_DATA_BITS; /* make LCD data bits outputs */
    RW_PIN = 0;

    /* send first nibble */
    LCD_PORT_OUT &= ~LCD_DATA_BITS;
#if !defined(LCD_DATA_ON_HIGH_4_BITS)
    LCD_Data = (unsigned char)((LCD_Data >> 4) | (LCD_Data << 4));
#endif
    LCD_PORT_OUT |= (unsigned char)(LCD_Data & LCD_DATA_BITS);
    LCD_E_Pulse();

    LCD_Data = (unsigned char)((LCD_Data >> 4) | (LCD_Data << 4));
    LCD_PORT_OUT &= ~LCD_DATA_BITS;
    LCD_PORT_OUT |= (unsigned char)((LCD_Data) & LCD_DATA_BITS);
    LCD_E_Pulse();

    LCD_PORT_DIR |= LCD_DATA_BITS; /* make LCD data bits inputs */
}

static void LCD_Busy(unsigned char SpinWait)
{
    if (LCD_BusyBit)
    {
        /* When busy bit is available test it */
        unsigned char LCD_Data;

        LCD_PORT_DIR |= LCD_DATA_BITS; /* make LCD data bits inputs */
        LCD_Data = 0;

        RS_PIN = 0;
        RW_PIN = 1;
        do
        {
            LCD_Data = LCD_GetByte();
        } while (LCD_Data & LCD_BusyBit);
    }
    else
    {
        /* When busy bit is not available do a spin wait */
        do
        {
            __delay_us(40); /* worst delay case for data type transaction */
        } while(--SpinWait);
    }
}

void LCD_Init(void)
{
    unsigned char LCD_Data;

    LCD_BusyBit = 0;
    LCD_PORT_DIR &= ~LCD_DATA_BITS; /* make LCD data bits outputs */
    E_PIN_DIR = 0;                  /* make LCD Enable strobe an output */
    RW_PIN_DIR = 0;                 /* make LCD Read/Write select an output */
    RS_PIN_DIR = 0;                 /* make LCD Register select an output */
#ifdef LCD_POWER_EN_DIR
    LCD_POWER_EN_DIR = 0;           /* make LCD Power enable an output */
#endif
    E_PIN = 0;                      /* set LCD Enable strobe to not active */
    RW_PIN = 0;                     /* set LCD Read/Write select to Write */
    RS_PIN = 0;                     /* set LCD Register select to command group */
    LCD_PORT_OUT &= ~LCD_DATA_BITS; /* set LCD data bits to zero */
#ifdef LCD_POWER_EN
    LCD_POWER_EN = 1;               /* Turn on LCD power */
#endif
    LCD_DelayPOR();                 /* wait for LCD power on to complete */

    /* Force LCD to 8-bit mode */
    LCD_PORT_OUT &= ~LCD_DATA_BITS; /* set LCD data bits to zero */
    LCD_PORT_OUT |= (0b00110011u & LCD_DATA_BITS);
    LCD_E_Pulse();
    LCD_Delay();
    LCD_E_Pulse();
    LCD_Delay();
    LCD_E_Pulse();
    LCD_Delay();

    /* Set LCD to 4-bit mode */
    LCD_PORT_OUT &= ~LCD_DATA_BITS; /* set LCD data bits to zero */
    LCD_PORT_OUT |= (0b00100010u & LCD_DATA_BITS);
    LCD_E_Pulse();
    LCD_Delay();

    /* Initialize LCD mode */
    LCD_WriteCmd(LCD_FORMAT);
    LCD_Delay();

    /*
     * Find position of busy bit.
     * Required when using 4-bit mode.
     */
    LCD_SetPosition(LINE_ONE+1);
    LCD_Busy(1);
    RS_PIN = 0;
    LCD_Data = LCD_GetByte();

    if (LCD_Data == 0x01)
    {
        LCD_BusyBit = 0x80;
    }
    else
    {
        if (LCD_Data == 0x10)
        {
            LCD_BusyBit = 0x08;
        }
    }

    /* Turn on display, Setup cursor and blinking */
    LCD_WriteCmd(DOFF & CURSOR_OFF & BLINK_OFF);
    LCD_WriteCmd(DON & CURSOR_OFF & BLINK_OFF);
    LCD_WriteCmd(CLEAR_DISPLAY);
    LCD_WriteCmd(SHIFT_CUR_LEFT);

    /* Initialize the character generator RAM */
    LCD_SetCGRamAddr(0);
    for(unsigned char Index = 0; Index < sizeof(CGRAM_Table); Index++)
    {
        LCD_WriteData(CGRAM_Table[Index]);
    }

    /* Set first position on line one, left most character */
    LCD_SetPosition(LINE_ONE);
}

void LCD_SetCGRamAddr(unsigned char data)
{
    RS_PIN = 0;
    LCD_PutByte(data | 0x40u);
    LCD_Busy(1);
}

void LCD_SetPosition(unsigned char data)
{
    RS_PIN = 0;
    LCD_PutByte(data | 0x80u);
    LCD_Busy(1);
}

void LCD_WriteCmd(unsigned char data)
{
    RS_PIN = 0;
    LCD_PutByte(data);
    LCD_Busy(50);
}

void LCD_WriteData(unsigned char data)
{
    RS_PIN = 1;
    LCD_PutByte(data);
    RS_PIN = 0;
    LCD_Busy(1);
}

void LCD_WriteString(char * pString)
{
    while(*pString)
    {
        LCD_WriteData(*pString);
        pString++;
    }
}
