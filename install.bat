@echo off
setlocal

echo Installing Yeep Programming Language...
echo.

REM Check if running as administrator
net session >nul 2>&1
if %errorLevel% == 0 (
    echo Running with administrator privileges.
) else (
    echo WARNING: Not running as administrator. Installation may fail.
    echo Please run as administrator for system-wide installation.
    echo.
)

REM Create installation directory
set INSTALL_DIR=%ProgramFiles%\Yeep
if not exist "%INSTALL_DIR%" (
    echo Creating installation directory: %INSTALL_DIR%
    mkdir "%INSTALL_DIR%" 2>nul
    if errorlevel 1 (
        echo Failed to create installation directory. Falling back to user directory.
        set INSTALL_DIR=%USERPROFILE%\Yeep
        mkdir "%INSTALL_DIR%" 2>nul
    )
)

REM Build the project if needed
if not exist "build\yeep.exe" (
    echo Building Yeep...
    call build.bat
    if errorlevel 1 (
        echo Build failed. Installation aborted.
        pause
        exit /b 1
    )
)

REM Copy files
echo Copying files to %INSTALL_DIR%...
copy "build\yeep.exe" "%INSTALL_DIR%\" >nul
copy "README.md" "%INSTALL_DIR%\" >nul
copy "LANGUAGE_SPEC.md" "%INSTALL_DIR%\" >nul

REM Copy examples
if not exist "%INSTALL_DIR%\examples" mkdir "%INSTALL_DIR%\examples"
copy "examples\*" "%INSTALL_DIR%\examples\" >nul

REM Create yeep.bat wrapper script in installation directory
echo Creating yeep command wrapper...
(
echo @echo off
echo "%INSTALL_DIR%\yeep.exe" %%*
) > "%INSTALL_DIR%\yeep.bat"

REM Add to PATH if possible
echo.
echo Adding Yeep to system PATH...
setx PATH "%PATH%;%INSTALL_DIR%" >nul 2>&1
if errorlevel 1 (
    echo Failed to add to system PATH automatically.
    echo Please manually add "%INSTALL_DIR%" to your PATH environment variable.
) else (
    echo Successfully added to PATH.
)

echo.
echo Installation completed!
echo Yeep is installed to: %INSTALL_DIR%
echo.
echo Usage:
echo   yeep                    - Start interactive shell
echo   yeep script.yeep        - Run a Yeep script
echo   yeep examples\hello.yeep - Run example
echo.
echo You may need to restart your command prompt for PATH changes to take effect.
pause
