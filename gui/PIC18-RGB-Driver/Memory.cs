using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace PIC18_RGB_Driver
{
    public class Memory
    {
        public void Init_Files()
        {
            if (File.Exists(@"C:\red.rgb")){ }else {try { File.Create(@"C:\red.rgb"); } catch { }}
            if (File.Exists(@"C:\green.rgb")) { } else { try { File.Create(@"C:\green.rgb"); } catch { } }
            if (File.Exists(@"C:\blue.rgb")) { } else { try { File.Create(@"C:\blue.rgb"); } catch { } }
        } 
        public void Save_Config(byte red, byte green, byte blue) 
        {

            byte[] miVariablered = { red };

            // Ruta del archivo de destino
            string rutaArchivored = "C:/redColor.rgb";

            // Escribir la variable en el archivo
            File.WriteAllBytes(rutaArchivored, miVariablered);

            byte[] miVariablegreen = { green };

            // Ruta del archivo de destino
            string rutaArchivogreen = "C:/greenColor.rgb";

            // Escribir la variable en el archivo
            File.WriteAllBytes(rutaArchivogreen, miVariablegreen);


            byte[] miVariableblue = { blue };

            // Ruta del archivo de destino
            string rutaArchivoblue = "C:/blueColor.rgb";

            // Escribir la variable en el archivo
            File.WriteAllBytes(rutaArchivoblue, miVariableblue);

        }
        public byte Read_Red_Conf()
        {

            string rutaArchivo = "C:/redColor.rgb";

            // Leer el contenido del archivo
            byte[] contenidoArchivo = File.ReadAllBytes(rutaArchivo);
           
            // Cargar el contenido en una variable
            byte miVariable = contenidoArchivo[0];
            return Convert.ToByte(miVariable);
        }
        public byte Read_Green_Conf()
        {

            string rutaArchivo = "C:/greenColor.rgb";

            // Leer el contenido del archivo
            byte[] contenidoArchivo = File.ReadAllBytes(rutaArchivo);

            // Cargar el contenido en una variable
            byte miVariable = contenidoArchivo[0];
            return Convert.ToByte(miVariable);
        }
        public byte Read_Blue_Conf()
        {

            string rutaArchivo = "C:/blueColor.rgb";

            // Leer el contenido del archivo
            byte[] contenidoArchivo = File.ReadAllBytes(rutaArchivo);

            // Cargar el contenido en una variable
            byte miVariable = contenidoArchivo[0];
            return Convert.ToByte(miVariable);
        }
    }
}
