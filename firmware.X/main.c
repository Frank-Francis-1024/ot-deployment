/*
 * File:   main.c
 * Author: Ing. Morales Orozco Jose Francisco
 *
 * Created on 2 de noviembre de 2021, 04:58 PM
 */
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

To request to license the code under the MLA license 
(www.microchip.com/mla_license), please contact mla_licensing@microchip.com
 
*******************************************************************************/

/***************************** INCLUDES ***************************************/

#include "usb_device_hid.h"
#include "system.h"
#include "pic18f4550.h"
#include "usb.h"
#include <xc.h>

#define _XTAL_FREQ 20000000L

/***************************** Var_Data ***************************************/

volatile USB_HANDLE USBOutHandle;    
volatile USB_HANDLE USBInHandle;

unsigned char ReceivedDataBuffer[64] HID_CUSTOM_OUT_DATA_BUFFER_ADDRESS;
unsigned char ToSendDataBuffer[64] HID_CUSTOM_IN_DATA_BUFFER_ADDRESS;

/*
 
  Estas funciones se encargan principalmente establecer la comuniacion del 
  modulo USB del microcontrolador PIC 18F4550 y el ordenador mediante una
  interfaz, por defecto se creo una basada en Visual Basic, sin embargo
  puede realizarce la comunicacion con cualquier interfaz basta con conocer los
  parametros de configuracion del modulo USB para establecer la comunicación. 
 
 
*/

/***************************** Functions ***************************************

                                PIC-PC

 * To read  : USBOutHandle = HIDRxPacket(CUSTOM_DEVICE_HID_EP, (uint8_t*)&ReceivedDataBuffer[0], 64);

 * To write : USBInHandle = HIDTxPacket(CUSTOM_DEVICE_HID_EP, (uint8_t*)&ToSendDataBuffer[0],64);

****************************** Main_Program ***********************************/
void main(void)
{
    PIC18F4550_Initialize(PIC18F4550_USB_START);
    USBDeviceInit();
    USBDeviceAttach();
    
    Init_PWM();
   // TRISDbits.RD0 = 0;      //RD0 <= OUT //debug
    while(1)
        {
            USBOutHandle = HIDRxPacket(CUSTOM_DEVICE_HID_EP, (uint8_t*)&ReceivedDataBuffer[0], 64);
            //if(ReceivedDataBuffer[0]<=127){LATDbits.LATD0=0;} else{ LATDbits.LATD0=1;}    //debug
            
            if(ReceivedDataBuffer[3]==1)
            {
                Update_Duty(ReceivedDataBuffer[0],ReceivedDataBuffer[1],ReceivedDataBuffer[2]);
            }
            
            
        }
    return;
}
/******************************************************************************/
