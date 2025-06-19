@echo off
setlocal

echo ================================================================
echo DEBUG: Installing Yeep Programming Language
echo ================================================================
echo.
echo Current directory: %CD%
echo.
echo Files in this directory:
dir /b
echo.

REM Check if running as administrator
net session >nul 2>&1
if %errorLevel% == 0 (
    echo ✅ Running with administrator privileges.
) else (
    echo ⚠️  WARNING: Not running as administrator.
    echo Some installation steps may fail without admin privileges.
    echo.
)

echo.
echo Checking for Yeep executable...
if exist "yeep.exe" (
    echo ✅ Found: yeep.exe
) else (
    echo ❌ NOT FOUND: yeep.exe
)

if exist "install.bat" (
    echo ✅ Found: install.bat
) else (
    echo ❌ NOT FOUND: install.bat
)

if exist "examples" (
    echo ✅ Found: examples folder
) else (
    echo ❌ NOT FOUND: examples folder
)

echo.
echo Press any key to continue with installation or Ctrl+C to cancel...
pause >nul

REM Call the actual installer
call install.bat

echo.
echo Installation script completed.
echo Press any key to close this window...
pause >nul
