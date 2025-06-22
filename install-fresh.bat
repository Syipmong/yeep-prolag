@echo off
setlocal enabledelayedexpansion

echo ================================================================
echo Yeep Programming Language - Complete Cleanup and Reinstall
echo ================================================================
echo.

echo 🧹 Cleaning up old Yeep installations...

REM Remove old yeep.exe from project directory if it exists
if exist "yeep.exe" (
    echo Removing old yeep.exe from project directory...
    del "yeep.exe" 2>nul
)

REM Check for existing installations
set FOUND_INSTALLS=0

if exist "%ProgramFiles%\Yeep" (
    echo Found system installation: %ProgramFiles%\Yeep
    set /a FOUND_INSTALLS+=1
    set SYSTEM_DIR=%ProgramFiles%\Yeep
)

if exist "%USERPROFILE%\Yeep" (
    echo Found user installation: %USERPROFILE%\Yeep
    set /a FOUND_INSTALLS+=1
    set USER_DIR=%USERPROFILE%\Yeep
)

if %FOUND_INSTALLS% gtr 0 (
    echo.
    echo Found existing installations. Cleaning up...
    
    REM Remove from PATH first
    echo Cleaning PATH entries...
    
    REM Clean user PATH
    for /f "skip=2 tokens=*" %%A in ('reg query "HKCU\Environment" /v PATH 2^>nul') do (
        set "USER_PATH=%%A"
        set "USER_PATH=!USER_PATH:*REG_SZ=!"
        set "USER_PATH=!USER_PATH:%ProgramFiles%\Yeep;=!"
        set "USER_PATH=!USER_PATH:;%ProgramFiles%\Yeep=!"
        set "USER_PATH=!USER_PATH:%USERPROFILE%\Yeep;=!"
        set "USER_PATH=!USER_PATH:;%USERPROFILE%\Yeep=!"
        set "USER_PATH=!USER_PATH:%CD%;=!"
        set "USER_PATH=!USER_PATH:;%CD%=!"
        reg add "HKCU\Environment" /v PATH /d "!USER_PATH!" /f >nul 2>&1
    )
    
    REM Remove directories
    if exist "%ProgramFiles%\Yeep" (
        echo Removing system directory...
        rmdir /s /q "%ProgramFiles%\Yeep" 2>nul
    )
    
    if exist "%USERPROFILE%\Yeep" (
        echo Removing user directory...
        rmdir /s /q "%USERPROFILE%\Yeep" 2>nul
    )
    
    echo ✅ Cleanup completed!
)

echo.
echo 🚀 Installing Yeep v2.0.2 fresh...
echo.

REM Now run the normal installation
call install.bat

echo.
echo 🎉 Fresh installation complete!
echo.
echo To use Yeep:
echo 1. Restart your command prompt/PowerShell
echo 2. Test: yeep --version
echo 3. Start REPL: yeep
echo.
pause
