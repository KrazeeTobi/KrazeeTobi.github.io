SET GCC_EXEC_PREFIX=C:\PROGRA~1\Cygnus\armelf-981216\H-i586-cygwin32\lib\gcc-lib\
SET PATH=C:\PROGRA~1\Cygnus\armelf-981216\H-i586-cygwin32\bin;c:\PROGRA~1\CYGNUS\CYGWIN~1\H-I586~1\BIN;.;
SET GCC_EXEC_PREFIX=C:\PROGRA~1\Cygnus\thumbelf-981216\H-i586-cygwin32\lib\gcc-lib\
SET PATH=C:\PROGRA~1\Cygnus\thumbelf-981216\H-i586-cygwin32\bin;c:\PROGRA~1\CYGNUS\CYGWIN~1\H-I586~1\BIN;.;
gcc.exe -mthumb-interwork -O2 -S -I../AgbInclude main.c
pause
