@echo off

echo CYBERDINE SYSTEMS (JSWARE DIVISION)
echo WESTINGHOUSE M95A1 PHASED PLASMA RIFLE
echo 40W RANGE WEAPON LOADING PROGRAM...
echo.

if "%1" == "" GOTO errNoDrive

FOR /F "tokens=*" %%F IN ('dir /b /o:n T*.WAV') DO (
  echo COPYING %%F TO %1\%%F ...
  copy %%F %1\%%F
)

goto :eof

:errNoDrive
echo ERROR: INCORRECT USAGE (%0 {DRIVE LETTER})
goto :eof
