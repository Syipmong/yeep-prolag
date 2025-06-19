$ErrorActionPreference = 'Stop'

$packageName = 'yeep'

# Remove the shim
Uninstall-ChocolateyShim -Name "yeep"

Write-Host "Yeep Programming Language has been uninstalled." -ForegroundColor Green
