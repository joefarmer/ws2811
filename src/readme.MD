C:\Projects\ws2811_2\src>path %path%;c:\WinAVR-20100110\bin;c:\WinAVR-20100110\utils\bin

C:\Users\admin>c:\projects\avrdude-6.1\avrdude.exe -c usbasp -p t87 -v -U flash:w:"c:\projects\ws2811\ws2811\Debug\ws2811.hex":a

C:\Users\admin>c:\projects\avrdude-6.1\avrdude.exe -c usbasp -p t87 -v -U lfuse:w:0xE2:m -U hfuse:w:0xDF:m -U efuse:w:0xFF:m -U lock:w:0xFF:m
