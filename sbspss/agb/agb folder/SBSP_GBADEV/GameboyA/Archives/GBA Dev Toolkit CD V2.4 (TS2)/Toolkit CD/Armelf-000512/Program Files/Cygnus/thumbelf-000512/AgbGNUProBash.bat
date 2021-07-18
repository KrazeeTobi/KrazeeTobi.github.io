@ECHO OFF

REM
REM    Errors
REM
REM Right-click this file and set "initial size of environment variable" of     
REM "memory" to 4096 if the message of "Not enough area for environment 
REM variable" is displayed.  
REM
REM
REM    Set up
REM
REM
REM Please describe the folder in which each AGB tool is installed in the  
REM following AGBDIR.   
REM
REM Please describe the folder in which each Cygnus tool is installed in 
REM CYGNUSDIR.   
REM

SET AGBDIR=C:/agb
SET CYGNUSDIR=C:/PROGRA~1/Cygnus
SET HOME=%AGBDIR%
SET MAKE_MODE=UNIX

REM Add REM before the following 2 lines and make it a comment if 
REM operating normally. 

ECHO If not operating normally, open this file by text editor and set 
ECHO up according to the explanation in the file. 

REM If REM is added before the following 1 line making it a comment, a path will
REM not be displayed in case of command input of BASH.  
 
SET PS1=[\w] 

SET PATH=%CYGNUSDIR%/thumbelf-000512/H-i686-cygwin32/bin;%CYGNUSDIR%/native-99r1/H-i686-cygwin32/bin;%AGBDIR%/bin;.
bash
