@echo off
setlocal enabledelayedexpansion

REM ================================================================
REM Yeep Programming Language v2.0.1 - Complete Release Builder
REM ================================================================

echo.
echo ╔══════════════════════════════════════════════════════════════╗
echo ║            🚀 Yeep v2.0.1 Release Package Builder           ║
echo ║                                                              ║
echo ║              Creating Production-Ready Release               ║
echo ╚══════════════════════════════════════════════════════════════╝
echo.

REM Clean previous release
if exist "release" (
    echo 🧹 Cleaning previous release...
    rmdir /s /q "release" 2>nul
)

REM Create release structure
echo 📁 Creating release directories...
mkdir "release"
mkdir "release\yeep-v2.0.1-windows"
mkdir "release\yeep-v2.0.1-windows\examples"
mkdir "release\yeep-v2.0.1-windows\src"
mkdir "release\yeep-v2.0.1-windows\include"
mkdir "release\yeep-v2.0.1-windows\vscode-extension"

REM Build the project
echo.
echo 🔨 Building Yeep v2.0.1...
call build.bat
if errorlevel 1 (
    echo ❌ Build failed! Cannot create release.
    pause
    exit /b 1
)
echo ✅ Build successful!

REM Copy main executable
echo.
echo 📋 Copying executable and core files...
copy "build\yeep.exe" "release\yeep-v2.0.1-windows\" >nul
if errorlevel 1 (
    echo ❌ Failed to copy executable!
    pause
    exit /b 1
)

REM Copy installation scripts
echo 📋 Copying installation system...
copy "install.bat" "release\yeep-v2.0.1-windows\" >nul
copy "install.sh" "release\yeep-v2.0.1-windows\" >nul
copy "uninstall.bat" "release\yeep-v2.0.1-windows\" >nul
copy "build.bat" "release\yeep-v2.0.1-windows\" >nul
copy "build.sh" "release\yeep-v2.0.1-windows\" >nul

REM Copy documentation
echo 📋 Copying documentation...
copy "README.md" "release\yeep-v2.0.1-windows\" >nul
copy "INSTALLATION.md" "release\yeep-v2.0.1-windows\" >nul
copy "LANGUAGE_SPEC_V2.md" "release\yeep-v2.0.1-windows\LANGUAGE_SPEC.md" >nul
copy "USER_GUIDE.md" "release\yeep-v2.0.1-windows\" >nul
copy "USAGE.md" "release\yeep-v2.0.1-windows\" >nul
copy "RELEASE-v2.0.1.md" "release\yeep-v2.0.1-windows\RELEASE-NOTES.md" >nul
copy "BUILD-CLEANUP-SUMMARY.md" "release\yeep-v2.0.1-windows\" >nul
copy "SYSTEM-INSTALL-COMPLETE.md" "release\yeep-v2.0.1-windows\" >nul
copy "VERSION" "release\yeep-v2.0.1-windows\" >nul
copy "LICENSE" "release\yeep-v2.0.1-windows\" >nul
copy "CHANGELOG.md" "release\yeep-v2.0.1-windows\" >nul

REM Copy all example files
echo 📋 Copying example programs...
for %%f in (*.yeep) do (
    if exist "%%f" (
        copy "%%f" "release\yeep-v2.0.1-windows\examples\" >nul
    )
)

REM Copy source code
echo 📋 Copying source code...
copy "src\*.cpp" "release\yeep-v2.0.1-windows\src\" >nul
copy "include\*.hpp" "release\yeep-v2.0.1-windows\include\" >nul

REM Copy VSCode extension
echo 📋 Copying VSCode extension...
if exist "vscode-extension\yeep-language-2.0.2.vsix" (
    copy "vscode-extension\yeep-language-2.0.2.vsix" "release\yeep-v2.0.1-windows\vscode-extension\" >nul
)
if exist "vscode-extension\README.md" (
    copy "vscode-extension\README.md" "release\yeep-v2.0.1-windows\vscode-extension\" >nul
)

REM Copy test and utility scripts
echo 📋 Copying utilities...
copy "test-install-dry-run.bat" "release\yeep-v2.0.1-windows\" >nul
copy "test-install-unix.sh" "release\yeep-v2.0.1-windows\" >nul
copy "diagnose.bat" "release\yeep-v2.0.1-windows\" >nul

