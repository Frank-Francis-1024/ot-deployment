using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.RightsManagement;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using HidLibrary;

namespace PIC18_RGB_Driver
{
    public class HID_Device
    {
        public HidDevice device = HidDevices.Enumerate(0x04DA, 0x0042).FirstOrDefault();

        public void Send_Data(byte red, byte green, byte blue)
        {
            if (device == null)
            {
                MessageBox.Show("No se encontró el dispositivo HID USB.","Error");
                return;
            }
                        //     Init, [      RGB      ],  EN,    Mode

            byte[] setData = { 0x00, red, green, blue, 0x01};
            device.Write(setData);
            byte[] stopData = { 0x00, red, green, blue, 0x00};
            device.Write(stopData);
           // MessageBox.Show("Datos enviados al dispositivo HID USB.","Aviso");  //debug
        }
        
    }
}
