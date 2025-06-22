@echo off
setlocal enabledelayedexpansion

REM ================================================================
REM Yeep Programming Language v2.0.4 - Release Package Creator
REM ================================================================

echo.
echo ╔══════════════════════════════════════════════════════════════╗
echo ║                🚀 Yeep v2.0.4 Release Builder               ║
echo ║                                                              ║
echo ║                Creating Production Release                   ║
echo ╚══════════════════════════════════════════════════════════════╝
echo.

REM Set version and build info
set VERSION=2.0.4
set RELEASE_DIR=releases\v%VERSION%
set PACKAGE_NAME=yeep-v%VERSION%-windows-x64
set BUILD_DATE=%DATE%
set BUILD_TIME=%TIME%

echo 🔧 Building Yeep v%VERSION% for Windows x64
echo 📁 Release directory: %RELEASE_DIR%
echo 📦 Package name: %PACKAGE_NAME%
echo.

REM Clean and create release directory
if exist "%RELEASE_DIR%" (
    echo 🧹 Cleaning existing release directory...
    rmdir /s /q "%RELEASE_DIR%"
)
mkdir "%RELEASE_DIR%"
mkdir "%RELEASE_DIR%\%PACKAGE_NAME%"

REM Build optimized release version
echo 🔨 Building optimized release version...
call build-release.bat
if errorlevel 1 (
    echo ❌ Build failed!
    pause
    exit /b 1
)

REM Copy main executable
echo 📋 Copying executable...
copy "build\yeep.exe" "%RELEASE_DIR%\%PACKAGE_NAME%\yeep.exe"
if errorlevel 1 (
    echo ❌ Failed to copy executable!
    pause
    exit /b 1
)

REM Copy installation scripts
echo 📋 Copying installation scripts...
copy "install.bat" "%RELEASE_DIR%\%PACKAGE_NAME%\install.bat"
copy "install-fresh.bat" "%RELEASE_DIR%\%PACKAGE_NAME%\install-fresh.bat"
copy "install.sh" "%RELEASE_DIR%\%PACKAGE_NAME%\install.sh"
copy "uninstall.bat" "%RELEASE_DIR%\%PACKAGE_NAME%\uninstall.bat"

REM Copy documentation
echo 📋 Copying documentation...
copy "README.md" "%RELEASE_DIR%\%PACKAGE_NAME%\README.md"
copy "LICENSE" "%RELEASE_DIR%\%PACKAGE_NAME%\LICENSE"
copy "VERSION" "%RELEASE_DIR%\%PACKAGE_NAME%\VERSION"
copy "INSTALLATION-GUIDE.md" "%RELEASE_DIR%\%PACKAGE_NAME%\INSTALLATION-GUIDE.md"
copy "RELEASE-NOTES-v%VERSION%.md" "%RELEASE_DIR%\%PACKAGE_NAME%\RELEASE-NOTES.md"
copy "USER_GUIDE.md" "%RELEASE_DIR%\%PACKAGE_NAME%\USER_GUIDE.md"

REM Create examples directory and copy example files
echo 📋 Copying examples...
mkdir "%RELEASE_DIR%\%PACKAGE_NAME%\examples"
copy "feature_showcase_v%VERSION%.yeep" "%RELEASE_DIR%\%PACKAGE_NAME%\examples\feature_showcase.yeep"
copy "test_simple.yeep" "%RELEASE_DIR%\%PACKAGE_NAME%\examples\test_simple.yeep"
copy "test_functions.yeep" "%RELEASE_DIR%\%PACKAGE_NAME%\examples\test_functions.yeep"
copy "test_for_loops.yeep" "%RELEASE_DIR%\%PACKAGE_NAME%\examples\test_for_loops.yeep"
copy "test_builtins.yeep" "%RELEASE_DIR%\%PACKAGE_NAME%\examples\test_builtins.yeep"
copy "calculator_example.yeep" "%RELEASE_DIR%\%PACKAGE_NAME%\examples\calculator_example.yeep"

REM Copy VSCode extension
echo 📋 Copying VSCode extension...
mkdir "%RELEASE_DIR%\%PACKAGE_NAME%\vscode-extension"
xcopy "vscode-extension\*" "%RELEASE_DIR%\%PACKAGE_NAME%\vscode-extension\" /s /e /q

REM Create build info file
echo 📋 Creating build info...
(
echo Yeep Programming Language v%VERSION%
echo Build Date: %BUILD_DATE%
echo Build Time: %BUILD_TIME%
echo Platform: Windows x64
echo Architecture: Modern C++17
echo Features: File I/O, System Integration, Enhanced REPL
echo Repository: https://github.com/Syipmong/yeep-prolag
echo.
echo Contents:
echo - yeep.exe - Main Yeep interpreter
echo - install.bat - Windows system installer
echo - install-fresh.bat - Clean Windows installer
echo - install.sh - Linux/macOS installer
echo - uninstall.bat - Windows uninstaller
echo - examples/ - Sample Yeep scripts
echo - vscode-extension/ - VSCode syntax highlighting
echo - Documentation and release notes
echo.
echo Installation:
echo 1. Extract this package
echo 2. Run install.bat as Administrator ^(Windows^)
echo 3. Or run install.sh with sudo ^(Linux/macOS^)
echo 4. Test with: yeep --version
echo.
echo New in v%VERSION%:
echo ✅ File I/O operations ^(readFile, writeFile, fileExists^)
echo ✅ System integration ^(env, now, exec^)
echo ✅ Enhanced REPL commands ^(vars, funcs, features^)
echo ✅ Production-ready stability and performance
) > "%RELEASE_DIR%\%PACKAGE_NAME%\BUILD_INFO.txt"

REM Create package ZIP file
echo 📦 Creating release package...
cd "%RELEASE_DIR%"
powershell -command "Compress-Archive -Path '%PACKAGE_NAME%' -DestinationPath '%PACKAGE_NAME%.zip' -Force"
cd ..\..

REM Create checksum
echo 🔐 Creating checksum...
cd "%RELEASE_DIR%"
powershell -command "$hash = Get-FileHash -Algorithm SHA256 '%PACKAGE_NAME%.zip'; $hash.Hash + '  %PACKAGE_NAME%.zip'" > "%PACKAGE_NAME%.zip.sha256"
cd ..\..

REM Display package info
echo.
echo ╔══════════════════════════════════════════════════════════════╗
echo ║                ✅ RELEASE PACKAGE CREATED!                  ║
echo ║                                                              ║
echo ║  Yeep v%VERSION% has been packaged successfully!             ║
echo ║                                                              ║
echo ║  📦 Package: %RELEASE_DIR%\%PACKAGE_NAME%.zip   ║
echo ║  🔐 Checksum: %PACKAGE_NAME%.zip.sha256           ║
echo ║                                                              ║
echo ║  📁 Package Contents:                                        ║
echo ║    • yeep.exe - Main interpreter                             ║
echo ║    • Installation scripts (Windows/Linux)                   ║
echo ║    • Complete documentation                                  ║
echo ║    • Example scripts and showcase                            ║
echo ║    • VSCode extension                                        ║
echo ║                                                              ║
echo ║  🚀 Ready for distribution!                                  ║
echo ╚══════════════════════════════════════════════════════════════╝
echo.

REM Show final instructions
echo 📋 Next Steps:
echo 1. Test the package by extracting and running install.bat
echo 2. Upload to GitHub releases
echo 3. Update documentation links
echo 4. Announce the release
echo.
echo 🎉 Yeep v%VERSION% release package is ready!
echo.
pause
