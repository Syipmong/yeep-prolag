@echo off
setlocal

REM Yeep Release Build Script for Windows
REM Creates distribution packages

echo Building Yeep for Windows distribution...

REM Read version
set /p VERSION=<VERSION
echo Building Yeep v%VERSION%...

REM Clean previous builds
echo Cleaning previous builds...
if exist build rmdir /s /q build
if exist dist rmdir /s /q dist

REM Create distribution directory
mkdir dist

echo Building Yeep...
call build.bat

REM Test the build
echo Testing build...
echo print("Build test successful!"); | build\yeep.exe

REM Create Windows package
echo Creating Windows package...
mkdir dist\yeep-windows-x64
copy build\yeep.exe dist\yeep-windows-x64\
copy install.bat dist\yeep-windows-x64\
copy README.md dist\yeep-windows-x64\
copy LICENSE dist\yeep-windows-x64\
xcopy examples dist\yeep-windows-x64\examples\ /E /I

REM Create ZIP archive (requires PowerShell)
powershell -Command "Compress-Archive -Path 'dist\yeep-windows-x64\*' -DestinationPath 'dist\yeep-windows-x64.zip'"

echo Distribution package created: dist\yeep-windows-x64.zip
echo.
echo Upload this file to GitHub Releases for distribution.

pause
