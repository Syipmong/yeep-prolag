@echo off
setlocal

echo Testing Program Files installation...
echo.

REM Check if running as administrator
net session >nul 2>&1
if %errorLevel% == 0 (
    echo [OK] Running with administrator privileges.
) else (
    echo [WARNING] NOT running as administrator.
    echo This will likely cause permission errors.
)

echo.
set INSTALL_DIR=%ProgramFiles%\Yeep
echo Attempting to create: %INSTALL_DIR%

REM Try to create the directory
mkdir "%INSTALL_DIR%" 2>nul
if errorlevel 1 (
    echo [ERROR] Failed to create Program Files directory!
    echo This confirms permission issue.
    echo.
    echo Falling back to user directory...
    set INSTALL_DIR=%USERPROFILE%\Yeep
    mkdir "%INSTALL_DIR%" 2>nul
    echo [OK] Created user directory: %INSTALL_DIR%
) else (
    echo [OK] Successfully created Program Files directory
)

REM Test copy to actual target directory
if exist "build\yeep.exe" (
    echo.
    echo Testing copy to: %INSTALL_DIR%
    copy "build\yeep.exe" "%INSTALL_DIR%\yeep.exe"
    if errorlevel 1 (
        echo [ERROR] Copy to target directory failed!
    ) else (
        echo [OK] Copy to target directory successful!
        if exist "%INSTALL_DIR%\yeep.exe" (
            echo [OK] File verified in target directory
            dir "%INSTALL_DIR%\yeep.exe"
        )
    )
)

echo.
echo Check the directory: %INSTALL_DIR%
pause

REM Cleanup (only if not Program Files)
if not "%INSTALL_DIR%"=="%ProgramFiles%\Yeep" (
    rmdir /s /q "%INSTALL_DIR%"
)
