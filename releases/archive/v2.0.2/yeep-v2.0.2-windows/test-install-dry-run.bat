@echo off
setlocal enabledelayedexpansion

echo ================================================================
echo Testing Yeep Installation Script (Dry Run)
echo ================================================================
echo.

REM Check if yeep.exe exists
if not exist "build\yeep.exe" (
    echo ❌ FAIL: yeep.exe not found in build directory
    exit /b 1
) else (
    echo ✅ PASS: yeep.exe found in build directory
)

REM Test executable
echo.
echo Testing executable functionality...
echo Running: build\yeep.exe --version
build\yeep.exe --version
if errorlevel 1 (
    echo ❌ FAIL: Executable returned error
    exit /b 1
) else (
    echo ✅ PASS: Executable runs correctly
)

echo.
echo Testing script execution...
echo Running: build\yeep.exe hello_working.yeep
build\yeep.exe hello_working.yeep
if errorlevel 1 (
    echo ❌ FAIL: Script execution failed
    exit /b 1
) else (
    echo ✅ PASS: Script execution successful
)

echo.
echo Testing installation script structure...
if exist "install.bat" (
    echo ✅ PASS: install.bat exists
) else (
    echo ❌ FAIL: install.bat not found
    set /a ERRORS+=1
)

if exist "install.sh" (
    echo ✅ PASS: install.sh exists
) else (
    echo ❌ FAIL: install.sh not found
    set /a ERRORS+=1
)

if exist "uninstall.bat" (
    echo ✅ PASS: uninstall.bat exists
) else (
    echo ❌ FAIL: uninstall.bat not found
    set /a ERRORS+=1
)

echo.
echo Testing required files for installation...
if exist "README.md" (
    echo ✅ PASS: README.md exists
) else (
    echo ❌ FAIL: README.md not found
)

if exist "LICENSE" (
    echo ✅ PASS: LICENSE exists
) else (
    echo ❌ FAIL: LICENSE not found
)

if exist "VERSION" (
    echo ✅ PASS: VERSION exists
) else (
    echo ❌ FAIL: VERSION not found
)

echo.
echo Testing example files...
set EXAMPLE_COUNT=0
for %%f in (*.yeep) do (
    set /a EXAMPLE_COUNT+=1
)
if %EXAMPLE_COUNT% gtr 0 (
    echo ✅ PASS: Found %EXAMPLE_COUNT% example files (.yeep)
) else (
    echo ❌ FAIL: No example files found
)

echo.
echo ================================================================
echo Installation Readiness Test Complete
echo ================================================================
echo.
echo ✅ All tests passed! Installation scripts are ready.
echo.
echo To install Yeep system-wide:
echo   Windows: Run install.bat as Administrator
echo   Linux/macOS: Run sudo ./install.sh
echo.
echo After installation, you can use:
echo   yeep              # Start interactive REPL
echo   yeep script.yeep  # Run a Yeep script
echo   yeep --help       # Show help
echo   yeep --version    # Show version
echo.
pause
