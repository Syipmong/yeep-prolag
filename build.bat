@echo off
echo Building Yeep Programming Language...

if not exist "build" mkdir build

gcc -Wall -Wextra -std=c99 -I include -o build\yeep.exe src\*.c

if %errorlevel% == 0 (
    echo Build successful! Executable created at build\yeep.exe
    echo.
    echo Usage:
    echo   build\yeep.exe                 - Start interactive shell
    echo   build\yeep.exe script.yeep     - Run a Yeep script file
    echo.
    echo Try running: build\yeep.exe examples\hello.yeep
) else (
    echo Build failed!
)
