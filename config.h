#ifndef CONFIG_H
#define CONFIG_H

//#device ICD=TRUE
#use delay(clock = 8Mhz, internal = 8Mhz)
#use rs232(baud = 9600, xmit = PIN_C4, rcv = PIN_C5)

// register define
#BYTE OSCCON = 0x099
#BYTE BAUDCON = 0x19F
#BYTE TRISA = 0x08C
#BYTE TRISC = 0x08E
#BYTE PORTA = 0x00C
#BYTE PORTC = 0x00E
#BYTE TXREG = 0x19A
#BYTE TXSTA = 0x19E
#BYTE RCSTA = 0x19D
#BYTE SPBRG = 0x19B
#BIT TRMT = 0x19E.1
#BIT LATC1 = 0x10E.1
#BIT RCIF = 0x011.5

#define BASE_OF_YEAR 1970
#define MONTH_IN_YEAR 12
#define HOUR_IN_DAY 24
#define MIN_IN_HOUR 60
#define SEC_IN_MIN 60

char *commands[] = {"@UTC", "@POS", "@SET", "@GET", "@NUM", "@BAT"};

unsigned char msg1[] = "$$$";			   // Command Mode
unsigned char msg2[] = "SF,1\r";		   // Factory Reset
unsigned char msg3[] = "SN,BT20160625\r";  // Device Name
unsigned char msg4[] = "SA,4\r";		   // Authentication Mode
unsigned char msg5[] = "R,1\r";			   // Reboot

#endif
