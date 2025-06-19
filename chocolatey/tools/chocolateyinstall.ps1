$ErrorActionPreference = 'Stop'

$packageName = 'yeep'
$toolsDir = "$(Split-Path -parent $MyInvocation.MyCommand.Definition)"
$url = 'https://github.com/Syipmong/yeep-prolag/releases/download/v2.0.0/yeep-v2.0.0-windows.zip'

$packageArgs = @{
  packageName   = $packageName
  unzipLocation = $toolsDir
  url           = $url
  checksum      = 'PLACEHOLDER_CHECKSUM'  # This will be updated when creating the actual release
  checksumType  = 'sha256'
}

Install-ChocolateyZipPackage @packageArgs

# Create shim for the executable
$yeepExe = Get-ChildItem $toolsDir -Recurse -Name "yeep.exe" | Select-Object -First 1
if ($yeepExe) {
    $yeepPath = Join-Path $toolsDir $yeepExe
    Install-ChocolateyShim -Name "yeep" -Path $yeepPath
}
