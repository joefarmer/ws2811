C:\Projects\ws2811_2\src>path %path%;c:\WinAVR-20100110\bin;c:\WinAVR-20100110\utils\bin

C:\Projects\ws2811\src>c:\Users\bmiller\Downloads\avrdude-6.1\avrdude.exe -c usbtiny -p t87 -v -U flash:w:"ws2811_controller.hex":a

C:\Projects\ws2811\src>c:\Users\bmiller\Downloads\avrdude-6.1\avrdude.exe -c usbtiny -p t87 -v -U lfuse:w:0xE2:m -U hfuse:w:0xDF:m -U efuse:w:0xFF:m -U lock:w:0xFF:m

