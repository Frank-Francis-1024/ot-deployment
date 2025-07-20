using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;

using static PIC18_RGB_Driver.HID_Device;
using static PIC18_RGB_Driver.Memory;

namespace PIC18_RGB_Driver
{
    /// <summary>
    /// Lógica de interacción para MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private StringBuilder stringBuilder = new StringBuilder();
        private DispatcherTimer timer=new DispatcherTimer();

        public HID_Device PIC18 = new HID_Device();
        public Memory config=new Memory();  

        public MainWindow()
        {
            InitializeComponent();

            stringBuilder.Append("IPN\n");
            stringBuilder.Append("ESIME Z\n");
            stringBuilder.Append("ICE\n");
            stringBuilder.Append("Computación\n");
            stringBuilder.Append("Arquitectura de Computadoras\n");
            stringBuilder.Append("8CM12\n");
            stringBuilder.Append("Proyecto: Microcontrolador\n");
            stringBuilder.Append("Por: Ing.Morales Orozco José Francisco\n");
            stringBuilder.Append("Email: jmoraleso1602@gmail.com\n");


            //config.Init_Files();
            //try 
            //{
            //    SlideRed.Value = config.Read_Red_Conf();
            //    SlideGreen.Value = config.Read_Green_Conf();
            //    SlideBlue.Value = config.Read_Blue_Conf();
            //}
            //catch
            //{
            //    config.Save_Config(127, 127, 127);
            //}


            timer = new DispatcherTimer();
            timer.Interval = TimeSpan.FromMilliseconds(10);
            timer.Tick += Timer_Tick;
            timer.Start();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            //Close();
            Hide();
            //config.Save_Config(Convert.ToByte(SlideRed.Value), Convert.ToByte(SlideGreen.Value), Convert.ToByte(SlideBlue.Value));
        }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            Author author = new Author();
            author.Show();
        }

        
        private byte duty_Red=0, duty_Green = 0, duty_Blue = 0, count=0;
        bool increment = true;

        private void Timer_Tick(object sender, EventArgs e)
        {
            switch (CBMode.SelectedIndex)
            {
                case 0: break;                      //Modo Manual
                case 1: 
                    {
                        if (count == 0)
                        {
                            // duty_Red++;
                            // if (duty_Red > 254) { count++; duty_Red = 0; }

                            if(increment)
                            {
                                duty_Red++;
                                if (duty_Red > 254) { increment=false;}
                            }
                            else
                            {
                                duty_Red--;
                                if (duty_Red < 1) { increment = true; count++; }
                            }
                        }
                        else if (count == 1)
                        {

                            if (increment)
                            {
                                duty_Green++;
                                if (duty_Green > 254) { increment = false; }
                            }
                            else
                            {
                                duty_Green--;
                                if (duty_Green < 1) { increment = true; count++; }
                            }
                        }
                        else if (count == 2)
                        {

                            if (increment)
                            {
                                duty_Blue++;
                                if (duty_Blue > 254) { increment = false; }
                            }
                            else
                            {
                                duty_Blue--;
                                if (duty_Blue < 1) { increment = true; count++; }
                            }
                        }
                        else if (count > 2) { count = 0; }
                        PIC18.Send_Data(duty_Red,duty_Green, duty_Blue);
                        SlideRed.Value = duty_Red;
                        SlideGreen.Value = duty_Green;
                        SlideBlue.Value = duty_Blue;
                    }
                    break;                         
                case 2: 
                    {
                        if (count == 0)
                        {
                            if (duty_Red < 254) { duty_Red++; }
                            else { count++; }
                           
                        }
                        else if (count == 1)
                        {
                            if (duty_Blue >= 1) { duty_Blue--; }
                            else if (duty_Blue < 1) { count++; }
                        }
                        else if (count == 2)
                        {
                            if (duty_Green < 254) { duty_Green++; }
                            else { count++; }
                        }
                        else if (count == 3)
                        {
                            if (duty_Red >= 1) { duty_Red--; }
                            else if (duty_Red < 1) { count++; }
                        }
                        else if (count == 4)
                        {
                            if (duty_Blue < 254) { duty_Blue++; }
                            else { count++; }
                        }
                        else if (count == 5)
                        {
                            if (duty_Green >= 1) { duty_Green--; }
                            else if (duty_Green < 1) { count++; }
                        }
                        else if(count > 5) { count = 0; }

                        PIC18.Send_Data(duty_Red, duty_Green, duty_Blue);
                        SlideRed.Value = duty_Red;
                        SlideGreen.Value = duty_Green;
                        SlideBlue.Value = duty_Blue;

                    }
                    break;
                default: break;
            }
        }


        private void SlideRed_PreviewMouseUp(object sender, MouseButtonEventArgs e)
        {
            PIC18.Send_Data(Convert.ToByte(SlideRed.Value), Convert.ToByte(SlideGreen.Value), Convert.ToByte(SlideBlue.Value));
           // MessageBox.Show(SlideBlue.Value.ToString(), "valor de azul");   //debug
        }

        private void CBMode_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if(CBMode.SelectedIndex==0) 
            {
                timer.Stop();
                SlideRed.IsEnabled = true;
                SlideGreen.IsEnabled = true;
                SlideBlue.IsEnabled = true;
            } 
            else 
            { 
                timer.Start();
                SlideRed.IsEnabled = false;
                SlideGreen.IsEnabled = false;
                SlideBlue.IsEnabled = false;
            }
        }
    }
}
