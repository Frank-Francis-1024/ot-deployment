/*******************************************************************************
Copyright 2016 Microchip Technology Inc. (www.microchip.com)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

To request to license the code under the MLA license (www.microchip.com/mla_license), 
please contact mla_licensing@microchip.com
*******************************************************************************/

#include <xc.h>
#include "system.h"
#include "usb.h"


/** CONFIGURATION Bits **********************************************/
#pragma config PLLDIV   = 5         // (20 MHz crystal on PICDEM FS USB board)
#pragma config CPUDIV   = OSC1_PLL2
#pragma config USBDIV   = 2         // Clock source from 96MHz PLL/2
#pragma config FOSC     = HSPLL_HS
#pragma config FCMEN    = OFF
#pragma config IESO     = OFF
#pragma config PWRT     = OFF
#pragma config BOR      = ON
#pragma config BORV     = 3
#pragma config VREGEN   = ON      //USB Voltage Regulator
#pragma config WDT      = OFF
#pragma config WDTPS    = 32768
#pragma config MCLRE    = ON
#pragma config LPT1OSC  = OFF
#pragma config PBADEN   = OFF
//#pragma config CCP2MX   = ON
#pragma config STVREN   = ON
#pragma config LVP      = OFF
//#pragma config ICPRT    = OFF       // Dedicated In-Circuit Debug/Programming
#pragma config XINST    = OFF       // Extended Instruction Set
#pragma config CP0      = OFF
#pragma config CP1      = OFF
//#pragma config CP2      = OFF
//#pragma config CP3      = OFF
#pragma config CPB      = OFF
//#pragma config CPD      = OFF
#pragma config WRT0     = OFF
#pragma config WRT1     = OFF
//#pragma config WRT2     = OFF
//#pragma config WRT3     = OFF
#pragma config WRTB     = OFF       // Boot Block Write Protection
#pragma config WRTC     = OFF
//#pragma config WRTD     = OFF
#pragma config EBTR0    = OFF
#pragma config EBTR1    = OFF
//#pragma config EBTR2    = OFF
//#pragma config EBTR3    = OFF
#pragma config EBTRB    = OFF

/*********************************************************************
* Function: void SYSTEM_Initialize( SYSTEM_STATE state )
*
* Overview: Initializes the system.
*
* PreCondition: None
*
* Input:  SYSTEM_STATE - the state to initialize the system into
*
* Output: None
*
**************************PIC18F4550_USB_START*********************************/
void PIC18F4550_Initialize( PIC18F4550 state )
{
    switch(state)
    {
        case PIC18F4550_USB_START:
            break;
            
        case PIC18F4550_USB_SUSPEND:
            break;
            
        case PIC18F4550_USB_RESUME:
            break;
    }
}
/******************************************************************************/
				
#if(__XC8_VERSION < 2000)
    #define INTERRUPT interrupt
#else
    #define INTERRUPT_H __interrupt(high_priority)
#endif			

void INTERRUPT_H SYS_InterruptHigh(void)
{
    #if defined(USB_INTERRUPT)
        USBDeviceTasks();
    #endif
}

/******************************************************************************/

/*PWM Functions*/



UInt8   duty_R, duty_G, duty_B;
UInt16  count = 0;

void Init_PWM(void)
{
    TRISCbits.RC0 = TRISCbits.RC1 = TRISCbits.RC2 = 0;      // RC[0:2] <= OUT
    duty_R = duty_G = duty_B = 127;                         // RGB.duty <= 50%
    count = 0;                                              // Clear Counter
    
    PIE1bits.TMR2IE = 1;                                    // TMR2.Interrupt = ON
    IPR1bits.TMR2IP = 0;                                    // TMR2.Priority = LOW
    
    INTCONbits.GIEH = 1;                                    // Interrupt.HighPriority = ON
    INTCONbits.GIEL = 1;                                    // Interrupt.LowPriority = ON
    
    PR2 = 0x10;                                             // PR2 <= 255 = Max Period
    T2CON = 0x00;                                           // Postscale = Prescale = 1:1
    T2CONbits.TMR2ON = 1;                                   // TMR2 <= ON
}

void Update_Duty(UInt8 red_Duty,UInt8 green_Duty,UInt8 blue_Duty)
{
    duty_R = duty_G = duty_B = 0;
    duty_R += red_Duty;
    duty_G += green_Duty;
    duty_B += blue_Duty;
}

void INTERRUPT_L pwm_low_priority() 
{
    if (PIR1bits.TMR2IF)                                    //TMR2.Interrupt.Event <= true
    {
       Update_PWM();
       PIR1bits.TMR2IF = 0;                                //Clear Interrupt Flag
    }
}

void Update_PWM(void)
{
    if(count<256){ count++;} else{count = count - count;}
    if(duty_R >= count){if(duty_R==0){LED_R = 0;} else{ LED_R = 1;}} else if(duty_R < count){LED_R = 0;}
    if(duty_G >= count){if(duty_G==0){LED_G = 0;} else{ LED_G = 1;}}else if(duty_G < count){LED_G = 0;}
    if(duty_B >= count){if(duty_B==0){LED_B = 0;} else{ LED_B = 1;}} else if(duty_B < count){LED_B = 0;}
}

/******************************************************************************/

/* ADC Functions */
/*
 void Init_ADC(void)
{
    // Configuración del ADC
    TRISAbits.RA0 = 1;          // RA0 como entrada
    
    ADCON1bits.PCFG = 0b1110;   // Configurar AN0 como analogico 
    ADCON0bits.CHS = 0;         // Seleccionar el canal AN0
    ADCON1bits.VCFG0 = 0;       // Voltaje de referencia VDD
    ADCON1bits.VCFG1 = 0;       // Voltaje de referencia VSS
    ADCON2bits.ADFM = 1;        // Justificado a la derecha
    
    ADCON2bits.ACQT = 2;        // Tiempo de adquisición de 4 TAD
    ADCON2bits.ADCS = 7;        // FOSC/2 como fuente de reloj del ADC
    
    ADCON0bits.ADON = 1;        // Activar el módulo ADC
    // Configuración de los pines ANSEL para habilitar la función de entrada analógica
    //ANSELbits.ANS0 = 1;         // Habilitar AN0 como entrada analógica
}
unsigned int Read_ADC(void)
{
    ADCON0bits.GO = 1;          // Iniciar la conversión ADC
    
    while (ADCON0bits.GO);      // Esperar a que la conversión se complete
    
    unsigned int adcValue = ADRESL;
    //unsigned int adcValue = ADRESH;  // Leer el byte alto del resultado
   // adcValue = (adcValue << 8) | ADRESL;  // Combinar con el byte bajo
    
    return adcValue;            // Retornar el valor del ADC
}
 */
/******************************************************************************/