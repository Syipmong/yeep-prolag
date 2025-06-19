@echo off
setlocal

echo ================================================================
echo Installing Yeep Programming Language v1.0.0
echo ================================================================
echo.
echo ✅ This version includes fixes for Windows DLL dependencies
echo ✅ Self-contained executable - no MSYS2 or MinGW required
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

REM Check for pre-built executable (from release download)
echo.
echo Checking for Yeep executable...
echo Current directory: %CD%
echo Looking for:
echo   - yeep.exe (release version)
echo   - build\yeep.exe (source build)
echo.

if exist "yeep.exe" (
    echo ✅ Found pre-built executable: yeep.exe
    set YEEP_EXE=yeep.exe
) else if exist "build\yeep.exe" (
    echo ✅ Found built executable: build\yeep.exe
    set YEEP_EXE=build\yeep.exe
) else (
    echo ❌ No Yeep executable found!
    echo.
    echo Files in current directory:
    dir /b
    echo.
    echo This usually means one of the following:
    echo 1. You downloaded the source code instead of the release
    echo 2. The CI build failed and no executable was created
    echo 3. Files are missing from the release download
    echo 4. The archive wasn't extracted completely
    echo.
    echo 🔧 Solutions:
    echo.
    echo A) Download Pre-built Release:
    echo    1. Go to: https://github.com/Syipmong/yeep-prolag/releases/latest
    echo    2. Download: yeep-windows-x64.zip
    echo    3. Extract ALL files to a folder
    echo    4. Verify yeep.exe exists in the folder
    echo    5. Run install.bat from that folder
    echo.
    echo B) Build from Source:
    echo    1. Install MSYS2 or MinGW-w64
    echo    2. Run: build.bat
    echo    3. Then run: install.bat
    echo.
    echo C) Check Release Status:
    echo    - The CI might have failed for the latest release
    echo    - Try downloading an older working release
    echo.
    pause
    exit /b 1
)

echo Using executable: %YEEP_EXE%

REM Copy files
echo Copying files to %INSTALL_DIR%...
copy "%YEEP_EXE%" "%INSTALL_DIR%\yeep.exe" >nul
if exist "README.md" copy "README.md" "%INSTALL_DIR%\" >nul
if exist "LANGUAGE_SPEC.md" copy "LANGUAGE_SPEC.md" "%INSTALL_DIR%\" >nul
if exist "LICENSE" copy "LICENSE" "%INSTALL_DIR%\" >nul

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