REM Create quick start guide
echo 📋 Creating quick start guide...
(
echo # Yeep v2.0.1 - Quick Start Guide
echo.
echo ## Installation
echo.
echo ### Windows
echo 1. Extract this ZIP file
echo 2. Right-click Command Prompt and select "Run as administrator"
echo 3. Navigate to the extracted folder
echo 4. Run: `install.bat`
echo 5. Restart your command prompt
echo 6. Test: `yeep --version`
echo.
echo ### Linux/macOS
echo 1. Extract this archive
echo 2. Open terminal in the extracted folder
echo 3. Run: `chmod +x install.sh build.sh`
echo 4. Run: `sudo ./install.sh`
echo 5. Restart your terminal
echo 6. Test: `yeep --version`
echo.
echo ## Usage
echo.
echo ```bash
echo # Start interactive REPL
echo yeep
echo.
echo # Run a script
echo yeep examples/hello_working.yeep
echo.
echo # Show help
echo yeep --help
echo.
echo # Show version
echo yeep --version
echo ```
echo.
echo ## Examples
echo.
echo Try these example programs:
echo - `examples/hello_working.yeep` - Basic hello world
echo - `examples/calculator_example.yeep` - Calculator with functions
echo - `examples/test_functions.yeep` - Function definitions and calls
echo - `examples/test_arrays.yeep` - Array operations
echo - `examples/test_for_loops.yeep` - Loop constructs
echo.
echo ## VSCode Extension
echo.
echo Install the VSCode extension for syntax highlighting:
echo 1. Open VS Code
echo 2. Go to Extensions tab
echo 3. Click "Install from VSIX..."
echo 4. Select `vscode-extension/yeep-language-2.0.2.vsix`
echo.
echo ## Support
echo.
echo - GitHub: https://github.com/Syipmong/yeep-prolag
echo - Documentation: See INSTALLATION.md and USER_GUIDE.md
echo - Issues: https://github.com/Syipmong/yeep-prolag/issues
echo.
echo Happy coding with Yeep! 🎉
) > "release\yeep-v2.0.1-windows\QUICK-START.md"

REM Create Windows ZIP package
echo.
echo 📦 Creating Windows release package...
cd release
powershell -command "Compress-Archive -Path 'yeep-v2.0.1-windows' -DestinationPath 'yeep-v2.0.1-windows-x64.zip' -Force"
cd ..

REM Create checksums
echo 📋 Creating checksums...
cd release
powershell -command "Get-FileHash 'yeep-v2.0.1-windows-x64.zip' -Algorithm SHA256 | Select-Object Hash | Format-Table -HideTableHeaders" > yeep-v2.0.1-windows-x64.zip.sha256
cd ..

REM Calculate package info
for %%f in ("release\yeep-v2.0.1-windows-x64.zip") do set "PACKAGE_SIZE=%%~zf"
set /a PACKAGE_SIZE_MB=!PACKAGE_SIZE! / 1024 / 1024

echo.
echo ╔══════════════════════════════════════════════════════════════╗
echo ║                🎉 RELEASE PACKAGE COMPLETE!                 ║
echo ║                                                              ║
echo ║  📦 Package: yeep-v2.0.1-windows-x64.zip                    ║
echo ║  📁 Directory: release\yeep-v2.0.1-windows\                 ║
echo ║  💾 Size: ~!PACKAGE_SIZE_MB! MB                                         ║
echo ║                                                              ║
echo ║  ✅ Includes:                                                ║
echo ║     • yeep.exe (main executable)                            ║
echo ║     • install.bat / install.sh (installers)                 ║
echo ║     • Complete documentation                                 ║
echo ║     • Example programs (*.yeep)                             ║
echo ║     • Source code (C++)                                     ║
echo ║     • VSCode extension (.vsix)                              ║
echo ║     • Build scripts                                         ║
echo ║     • Test utilities                                        ║
echo ║                                                              ║
echo ║  🚀 Ready for GitHub Release!                               ║
echo ╚══════════════════════════════════════════════════════════════╝
echo.
echo 📋 Package Contents Summary:
echo   📁 release\
echo   ├── 📦 yeep-v2.0.1-windows-x64.zip
echo   ├── 🔐 yeep-v2.0.1-windows-x64.zip.sha256
echo   └── 📁 yeep-v2.0.1-windows\
echo       ├── 🚀 yeep.exe
echo       ├── ⚡ install.bat
echo       ├── ⚡ install.sh  
echo       ├── 📖 README.md
echo       ├── 📖 INSTALLATION.md
echo       ├── 📖 QUICK-START.md
echo       ├── 📁 examples\ (29 .yeep files)
echo       ├── 📁 src\ (C++ source)
echo       ├── 📁 include\ (C++ headers)
echo       └── 📁 vscode-extension\
echo.
echo 🎯 Next Steps:
echo   1. Test the package: extract and run install.bat
echo   2. Upload to GitHub Releases
echo   3. Update documentation links
echo   4. Announce the release!
echo.
pause
