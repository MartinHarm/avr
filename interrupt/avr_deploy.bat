@Echo Off
echo ----------------- Compiling C code to Object file --------------
avr-gcc -g -Os -mmcu=attiny2313 -c %1.c
echo ----------------- Building ELF file ----------------------------
avr-gcc -g -mmcu=attiny2313 -o %1.elf %1.o
echo ----------------- Building INTEL HEX file ----------------------
avr-objcopy -j .text -j .data -O ihex %1.elf %1.hex
echo ----------------- Flashing HEX to MCU --------------------------
avrdude -p attiny2313 -c usbtiny -b 19200 -v -U flash:w:%1.hex -F