zarmasm -CPU ARM7TDMI -Littleend start.asm
zarmasm -CPU ARM7TDMI -Littleend data.asm
zarmcc -c -Wall -Otime -ansic -fpu none -Littleend -cpu ARM7TDMI -apcs /narrow/noswst roto.c -o roto.o
pause
zarmlink -bin -first start.o start.o data.o roto.o -map -ro-base 0x08000000 -o roto.bin
@del *.o
D:\GBA\Igba.exe D:\GBA\roto\roto.bin