# Yeep Programming Language v2.0.0 - One-Line Windows Installer
# Usage: iwr -useb https://raw.githubusercontent.com/Syipmong/yeep-prolag/main/install-one-line.ps1 | iex

$ErrorActionPreference = "Stop"

Write-Host "🎉 Installing Yeep Programming Language v2.0.0..." -ForegroundColor Green
Write-Host "=================================================" -ForegroundColor Green

try {
    # Detect architecture
    $Arch = $env:PROCESSOR_ARCHITECTURE
    if ($Arch -eq "AMD64") {
        $ArchSuffix = "x64"
    } elseif ($Arch -eq "ARM64") {
        $ArchSuffix = "arm64"
    } else {
        Write-Host "❌ Unsupported architecture: $Arch" -ForegroundColor Red
        exit 1
    }

    # Download URL
    $ReleaseUrl = "https://github.com/Syipmong/yeep-prolag/releases/latest/download"
    $Archive = "yeep-v2.0.0-windows.zip"
    $DownloadUrl = "$ReleaseUrl/$Archive"

    # Create temporary directory
    $TempDir = [System.IO.Path]::GetTempPath() + [System.Guid]::NewGuid().ToString()
    New-Item -ItemType Directory -Path $TempDir | Out-Null
    Set-Location $TempDir

    Write-Host "📥 Downloading Yeep v2.0.0 for Windows..." -ForegroundColor Cyan

    # Download archive
    try {
        Invoke-WebRequest -Uri $DownloadUrl -OutFile $Archive -UseBasicParsing
    } catch {
        Write-Host "❌ Failed to download: $_" -ForegroundColor Red
        exit 1
    }

    Write-Host "📦 Extracting archive..." -ForegroundColor Cyan
    Expand-Archive -Path $Archive -DestinationPath . -Force

    # Find extracted directory
    $ExtractDir = Get-ChildItem -Directory -Name "yeep-v2.0.0-*" | Select-Object -First 1
    if (-not $ExtractDir) {
        Write-Host "❌ Failed to find extracted directory" -ForegroundColor Red
        exit 1
    }

    Set-Location $ExtractDir

    Write-Host "🔧 Installing Yeep..." -ForegroundColor Cyan

    # Determine install location
    $IsAdmin = ([Security.Principal.WindowsPrincipal] [Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole] "Administrator")
    
    if ($IsAdmin) {
        # System install
        $InstallDir = "$env:ProgramFiles\Yeep"
        $BinPath = "$InstallDir\yeep.exe"
        
        if (-not (Test-Path $InstallDir)) {
            New-Item -ItemType Directory -Path $InstallDir -Force | Out-Null
        }
        
        Copy-Item "yeep.exe" $BinPath -Force
        
        # Add to system PATH
        $CurrentPath = [Environment]::GetEnvironmentVariable("PATH", "Machine")
        if ($CurrentPath -notlike "*$InstallDir*") {
            [Environment]::SetEnvironmentVariable("PATH", "$CurrentPath;$InstallDir", "Machine")
            Write-Host "📝 Added $InstallDir to system PATH" -ForegroundColor Yellow
        }
        
        Write-Host "✅ Yeep installed to $BinPath" -ForegroundColor Green
        
    } else {
        # User install
        $InstallDir = "$env:USERPROFILE\bin"
        $BinPath = "$InstallDir\yeep.exe"
        
        if (-not (Test-Path $InstallDir)) {
            New-Item -ItemType Directory -Path $InstallDir -Force | Out-Null
        }
        
        Copy-Item "yeep.exe" $BinPath -Force
        
        # Add to user PATH
        $CurrentPath = [Environment]::GetEnvironmentVariable("PATH", "User")
        if ($CurrentPath -notlike "*$InstallDir*") {
            [Environment]::SetEnvironmentVariable("PATH", "$CurrentPath;$InstallDir", "User")
            Write-Host "📝 Added $InstallDir to user PATH" -ForegroundColor Yellow
        }
        
        Write-Host "✅ Yeep installed to $BinPath" -ForegroundColor Green
    }

    # Cleanup
    Set-Location $env:TEMP
    Remove-Item $TempDir -Recurse -Force

    Write-Host ""
    Write-Host "🎊 Installation complete!" -ForegroundColor Green
    Write-Host ""
    Write-Host "📖 Quick start:" -ForegroundColor White
    Write-Host "   yeep                 # Start interactive REPL" -ForegroundColor Gray
    Write-Host "   yeep script.yeep     # Run a script file" -ForegroundColor Gray
    Write-Host ""
    Write-Host "🔗 Documentation: " -NoNewline -ForegroundColor White
    Write-Host "https://github.com/Syipmong/yeep-prolag" -ForegroundColor Blue
    Write-Host "💬 Issues: " -NoNewline -ForegroundColor White
    Write-Host "https://github.com/Syipmong/yeep-prolag/issues" -ForegroundColor Blue
    Write-Host ""

    # Refresh PATH for current session
    $env:PATH = [Environment]::GetEnvironmentVariable("PATH", "User") + ";" + [Environment]::GetEnvironmentVariable("PATH", "Machine")

    # Test installation
    try {
        $TestResult = & yeep --help 2>&1
        Write-Host "✅ Installation verified - 'yeep' command is available!" -ForegroundColor Green
        
        Write-Host ""
        Write-Host "🧪 Testing with a simple script..." -ForegroundColor Cyan
        $TestScript = 'print("Hello from Yeep v2.0.0!");'
        $TestScript | & yeep
        
    } catch {
        Write-Host "⚠️  'yeep' command not found in current session" -ForegroundColor Yellow
        Write-Host "💡 Please restart your terminal or PowerShell session" -ForegroundColor Yellow
    }

} catch {
    Write-Host "❌ Installation failed: $_" -ForegroundColor Red
    exit 1
}
