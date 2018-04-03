/*
 * Contains functions protoytpes, structs, and defines relevant 
 * to initializing IO Ports on the Helios PC/104 development board 
 * to utilize the relevant port pins  for I/O
 * 
 * (C) 2017-2018 Chris Ranc (clranc94@gmail.com)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public Licence
 * as published by the Free Software Foundation; either version
 * 2.1 of the Licence, or (at your option) any later version.
 */


#ifndef PORT_CTRL
#define PORT_CTRL

#include <stdint.h>

/* IO Control register addresses */
#define BASE_IO_REGISTER 0x280
#define PORT_A_REGISTER  0x288
#define PORT_B_REGISTER  0x289
#define PORT_C_REGISTER  0x28A
#define IO_CTRL_REGISTER 0x28B

/* IO mode defines */
#define OUT 0
#define IN  1

/* Defines for each pin in ports A, B, and C */
#define PIN0 0x01
#define PIN1 0x02
#define PIN2 0x04
#define PIN3 0x08
#define PIN4 0x10
#define PIN5 0x20
#define PIN6 0x40
#define PIN7 0x80

/* Defines for return codes */
#define FAILEDPERMISSION -1

/* Enumerators for IO ports
 * ** Each port can either only be configured for
 *    performing output or input.  With the exception
 *    of PORTC.  The high half and low half of PORTC
 *    can be configured seperately.
 */
enum port{
    PORTA,
    PORTB,
    PORTC,
    PORTCH,
    PORTCL
};

/* Acquire access IO control registers and initialize them */
int initIOCtrl(void);

/* Set IO mode of GPIO port */
void setPort(enum port pr, int mode);

/* Turn a pin in an GPIO port on */
void pinOn(enum port prt, uint8_t pn);

/* Turn a pin in a GPIO port off */
void pinOff(enum port prt, uint8_t pn);

/* Write a byte value to a GPIO port register */
void writePins(enum port prt, uint8_t pins);

/* Read the value of a particular pin on a GPIO port */
int readPin(enum port prt, uint8_t pin);

/* Readd the whole byte of a GPIO port */
uint8_t readPort(enum port prt);
#endif /* PORT_CTRL */
