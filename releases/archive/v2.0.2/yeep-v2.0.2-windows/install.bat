@echo off
setlocal enabledelayedexpansion

REM ================================================================
REM Yeep Programming Language v2.0.1 - System-Wide Installation
REM ================================================================

echo.
echo ╔══════════════════════════════════════════════════════════════╗
echo ║                🎯 Yeep Programming Language v2.0.1          ║
echo ║                                                              ║
echo ║                  System-Wide Installation                    ║
echo ╚══════════════════════════════════════════════════════════════╝
echo.

REM Check if yeep.exe exists
if not exist "build\yeep.exe" (
    echo ❌ Error: yeep.exe not found in build directory
    echo Please run build.bat first to compile Yeep
    echo.
    pause
    exit /b 1
)

REM Check for administrator privileges
net session >nul 2>&1
if %errorLevel% == 0 (
    echo ✅ Running with administrator privileges
    set INSTALL_TYPE=system
    set INSTALL_DIR=%ProgramFiles%\Yeep
    set PATH_DIR=%ProgramFiles%\Yeep
) else (
    echo ⚠️  Not running as administrator
    echo Installing to user directory instead
    set INSTALL_TYPE=user
    set INSTALL_DIR=%USERPROFILE%\Yeep
    set PATH_DIR=%USERPROFILE%\Yeep
)

echo.
echo 📁 Installation Directory: !INSTALL_DIR!
echo 🔧 Installation Type: !INSTALL_TYPE!
echo.

REM Create installation directory
if not exist "!INSTALL_DIR!" (
    echo 📂 Creating installation directory...
    mkdir "!INSTALL_DIR!" 2>nul
    if errorlevel 1 (
        echo ❌ Failed to create installation directory
        echo Please run as administrator for system-wide installation
        pause
        exit /b 1
    )
)

REM Copy executable
echo 📋 Copying yeep.exe...
copy "build\yeep.exe" "!INSTALL_DIR!\yeep.exe" >nul
if errorlevel 1 (
    echo ❌ Failed to copy yeep.exe
    pause
    exit /b 1
)

REM Copy documentation files
echo 📋 Copying documentation...
if exist "README.md" copy "README.md" "!INSTALL_DIR!\README.md" >nul
if exist "LICENSE" copy "LICENSE" "!INSTALL_DIR!\LICENSE" >nul
if exist "VERSION" copy "VERSION" "!INSTALL_DIR!\VERSION" >nul
if exist "RELEASE-v2.0.1.md" copy "RELEASE-v2.0.1.md" "!INSTALL_DIR!\RELEASE-NOTES.md" >nul

REM Copy example files
echo 📋 Copying examples...
if not exist "!INSTALL_DIR!\examples" mkdir "!INSTALL_DIR!\examples"
for %%f in (*.yeep) do (
    if exist "%%f" copy "%%f" "!INSTALL_DIR!\examples\%%f" >nul
)

REM Create uninstall script
echo 📋 Creating uninstall script...
(
echo @echo off
echo echo Uninstalling Yeep Programming Language...
echo.
echo REM Remove from PATH
echo for /f "skip=2 tokens=*" %%%%A in ^('reg query "HKCU\Environment" /v PATH 2^>nul'^) do set "USER_PATH=%%%%A"
echo if defined USER_PATH ^(
echo     set "USER_PATH=!USER_PATH:*REG_SZ=!"
echo     set "USER_PATH=!USER_PATH:;!PATH_DIR!=!"
echo     set "USER_PATH=!USER_PATH:!PATH_DIR!;=!"
echo     reg add "HKCU\Environment" /v PATH /d "!USER_PATH!" /f ^>nul
echo ^)
echo.
echo REM Remove installation directory
echo echo Removing installation directory...
echo rmdir /s /q "!INSTALL_DIR!"
echo.
echo echo ✅ Yeep has been uninstalled successfully
echo pause
) > "!INSTALL_DIR!\uninstall.bat"

REM Add to PATH
echo 🔧 Adding to system PATH...

if "!INSTALL_TYPE!"=="system" (
    REM System-wide PATH (requires admin)
    for /f "skip=2 tokens=*" %%A in ('reg query "HKLM\SYSTEM\CurrentControlSet\Control\Session Manager\Environment" /v PATH 2>nul') do set "SYSTEM_PATH=%%A"
    if defined SYSTEM_PATH (
        set "SYSTEM_PATH=!SYSTEM_PATH:*REG_EXPAND_SZ=!"
        echo !SYSTEM_PATH! | findstr /i "!PATH_DIR!" >nul
        if errorlevel 1 (
            reg add "HKLM\SYSTEM\CurrentControlSet\Control\Session Manager\Environment" /v PATH /d "!SYSTEM_PATH!;!PATH_DIR!" /f >nul
            echo ✅ Added to system PATH
        ) else (
            echo ℹ️  Already in system PATH
        )
    )
) else (
    REM User-specific PATH
    for /f "skip=2 tokens=*" %%A in ('reg query "HKCU\Environment" /v PATH 2>nul') do set "USER_PATH=%%A"
    if defined USER_PATH (
        set "USER_PATH=!USER_PATH:*REG_SZ=!"
        echo !USER_PATH! | findstr /i "!PATH_DIR!" >nul
        if errorlevel 1 (
            reg add "HKCU\Environment" /v PATH /d "!USER_PATH!;!PATH_DIR!" /f >nul
            echo ✅ Added to user PATH
        ) else (
            echo ℹ️  Already in user PATH
        )
    ) else (
        reg add "HKCU\Environment" /v PATH /d "!PATH_DIR!" /f >nul
        echo ✅ Added to user PATH
    )
)

echo.
echo ╔══════════════════════════════════════════════════════════════╗
echo ║                 ✅ INSTALLATION COMPLETE!                   ║
echo ║                                                              ║
echo ║  Yeep v2.0.1 has been installed successfully!               ║
echo ║                                                              ║
echo ║  📁 Location: !INSTALL_DIR!              ║
echo ║                                                              ║
echo ║  🚀 Usage:                                                   ║
echo ║     yeep              # Start interactive REPL              ║
echo ║     yeep script.yeep  # Run a Yeep script                   ║
echo ║     yeep --help       # Show help                           ║
echo ║     yeep --version    # Show version                        ║
echo ║                                                              ║
echo ║  📚 Examples: !INSTALL_DIR!\examples\*.yeep    ║
echo ║                                                              ║
echo ║  🗑️  Uninstall: Run !INSTALL_DIR!\uninstall.bat ║
echo ╚══════════════════════════════════════════════════════════════╝
echo.
echo ⚠️  Important: Please restart your command prompt or terminal
echo    to use the 'yeep' command from anywhere!
echo.
echo 🎉 Ready to code in Yeep! Try: yeep --help
echo.
pause
