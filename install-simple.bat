@echo off
setlocal

echo ================================================================
echo Installing Yeep Programming Language v1.0.5
echo ================================================================
echo.

REM Check if running as administrator
net session >nul 2>&1
if %errorLevel% == 0 (
    echo Running with administrator privileges.
) else (
    echo WARNING: Not running as administrator.
    echo Please run as administrator for system-wide installation.
    echo.
)

REM Create installation directory
set INSTALL_DIR=%ProgramFiles%\Yeep
if not exist "%INSTALL_DIR%" (
    echo Creating installation directory: %INSTALL_DIR%
    mkdir "%INSTALL_DIR%" 2>nul
    if errorlevel 1 (
        echo Failed to create installation directory. Using user directory.
        set INSTALL_DIR=%USERPROFILE%\Yeep
        mkdir "%INSTALL_DIR%" 2>nul
    )
)

REM Check for executable
echo.
echo Checking for Yeep executable...
if exist "yeep.exe" (
    echo Found: yeep.exe
    set YEEP_EXE=yeep.exe
) else if exist "build\yeep.exe" (
    echo Found: build\yeep.exe  
    set YEEP_EXE=build\yeep.exe
) else (
    echo ERROR: No Yeep executable found!
    echo.
    echo Make sure you have extracted all files from the ZIP archive
    echo and that yeep.exe exists in this directory.
    echo.
    pause
    exit /b 1
)

REM Copy files
echo.
echo Copying files to installation directory...
copy "%YEEP_EXE%" "%INSTALL_DIR%\yeep.exe" >nul
if exist "README.md" copy "README.md" "%INSTALL_DIR%\" >nul
if exist "USAGE.md" copy "USAGE.md" "%INSTALL_DIR%\" >nul
if exist "LICENSE" copy "LICENSE" "%INSTALL_DIR%\" >nul
if exist "uninstall.bat" copy "uninstall.bat" "%INSTALL_DIR%\" >nul

REM Copy examples
if exist "examples" (
    if not exist "%INSTALL_DIR%\examples" mkdir "%INSTALL_DIR%\examples"
    copy "examples\*" "%INSTALL_DIR%\examples\" >nul
)

REM Create command wrapper
echo Creating global yeep command...
(
echo @echo off
echo "%INSTALL_DIR%\yeep.exe" %%*
) > "%INSTALL_DIR%\yeep.bat"

REM Add to PATH
echo.
echo Adding to system PATH...
setx PATH "%PATH%;%INSTALL_DIR%" >nul 2>&1
if errorlevel 1 (
    echo Failed to add to PATH automatically.
    echo Please add "%INSTALL_DIR%" to your PATH manually.
) else (
    echo Successfully added to PATH.
)

echo.
echo ================================================================
echo Installation completed successfully!
echo ================================================================
echo.
echo Yeep is installed to: %INSTALL_DIR%
echo.
echo To use Yeep:
echo   yeep                 - Start interactive shell
echo   yeep script.yeep     - Run a script file
echo   yeep --help          - Show help
echo   yeep --version       - Show version
echo.
echo NOTE: Restart your command prompt for PATH changes to take effect.
echo.
pause
