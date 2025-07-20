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

#ifndef SYSTEM_H
#define SYSTEM_H

#include <xc.h>
#include <stdbool.h>
#include <stdint.h>
#include "io_mapping.h"

//#define MAIN_RETURN void
/******************************************************************************/


/*******************************Buffers IO DATA********************************/
                    /*#include "fixed_address_memory.h"*/

#define HID_CUSTOM_OUT_DATA_BUFFER_ADDRESS      __at(0x500)
#define HID_CUSTOM_IN_DATA_BUFFER_ADDRESS     __at(0x540)

/*** System States **************************************************/
typedef enum
{
    PIC18F4550_USB_START,
    PIC18F4550_USB_SUSPEND,
    PIC18F4550_USB_RESUME
} PIC18F4550;

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
********************************************************************/
void PIC18F4550_Initialize( PIC18F4550 state );


/*********************************************************************
* Function: void SYSTEM_Tasks(void)
*
* Overview: Runs system level tasks that keep the system running
*
* PreCondition: System has been initalized with SYSTEM_Initialize()
*
* Input: None
*
* Output: None
*
********************************************************************/
//void SYSTEM_Tasks(void);
#define SYSTEM_Tasks()

#endif //SYSTEM_H

#define INTERRUPT_H __interrupt(high_priority)
/********************************************************************/

/*PWM Functions*/

#define LED_R LATCbits.LATC0
#define LED_G LATCbits.LATC1
#define LED_B LATCbits.LATC2

#define INTERRUPT_L __interrupt(low_priority)
#define UInt8   volatile unsigned char
#define UInt16  volatile unsigned int

void Init_PWM(void);
void INTERRUPT_L pwm_low_priority();

void Update_PWM(void);
void Update_Duty(UInt8 red_Duty,UInt8 green_Duty,UInt8 blue_Duty);
/* ADC Functions */
/*
 void Init_ADC(void);
unsigned int Read_ADC(void);
 */
/********************************************************************/