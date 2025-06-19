@echo off 
echo Installing Yeep Programming Language v2.0.0... 
if not exist "%USERPROFILE%\bin" mkdir "%USERPROFILE%\bin" 
copy bin\yeep.exe "%USERPROFILE%\bin\yeep.exe" 
echo. 
echo Yeep installed successfully! 
echo Add %USERPROFILE%\bin to your PATH if not already done. 
echo. 
echo Quick start: 
echo   yeep                # Interactive REPL 
echo   yeep script.yeep    # Run a script 
pause 
