# Yeep Programming Language v2.0.0 - Windows PowerShell Installer
# Downloads, builds, and installs Yeep for Windows

param(
    [switch]$BuildFromSource,
    [switch]$Help
)

if ($Help) {
    Write-Host "Yeep Programming Language v2.0.0 Installer"
    Write-Host "Usage: .\install.ps1 [-BuildFromSource] [-Help]"
    Write-Host ""
    Write-Host "Options:"
    Write-Host "  -BuildFromSource    Build from source instead of downloading binary"
    Write-Host "  -Help              Show this help message"
    exit 0
}

Write-Host "🎉 Yeep Programming Language v2.0.0 Windows Installer" -ForegroundColor Green
Write-Host "======================================================" -ForegroundColor Green
Write-Host ""

# Check if running as administrator for system install
$isAdmin = ([Security.Principal.WindowsPrincipal] [Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole] "Administrator")

if (-not $isAdmin) {
    Write-Host "ℹ️  Running as user (not administrator)" -ForegroundColor Yellow
    Write-Host "   Will install to user directory: $env:USERPROFILE\bin" -ForegroundColor Yellow
    Write-Host ""
}

try {
    if ($BuildFromSource) {
        Write-Host "🔨 Building from source..." -ForegroundColor Cyan
        
        # Check for git
        if (-not (Get-Command git -ErrorAction SilentlyContinue)) {
            Write-Host "❌ Git not found. Please install Git for Windows." -ForegroundColor Red
            exit 1
        }
        
        # Check for g++
        if (-not (Get-Command g++ -ErrorAction SilentlyContinue)) {
            Write-Host "❌ g++ compiler not found!" -ForegroundColor Red
            Write-Host "Please install one of the following:" -ForegroundColor Red
            Write-Host "  1. MinGW-w64 via MSYS2: https://www.msys2.org/" -ForegroundColor Yellow
            Write-Host "  2. Visual Studio with C++ support" -ForegroundColor Yellow
            Write-Host "  3. Git Bash with MinGW" -ForegroundColor Yellow
            exit 1
        }
        
        # Clone and build
        $tempDir = New-TemporaryFile | ForEach-Object { Remove-Item $_; New-Item -ItemType Directory -Path $_ }
        Push-Location $tempDir
        
        Write-Host "📥 Cloning repository..." -ForegroundColor Cyan
        git clone https://github.com/Syipmong/yeep-prolag.git
        Set-Location yeep-prolag
        
        Write-Host "🔨 Building..." -ForegroundColor Cyan
        .\build_official.bat
        
        $executablePath = "build\yeep.exe"
        
    } else {
        Write-Host "📥 Downloading pre-built binary..." -ForegroundColor Cyan
        
        # Create temp directory
        $tempDir = New-TemporaryFile | ForEach-Object { Remove-Item $_; New-Item -ItemType Directory -Path $_ }
        Push-Location $tempDir
        
        # Download from GitHub releases
        $downloadUrl = "https://github.com/Syipmong/yeep-prolag/releases/latest/download/yeep-v2.0.0-windows.zip"
        
        try {
            Write-Host "Downloading from: $downloadUrl" -ForegroundColor Gray
            Invoke-WebRequest -Uri $downloadUrl -OutFile "yeep-v2.0.0-windows.zip"
            Expand-Archive "yeep-v2.0.0-windows.zip" -DestinationPath "."
            Set-Location "yeep-v2.0.0-windows"
            $executablePath = "yeep.exe"
        }
        catch {
            Write-Host "❌ Failed to download pre-built binary." -ForegroundColor Red
            Write-Host "Falling back to building from source..." -ForegroundColor Yellow
            
            # Fallback to source build
            Set-Location $tempDir
            git clone https://github.com/Syipmong/yeep-prolag.git
            Set-Location yeep-prolag
            .\build_official.bat
            $executablePath = "build\yeep.exe"
        }
    }
    
    # Verify executable exists
    if (-not (Test-Path $executablePath)) {
        Write-Host "❌ Build failed - executable not found!" -ForegroundColor Red
        exit 1
    }
    
    Write-Host "✅ Build successful!" -ForegroundColor Green
    Write-Host ""
    
    # Install
    Write-Host "📦 Installing Yeep..." -ForegroundColor Cyan
    
    # Create bin directory
    $binDir = "$env:USERPROFILE\bin"
    if (-not (Test-Path $binDir)) {
        New-Item -ItemType Directory -Path $binDir -Force | Out-Null
    }
    
    # Copy executable
    $installPath = "$binDir\yeep.exe"
    Copy-Item $executablePath $installPath -Force
    
    Write-Host "✅ Installed to: $installPath" -ForegroundColor Green
    
    # Add to PATH if needed
    $userPath = [Environment]::GetEnvironmentVariable("PATH", "User")
    if ($userPath -notlike "*$binDir*") {
        Write-Host "🔧 Adding to PATH..." -ForegroundColor Cyan
        [Environment]::SetEnvironmentVariable("PATH", "$userPath;$binDir", "User")
        $env:PATH += ";$binDir"  # Update current session
        Write-Host "✅ Added $binDir to user PATH" -ForegroundColor Green
    }
    
    # Cleanup
    Pop-Location
    Remove-Item $tempDir -Recurse -Force
    
    Write-Host ""
    Write-Host "🎉 Installation complete!" -ForegroundColor Green
    Write-Host "=========================" -ForegroundColor Green
    Write-Host ""
    Write-Host "🚀 Quick start:" -ForegroundColor Cyan
    Write-Host "  yeep                    # Interactive mode"
    Write-Host "  yeep script.yeep        # Run a script"
    Write-Host ""
    Write-Host "📝 Create your first script:" -ForegroundColor Cyan
    Write-Host '  echo print("Hello, Yeep!"); > hello.yeep'
    Write-Host "  yeep hello.yeep"
    Write-Host ""
    
    # Test installation
    Write-Host "🧪 Testing installation..." -ForegroundColor Cyan
    try {
        $testResult = echo 'print("Installation test successful! 🎉");' | & $installPath
        Write-Host $testResult -ForegroundColor Green
    }
    catch {
        Write-Host "⚠️  Test failed, but installation may still be successful." -ForegroundColor Yellow
        Write-Host "   Try running 'yeep' in a new PowerShell window." -ForegroundColor Yellow
    }
    
    Write-Host ""
    Write-Host "📚 Documentation: https://github.com/Syipmong/yeep-prolag/wiki" -ForegroundColor Cyan
    Write-Host ""
    Write-Host "Welcome to Yeep Programming Language! 🎊" -ForegroundColor Green
    
} catch {
    Write-Host "❌ Installation failed: $($_.Exception.Message)" -ForegroundColor Red
    Write-Host "Please check the requirements and try again." -ForegroundColor Red
    exit 1
}
