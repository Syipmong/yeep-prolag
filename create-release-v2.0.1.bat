@echo off
echo ========================================
echo Creating Yeep v2.0.1 Release Package
echo ========================================

:: Create release directory
if exist release rmdir /s /q release
mkdir release
mkdir release\yeep-v2.0.1

:: Build the project first
echo [1/6] Building Yeep v2.0.1...
call build-v2.bat
if errorlevel 1 (
    echo Build failed! Aborting release.
    exit /b 1
)

:: Copy executable
echo [2/6] Copying executable...
copy build\yeep.exe release\yeep-v2.0.1\
if errorlevel 1 (
    echo Failed to copy executable!
    exit /b 1
)

:: Copy documentation
echo [3/6] Copying documentation...
copy README.md release\yeep-v2.0.1\
copy LANGUAGE_SPEC_V2.md release\yeep-v2.0.1\
copy USER_GUIDE.md release\yeep-v2.0.1\
copy INSTALLATION.md release\yeep-v2.0.1\
copy RELEASE-v2.0.1.md release\yeep-v2.0.1\README-RELEASE.md
copy VERSION release\yeep-v2.0.1\
copy LICENSE release\yeep-v2.0.1\

:: Copy example files
echo [4/6] Copying examples...
mkdir release\yeep-v2.0.1\examples
copy feature_showcase.yeep release\yeep-v2.0.1\examples\
copy calculator_example.yeep release\yeep-v2.0.1\examples\
copy test_arrays.yeep release\yeep-v2.0.1\examples\
copy test_functions.yeep release\yeep-v2.0.1\examples\
copy test_for_loops.yeep release\yeep-v2.0.1\examples\
copy test_simple.yeep release\yeep-v2.0.1\examples\

:: Copy source code (optional)
echo [5/6] Copying source code...
mkdir release\yeep-v2.0.1\src
mkdir release\yeep-v2.0.1\include
copy src\*.cpp release\yeep-v2.0.1\src\
copy include\*.hpp release\yeep-v2.0.1\include\
copy build-v2.bat release\yeep-v2.0.1\

:: Create ZIP package
echo [6/6] Creating ZIP package...
cd release
powershell -command "Compress-Archive -Path 'yeep-v2.0.1' -DestinationPath 'yeep-v2.0.1-windows.zip' -Force"
cd ..

echo ========================================
echo Release package created successfully!
echo ========================================
echo Package: release\yeep-v2.0.1-windows.zip
echo Directory: release\yeep-v2.0.1\
echo.
echo Contents:
echo   - yeep.exe (executable)
echo   - Documentation (README, guides, specs)
echo   - Examples (sample .yeep programs)
echo   - Source code (C++ implementation)
echo   - Build script (build-v2.bat)
echo.
echo Ready for distribution!
echo ========================================
pause
