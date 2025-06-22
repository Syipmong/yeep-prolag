@echo off
setlocal

echo ================================================================
echo Diagnosing Directory Creation Issues
echo ================================================================
echo.

REM Check admin status
net session >nul 2>&1
if %errorLevel% == 0 (
    echo [OK] Running with administrator privileges
) else (
    echo [WARNING] NOT running as administrator
)

echo.
echo Environment Variables:
echo ProgramFiles: %ProgramFiles%
echo USERPROFILE: %USERPROFILE%
echo.

REM Test Program Files creation
echo Testing Program Files directory creation...
set TEST_DIR=%ProgramFiles%\YeepTest
echo Attempting to create: %TEST_DIR%
mkdir "%TEST_DIR%" 2>nul
if errorlevel 1 (
    echo [ERROR] Failed to create Program Files test directory
    echo Error level: %errorlevel%
) else (
    echo [OK] Program Files test directory created
    rmdir "%TEST_DIR%" 2>nul
)

echo.
REM Test user directory creation
echo Testing user directory creation...
set USER_TEST_DIR=%USERPROFILE%\YeepTest
echo Attempting to create: %USER_TEST_DIR%
mkdir "%USER_TEST_DIR%" 2>nul
if errorlevel 1 (
    echo [ERROR] Failed to create user test directory
    echo Error level: %errorlevel%
) else (
    echo [OK] User test directory created
    rmdir "%USER_TEST_DIR%" 2>nul
)

echo.
REM Check if Yeep directory already exists
echo Checking existing Yeep directories...
if exist "%ProgramFiles%\Yeep" (
    echo [FOUND] %ProgramFiles%\Yeep already exists
    dir "%ProgramFiles%\Yeep" 2>nul
    echo.
)
if exist "%USERPROFILE%\Yeep" (
    echo [FOUND] %USERPROFILE%\Yeep already exists
    dir "%USERPROFILE%\Yeep" 2>nul
    echo.
)

echo.
echo Diagnosis complete.
pause
