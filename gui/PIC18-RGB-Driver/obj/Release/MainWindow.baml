   M S B A M L   `   `   `  ���� K  GPIC18-RGB-Driver, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null3clr-namespace:PIC18_RGB_DriverPIC18_RGB_Driver  !    PIC18_RGB_Driver.MainWindow   R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     @d2http://schemas.microsoft.com/expression/blend/2008     Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     0localclr-namespace:PIC18_RGB_Driver       � Title$  PIC18-RGB-Driver��$	��300��$	��462�� � Icon$ 	/Icon.ico�� � 
ResizeMode$ NoResize=�
���   �
���   � � WindowStyle$
 None=� � WindowStartupLocation$ CenterScreen=�.��� .+��� -   
���   �
�������$	�� ? ��$
��Left=�$��	386,0,0,0q�$	��Top=�
���   �$��20��$��40��$��Consolas)�$��14(��� -   
���   �
�������$	�� X ��$
��Left=�$��	422,0,0,0q�$	��Top=�
���   �$��20��$��40��$��Consolas)�$��14(��� $��PIC18-RGB-Driver��
�������$
��Left=�$	��Top=�$��14(�$
��Bold"�$��29��$	��128���� $��LED Control Panel:��
�������$
��Left=�$	��Top=�$��14(�$
��Bold"�$��	48,71,0,0q�$��29��$	��132���� -    ��Name$ SlideRed��
�������$
��Left=�$��
52,128,0,0q�$	��Top=�$	��120�� � Maximum$	 255Q� � SmallChange$ 0Q�$��18�� � Value$	 128Q��� -   $ 
SlideGreen��
�������$
��Left=�$��
52,168,0,0q�$	��Top=�$	��120��$	 255Q�$��18��$	 128Q��� -   $ 	SlideBlue��
�������$
��Left=�$��
52,208,0,0q�$	��Top=�$	��120��$	 255Q�$��18��$	 128Q�A� $
��Left=�$��20��$��178,128,0,0q�
�������$	��Top=�$��20��
���  ��A� $
��Left=�$��20��$��178,168,0,0q�
�������$	��Top=�$��20��
���2�2�A� $
��Left=�$��20��$��178,208,0,0q�
�������$	��Top=�$��20��
����� ��� $��R��
�������$
��Left=�$	��Top=�$��14(�$
��Bold"�$��
28,122,0,0q�$��29��$��19���� $��G��
�������$
��Left=�$	��Top=�$��14(�$
��Bold"�$��
28,162,0,0q�$��29��$��20���� $��B��
�������$
��Left=�$	��Top=�$��14(�$
��Bold"�$��
28,202,0,0q�$��29��$��19���� $��Center=�$��40��$	��Top=�$��40��$��/circuit.png��$��	0,157,0,0q��� $��
Auto Mode:��
�������$
��Left=�$	��Top=�$��14(�$
��Bold"�$��
308,71,0,0q�$��29��$��89���� -   	 ��Name$	 CBMode��$
��Left=�$��308,126,0,0q�$	��Top=�$��89��@��� 
 �� 
IsSelected
 . .��Manual�� .��Static Color�� .��Sweep Color