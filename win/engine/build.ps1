# Builds treelevel-engine.exe, the C++ engine the C# host runs for Pythia and the passthrough.
#
#   .\build.ps1                      # for this machine's architecture, into win\engine\build\<arch>\Release
#   .\build.ps1 -Arch x64 -Prefix <folder>
#
# Copyright (C) 2026 Guglielmo Pasa. GNU General Public License v3 or later.

[CmdletBinding()]
param(
    [ValidateSet('x64', 'arm64')] [string]$Arch,
    [string]$Prefix,
    [switch]$Clean
)

$ErrorActionPreference = 'Stop'
$root = $PSScriptRoot

function Fail($message) { Write-Host $message -ForegroundColor Red; exit 1 }

# The machine architecture, not the one of the PowerShell that is running.
if (-not $Arch) {
    $machine = (Get-ItemProperty 'HKLM:\SYSTEM\CurrentControlSet\Control\Session Manager\Environment').PROCESSOR_ARCHITECTURE
    $Arch = if ($machine -eq 'ARM64') { 'arm64' } else { 'x64' }
}
$platform = if ($Arch -eq 'arm64') { 'ARM64' } else { 'x64' }

# CMake: the PATH first, then the one Visual Studio installs.
$cmake = (Get-Command cmake -ErrorAction SilentlyContinue).Source
$vswhere = Join-Path ${env:ProgramFiles(x86)} 'Microsoft Visual Studio\Installer\vswhere.exe'
$vsVersion = $null
if (Test-Path $vswhere) {
    $vsPath = & $vswhere -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath
    $vsVersion = & $vswhere -latest -products * -property installationVersion
    if (-not $cmake -and $vsPath) {
        $bundled = Join-Path $vsPath 'Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe'
        if (Test-Path $bundled) { $cmake = $bundled }
    }
}
if (-not $cmake) { Fail 'CMake not found — install it, or install the "Desktop development with C++" workload of Visual Studio.' }

$generator = switch (($vsVersion -split '\.')[0]) {
    '18' { 'Visual Studio 18 2026' }
    '17' { 'Visual Studio 17 2022' }
    '16' { 'Visual Studio 16 2019' }
    default { $null }
}
if (-not $generator) { Fail 'Visual Studio 2019 or later is needed to build the engine.' }

$build = Join-Path $root "build\$Arch"
if ($Clean -and (Test-Path $build)) { Remove-Item $build -Recurse -Force }

& $cmake -S $root -B $build -G $generator -A $platform | Out-Null
if ($LASTEXITCODE -ne 0) { Fail 'cmake configuration failed' }
# MSB8064/8065 are MSBuild comparing paths by case on a shared drive (Parallels): noise, not a fault.
& $cmake --build $build --config Release --parallel | Where-Object { $_ -notmatch 'MSB806[45]' }
if ($LASTEXITCODE -ne 0) { Fail 'compilation failed' }

$engine = Join-Path $build 'Release\treelevel-engine.exe'
if (-not (Test-Path $engine)) { Fail "the engine was not produced ($engine)" }
Write-Host ("built     " + (& $engine version)) -ForegroundColor Green

if ($Prefix) {
    & $cmake --install $build --config Release --prefix $Prefix
    if ($LASTEXITCODE -ne 0) { Fail 'installation failed' }
    Write-Host "installed $Prefix" -ForegroundColor Green
}
