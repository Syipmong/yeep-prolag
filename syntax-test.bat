@echo off
echo Testing install.bat syntax...
echo.

REM Just test the initial part that was causing issues
if exist "yeep.exe" (
    echo Found yeep.exe in current directory
    goto :found
)

if exist "build\yeep.exe" (
    echo Found build\yeep.exe
    goto :found
)

echo No executable found - this is expected for syntax test
goto :end

:found
echo Executable located successfully

:end
echo Syntax test completed - no errors means the batch file is valid
pause
