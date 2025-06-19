@echo off
setlocal

echo ================================================================
echo Installing Yeep Programming Language v1.0.6
echo ================================================================
echo.
echo [OK] This version includes fixes for Windows DLL dependencies
echo [OK] Self-contained executable - no MSYS2 or MinGW required
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
echo Creating installation directory: %INSTALL_DIR%
mkdir "%INSTALL_DIR%" 2>nul
if errorlevel 1 (
    echo [WARNING] Failed to create Program Files directory (permission denied)
    echo Falling back to user directory...
    set INSTALL_DIR=%USERPROFILE%\Yeep
    echo Creating user directory: %INSTALL_DIR%
    mkdir "%INSTALL_DIR%" 2>nul
    if errorlevel 1 (
        echo [ERROR] Failed to create user directory!
        echo Please check your permissions and try again.
        pause
        exit /b 1
    )
    echo [OK] User directory created successfully
) else (
    echo [OK] Installation directory created successfully
)

REM Check for pre-built executable
echo.
echo Checking for Yeep executable...
echo Current directory: %CD%
echo Looking for:
echo   - yeep.exe (release version)
echo   - build\yeep.exe (source build)
echo.

if exist "yeep.exe" (
    echo [OK] Found pre-built executable: yeep.exe
    set YEEP_EXE=yeep.exe
    goto :copy_files
)

if exist "build\yeep.exe" (
    echo [OK] Found built executable: build\yeep.exe
    set YEEP_EXE=build\yeep.exe
    goto :copy_files
)

echo [ERROR] No Yeep executable found!
echo.
echo Files in current directory:
dir /b
echo.
echo This usually means one of the following:
echo 1. You downloaded the source code instead of the release
echo 2. The CI build failed and no executable was created
echo 3. Files are missing from the release download
echo 4. The archive was not extracted completely
echo.
echo SOLUTIONS:
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

:copy_files
echo Using executable: %YEEP_EXE%

REM Copy files
echo.
echo Copying files to %INSTALL_DIR%...
echo [1/6] Copying main executable...
copy "%YEEP_EXE%" "%INSTALL_DIR%\yeep.exe"
if errorlevel 1 (
    echo [ERROR] Failed to copy main executable!
    echo Check permissions and disk space.
    pause
    exit /b 1
)
echo [OK] Main executable copied

echo [2/6] Copying documentation...
if exist "README.md" (
    copy "README.md" "%INSTALL_DIR%\" >nul
    echo [OK] README.md copied
)
if exist "USAGE.md" (
    copy "USAGE.md" "%INSTALL_DIR%\" >nul
    echo [OK] USAGE.md copied
)
if exist "LANGUAGE_SPEC.md" (
    copy "LANGUAGE_SPEC.md" "%INSTALL_DIR%\" >nul
    echo [OK] LANGUAGE_SPEC.md copied
)
if exist "LICENSE" (
    copy "LICENSE" "%INSTALL_DIR%\" >nul
    echo [OK] LICENSE copied
)

echo [3/6] Copying uninstaller...
if exist "uninstall.bat" (
    copy "uninstall.bat" "%INSTALL_DIR%\" >nul
    echo [OK] uninstall.bat copied
)

echo [4/6] Copying examples...
if not exist "%INSTALL_DIR%\examples" mkdir "%INSTALL_DIR%\examples"
if exist "examples\*" (
    copy "examples\*" "%INSTALL_DIR%\examples\" >nul
    echo [OK] Examples copied
)

echo [5/6] Creating command wrapper...
echo @echo off > "%INSTALL_DIR%\yeep.bat"
echo "%INSTALL_DIR%\yeep.exe" %%* >> "%INSTALL_DIR%\yeep.bat"
echo [OK] Command wrapper created

echo [6/6] Adding to system PATH...
setx PATH "%PATH%;%INSTALL_DIR%" >nul 2>&1
if errorlevel 1 (
    echo Failed to add to system PATH automatically.
    echo Please manually add "%INSTALL_DIR%" to your PATH environment variable.
) else (
    echo Successfully added to PATH.
)

echo.
echo ================================================================
echo [SUCCESS] Installation completed successfully!
echo ================================================================
echo.
echo Yeep is installed to: %INSTALL_DIR%
echo Added to system PATH for global access
echo.
echo Getting Started:
echo   yeep                    - Start interactive shell
echo   yeep script.yeep        - Run a Yeep script file
echo   yeep --help             - Show help information
echo   yeep --version          - Show version information
echo.
echo Learn More:
echo   yeep examples\hello.yeep - Run example program
echo   notepad "%INSTALL_DIR%\README.md"  - Read documentation
echo   notepad "%INSTALL_DIR%\USAGE.md"   - Detailed usage guide
echo.
echo To Uninstall:
echo   "%INSTALL_DIR%\uninstall.bat"      - Run uninstaller
echo.
echo NOTE: You may need to restart your command prompt for PATH changes to take effect.
echo.
echo Happy coding with Yeep!
pause
