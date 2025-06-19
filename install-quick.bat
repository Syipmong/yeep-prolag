@echo off
setlocal

echo 🚀 Yeep Programming Language - Quick Installer for Windows
echo.

echo This script will download and install the latest version of Yeep.
echo.
pause

echo 📥 Please download Yeep manually:
echo.
echo 1. Go to: https://github.com/syipmong/yeep-prolag/releases/latest
echo 2. Download: yeep-windows-x64.zip
echo 3. Extract the ZIP file
echo 4. Run install.bat as administrator
echo.

echo 💡 Alternative: Use Windows Subsystem for Linux (WSL) for automatic install:
echo    curl -fsSL https://raw.githubusercontent.com/syipmong/yeep-prolag/main/install-quick.sh ^| bash
echo.

start https://github.com/syipmong/yeep-prolag/releases/latest

pause
