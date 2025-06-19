@echo off
setlocal

echo ================================================================
echo Uninstalling Yeep Programming Language
echo ================================================================
echo.

REM Check if running as administrator
net session >nul 2>&1
if %errorLevel% == 0 (
    echo Running with administrator privileges.
) else (
    echo WARNING: Not running as administrator.
    echo Some uninstallation steps may fail without admin privileges.
    echo.
)

REM Check common installation directories
set INSTALL_DIR_SYSTEM=%ProgramFiles%\Yeep
set INSTALL_DIR_USER=%USERPROFILE%\Yeep

echo Looking for Yeep installations...

if exist "%INSTALL_DIR_SYSTEM%" (
    echo Found system installation: %INSTALL_DIR_SYSTEM%
    set FOUND_SYSTEM=1
) else (
    set FOUND_SYSTEM=0
)

if exist "%INSTALL_DIR_USER%" (
    echo Found user installation: %INSTALL_DIR_USER%
    set FOUND_USER=1
) else (
    set FOUND_USER=0
)

if %FOUND_SYSTEM%==0 if %FOUND_USER%==0 (
    echo No Yeep installations found in standard locations.
    echo.
    echo If you installed Yeep to a custom location, please:
    echo 1. Delete the installation folder manually
    echo 2. Remove the folder from your PATH environment variable
    echo 3. Restart your command prompt
    echo.
    pause
    exit /b 0
)

echo.
echo The following will be removed:

if %FOUND_SYSTEM%==1 (
    echo - System installation: %INSTALL_DIR_SYSTEM%
)

if %FOUND_USER%==1 (
    echo - User installation: %INSTALL_DIR_USER%
)

echo - Yeep from system PATH
echo.

set /p CONFIRM=Are you sure you want to uninstall Yeep? (y/N): 
if /i not "%CONFIRM%"=="y" (
    echo Uninstallation cancelled.
    pause
    exit /b 0
)

echo.
echo Uninstalling Yeep...

REM Remove system installation
if %FOUND_SYSTEM%==1 (
    echo Removing system installation...
    rmdir /s /q "%INSTALL_DIR_SYSTEM%" 2>nul
    if errorlevel 1 (
        echo Failed to remove system installation. Try running as administrator.
    ) else (
        echo System installation removed successfully.
    )
)

REM Remove user installation
if %FOUND_USER%==1 (
    echo Removing user installation...
    rmdir /s /q "%INSTALL_DIR_USER%" 2>nul
    if errorlevel 1 (
        echo Failed to remove user installation.
    ) else (
        echo User installation removed successfully.
    )
)

REM Remove from PATH (this is complex, so we'll provide instructions)
echo.
echo ⚠️  PATH Cleanup Required:
echo.
echo The installation directory may still be in your PATH environment variable.
echo To remove it:
echo.
echo 1. Open System Properties (Win+R → sysdm.cpl)
echo 2. Click "Environment Variables"
echo 3. Find "PATH" in System Variables
echo 4. Edit and remove any entries containing "Yeep"
echo 5. Click OK to save
echo.
echo OR use PowerShell (as administrator):
if %FOUND_SYSTEM%==1 (
    echo   [Environment]::SetEnvironmentVariable("PATH", [Environment]::GetEnvironmentVariable("PATH", "Machine").Replace(";%INSTALL_DIR_SYSTEM%", ""), "Machine"^)
)
if %FOUND_USER%==1 (
    echo   [Environment]::SetEnvironmentVariable("PATH", [Environment]::GetEnvironmentVariable("PATH", "User").Replace(";%INSTALL_DIR_USER%", ""), "User"^)
)

echo.
echo ✅ Yeep uninstallation completed!
echo.
echo You may need to restart your command prompt or computer
echo for PATH changes to take effect.
echo.
pause
