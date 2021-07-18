
armasm -Littleend -cpu ARM7TDMI start.c 




armcc -c -Wall -Otime -ansic -fpu none -Littleend -cpu ARM7TDMI -apcs /narrow/noswst test2.c -o test.o

pause
armlink -bin -first start.o -map -ro-base 0x08000000 -rw-base 0x3000000 start.o  test.o  -o maze.bin

del *.o

