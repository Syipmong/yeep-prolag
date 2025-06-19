@echo off
setlocal

echo Testing installation process...
echo.

REM Create test installation directory
set INSTALL_DIR=%USERPROFILE%\YeepTest
echo Creating test directory: %INSTALL_DIR%
if exist "%INSTALL_DIR%" rmdir /s /q "%INSTALL_DIR%"
mkdir "%INSTALL_DIR%"

REM Test file detection
echo.
echo Testing file detection:
if exist "yeep.exe" (
    echo [OK] Found yeep.exe in current directory
    set YEEP_EXE=yeep.exe
) else if exist "build\yeep.exe" (
    echo [OK] Found build\yeep.exe
    set YEEP_EXE=build\yeep.exe
) else (
    echo [ERROR] No executable found
    pause
    exit /b 1
)

echo Using executable: %YEEP_EXE%

REM Test copy operation
echo.
echo Testing copy operation:
echo Copying %YEEP_EXE% to %INSTALL_DIR%\yeep.exe
copy "%YEEP_EXE%" "%INSTALL_DIR%\yeep.exe"
if errorlevel 1 (
    echo [ERROR] Copy failed!
) else (
    echo [OK] Copy successful
)

REM Test if file exists after copy
if exist "%INSTALL_DIR%\yeep.exe" (
    echo [OK] File exists in destination
    dir "%INSTALL_DIR%\yeep.exe"
) else (
    echo [ERROR] File NOT found in destination
)

echo.
echo Test completed. Check %INSTALL_DIR% for results.
pause

REM Cleanup
rmdir /s /q "%INSTALL_DIR%"
