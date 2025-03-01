@echo off 
 
 
setlocal ENABLEDELAYEDEXPANSION 
 
color 02 
 
for /l %%i in (1,1,80) do ( 
 
set Down%%i=0 
 
) 
 
:loop 
 
for /l %%j in (1,1,80) do ( 
 
set /a Down%%j-=1 
 
if !down%%j! LSS 0 ( 
 
set /a Arrow%%j=!random!%%4 
 
set /a Down%%j=!random!%%15+10 
 
) 
 
if "!Arrow%%j!" == "1" ( 
 
set /a chr=!random!%%2 
 
set /p=!chr!<NUL 
 
) else ( 
 
set /p= <NUL 
 
) 
 
) 
 
goto loop 
 
goto :eof 