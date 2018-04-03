# Helios Portctrl : A library for easy utilization of the Helios PC/104 GPIO pins

## Descriptions
This is a small C library I made to help with my embedded systems classes to 
have easy access to the Helios PC/104's GPIO pins when developing for QNX Neutrino.

## Example Program

A simple blinky program for blinking 2 LEDs:

    int main(void) {
        int i;
        if (initIOCtrl() == FAILEDPERMISSION){
            return;
        }

        setPort(PORTA, IN);
        setPort(PORTB, OUT);
            
        while (1){
            for(i=0; i < 10000; i++);
            pinOn(PORTB, PIN0);
            
            if(readPin(PORTA, PIN0))
                pinOn(PORTB, PIN1);
            
            for(i=0; i < 10000; i++);
            pinOff(PORTB, PIN0);
            
            pinOff(PORTB, PIN1);
        }
    }

