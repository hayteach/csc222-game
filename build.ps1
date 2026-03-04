param(
    [string]$SRCDIR = "dungeongame/src",
    [string]$APP = "dungeongame",
    [string]$INCDIR = "dungeongame/include",
    [switch]$Run
)

# PowerShell build script: prefers cl.exe (MSVC) if available, otherwise tries g++
# Parameters are passed in from build.py or can be supplied manually.
$src = "$SRCDIR/*.cpp"
$outdir = "build/bin"
if (!(Test-Path $outdir)) { New-Item -ItemType Directory -Path $outdir -Force | Out-Null }

if (Get-Command cl -ErrorAction SilentlyContinue) {
    Write-Host "Building with MSVC (cl.exe)..."
    cl /nologo /EHsc /std:c++17 /I $INCDIR $src /Fe:$outdir\$APP.exe
} elseif (Get-Command g++ -ErrorAction SilentlyContinue) {
    Write-Host "Building with g++..."
    g++ -std=c++17 -I $INCDIR $SRCDIR\*.cpp -o $outdir\$APP.exe
} else {
    Write-Error "No suitable compiler found. Install MSVC (cl.exe) or g++ and try again."
}

if ($LASTEXITCODE -eq 0) {
    Write-Host "Build succeeded."
    if ($Run) {
        Write-Host "Launching $outdir\$APP.exe"
        & "$outdir\$APP.exe"
    } else {
        Write-Host "Use -Run to execute the binary after building."
    }
}
