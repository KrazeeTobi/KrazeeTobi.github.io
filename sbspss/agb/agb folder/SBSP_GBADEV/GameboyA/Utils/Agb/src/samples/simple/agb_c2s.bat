SET PATH=C:\PROGRA~1\Cygnus\armelf-000512\H-i686-cygwin32\bin;C:\PROGRA~1\CYGNUS\native-99r1\H-I686~1\BIN;.;
SET PATH=C:\PROGRA~1\Cygnus\thumbelf-000512\H-i686-cygwin32\bin;C:\PROGRA~1\CYGNUS\native-99r1\H-I686~1\BIN;.;
gcc.exe -mthumb-interwork -O2 -S -I../../../include main.c
pause
