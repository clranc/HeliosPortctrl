/*
 * Routines for initializing and utilizing the IO pins on Ports A, 
 * B, and C in the Helios PC/104 development board for QNX.
 * 
 * (C) 2017-2018 Chris Ranc (clranc94@gmail.com)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public Licence
 * as published by the Free Software Foundation; either version
 * 2.1 of the Licence, or (at your option) any later version.
 */


#include "portctrl.h"

#include <sys/mman.h>
#include <sys/neutrino.h>
#include <hw/inout.h>
#include <pthread.h>
#include <stdio.h>

uintptr_t portAReg;
uintptr_t portBReg;
uintptr_t portCReg;

uintptr_t ioCtrlReg;
uintptr_t baseReg;

/* 
 * Requests permission from QNX to access IO pins of the
 * Helios board and then configures control registers to
 * enable the pins for IO output
 */
int initIOCtrl(void){
    if (ThreadCtl(_NTO_TCTL_IO,NULL)){
        printf("Failed to get access to Helios IO Ports\n");
        return FAILEDPERMISSION;
    }

    ioCtrlReg = mmap_device_io(1, IO_CTRL_REGISTER);
    baseReg   = mmap_device_io(1, BASE_IO_REGISTER);
    portAReg = mmap_device_io(1, PORT_A_REGISTER);
    portBReg = mmap_device_io(1, PORT_B_REGISTER);
    portCReg = mmap_device_io(1, PORT_C_REGISTER);

    out8(baseReg, 0x44);
    /* Default all IO pins to 0. Which initializes ports A, B, and C to output mode */
    out8(ioCtrlReg, 0x00);

    return 0;
}

/*
 * Initalizies one of the ports avaialable for setting pin output
 */
void setPort(enum port prt, int mode){
    uint8_t pin, tmp;
    switch(prt){
        case PORTA :
            pin = 1 << 4;
            break;
        case PORTB :
            pin = 1 << 1;
            break;
        case PORTCH :
            pin = 1 << 3;
        case PORTCL :
            pin = 1;
        default :
            break;
    }
    tmp = in8(ioCtrlReg);
    if (mode)
        out8(ioCtrlReg, tmp | pin);
    else
        out8(ioCtrlReg, tmp & ~pin);
}

/*
 * Sets associated pin on the selected port to be on
 */
void pinOn(enum port prt, uint8_t pn){
    uint8_t pins;
    switch(prt){
        case PORTA :
            pins = in8(portAReg);
            pins |= pn;
            out8(portAReg, pins);
            break;
        case PORTB :
            pins = in8(portBReg);
            pins |= pn;
            out8(portBReg, pins);
            break;
        case PORTC :
            pins = in8(portCReg);
            pins |= pn;
            out8(portCReg, pins);
        default :
            break;
    }
}

/*
 * Sets associated pin on the selected port to be off
 */
void pinOff(enum port prt, uint8_t pn){
    uint8_t pins;
    switch(prt){
        case PORTA :
            pins = in8(portAReg);
            pins &= ~pn;
            out8(portAReg, pins);
            break;
        case PORTB :
            pins = in8(portBReg);
            pins &= ~pn;
            out8(portBReg, pins);
            break;
        case PORTC :
            pins = in8(portCReg);
            pins &= ~pn;
            out8(portCReg, pins);
        default :
            break;
    }
}

/* 
 * Write to all pins on a port 
 */
void writePins(enum port prt, uint8_t pins){
    switch(prt){
        case PORTA :
            out8(portAReg, pins);
            break;
        case PORTB :
            out8(portBReg, pins);
            break;
        case PORTC :
            out8(portCReg, pins);
        default :
            break;
    }
}

/* 
 * See the value of a particular pin on a port 
 */
int readPin(enum port prt, uint8_t pin){
    uint8_t pins = NULL;
    switch(prt){
        case PORTA :
            pins = in8(portAReg);
            pins &= pin;
            break;
        case PORTB :
            pins = in8(portBReg);
            pins &= pin;
            break;
        case PORTC :
            pins = in8(portCReg);
            pins &= pin;
        default :
            break;
    }
    if (pins == pin)
        pins = 1;
    else
        pins = 0;
    return pins;
}

/* 
 * Read all pins on a port 
 */
uint8_t readPort(enum port prt){
    uint8_t pins = NULL;
    switch(prt){
        case PORTA :
            pins = in8(portAReg);
            break;
        case PORTB :
            pins = in8(portBReg);
            break;
        case PORTC :
            pins = in8(portCReg);
        default :
            break;
    }
    return pins;
}
