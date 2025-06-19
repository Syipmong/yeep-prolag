@echo off
echo Creating Manual Release Package...
echo.

REM Check if we have a built executable
if not exist "build\yeep.exe" (
    echo ERROR: build\yeep.exe not found!
    echo Please run build.bat first to create the executable.
    pause
    exit /b 1
)

REM Create release directory
if exist "release" rmdir /s /q release
mkdir release

echo Copying files to release directory...

REM Copy the executable to the root of release (not in build/ folder)
copy "build\yeep.exe" "release\yeep.exe" >nul

REM Copy other files
copy "install.bat" "release\" >nul
copy "README.md" "release\" >nul
if exist "LICENSE" copy "LICENSE" "release\" >nul
if exist "LANGUAGE_SPEC.md" copy "LANGUAGE_SPEC.md" "release\" >nul

REM Copy examples folder
if exist "examples" (
    xcopy "examples" "release\examples\" /e /i >nul
)

echo.
echo ✅ Release package created in 'release' folder
echo.
echo Contents:
dir /b release
echo.
echo To test installation:
echo 1. Copy contents of 'release' folder to a new directory
echo 2. Run install.bat from that directory
echo.
echo To create ZIP for distribution:
echo 1. Select all files in 'release' folder
echo 2. Right-click → Send to → Compressed folder
echo 3. Name it: yeep-windows-x64.zip
echo.
pause
