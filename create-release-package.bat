@echo off
echo ========================================
echo Creating Yeep v2.0.0 Release Package
echo ========================================

REM Clean and build
if exist "release" rmdir /s /q release
mkdir release
mkdir release\bin
mkdir release\docs
mkdir release\examples

REM Build the executable
call build_official.bat

REM Copy files to release directory
copy build\yeep.exe release\bin\
copy README.md release\
copy CHANGELOG.md release\
copy LICENSE release\
copy INSTALLATION.md release\
copy USER_GUIDE.md release\
copy GET_STARTED.md release\
copy demo_v2.yeep release\examples\

REM Create Windows installer
echo @echo off > release\install.bat
echo echo Installing Yeep Programming Language v2.0.0... >> release\install.bat
echo if not exist "%%USERPROFILE%%\bin" mkdir "%%USERPROFILE%%\bin" >> release\install.bat
echo copy bin\yeep.exe "%%USERPROFILE%%\bin\yeep.exe" >> release\install.bat
echo echo. >> release\install.bat
echo echo Yeep installed successfully! >> release\install.bat
echo echo Add %%USERPROFILE%%\bin to your PATH if not already done. >> release\install.bat
echo echo. >> release\install.bat
echo echo Quick start: >> release\install.bat
echo echo   yeep                # Interactive REPL >> release\install.bat
echo echo   yeep script.yeep    # Run a script >> release\install.bat
echo pause >> release\install.bat

REM Create usage instructions
echo # Yeep v2.0.0 - Windows Release Package > release\README_WINDOWS.md
echo. >> release\README_WINDOWS.md
echo ## Installation >> release\README_WINDOWS.md
echo 1. Run `install.bat` to install Yeep >> release\README_WINDOWS.md
echo 2. Add %%USERPROFILE%%\bin to your PATH if needed >> release\README_WINDOWS.md
echo 3. Open a new command prompt and run `yeep --version` >> release\README_WINDOWS.md
echo. >> release\README_WINDOWS.md
echo ## Quick Start >> release\README_WINDOWS.md
echo ```cmd >> release\README_WINDOWS.md
echo yeep                     # Start interactive REPL >> release\README_WINDOWS.md
echo yeep examples\demo_v2.yeep  # Run demo script >> release\README_WINDOWS.md
echo ``` >> release\README_WINDOWS.md

REM Create release archive
echo Creating release archive...
powershell Compress-Archive -Path release\* -DestinationPath yeep-v2.0.0-windows-manual.zip -Force

echo ========================================
echo Release package created: yeep-v2.0.0-windows-manual.zip
echo ========================================
echo.
echo Contents:
echo - yeep.exe (in bin\ folder)
echo - install.bat (automatic installer)
echo - Documentation and examples
echo - README_WINDOWS.md (Windows-specific instructions)
echo.
echo This package is ready for manual distribution!
pause
