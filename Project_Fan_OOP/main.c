#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdio.h>

#include "ap/apMain.h"

int main(void)
{
	ap_init();
	
    while (1) 
    {
		ap_excute();
    }
}

