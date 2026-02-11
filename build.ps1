param()

# PowerShell build script: prefers cl.exe (MSVC) if available, otherwise tries g++
$src = "dungeongame/src/*.cpp"
$outdir = "build/bin"
if (!(Test-Path $outdir)) { New-Item -ItemType Directory -Path $outdir -Force | Out-Null }

if (Get-Command cl -ErrorAction SilentlyContinue) {
    Write-Host "Building with MSVC (cl.exe)..."
    cl /nologo /EHsc /std:c++17 /I dungeongame\include $src /Fe:$outdir\dungeongame.exe
} elseif (Get-Command g++ -ErrorAction SilentlyContinue) {
    Write-Host "Building with g++..."
    g++ -std=c++17 -I dungeongame\include dungeongame\src\*.cpp -o $outdir\dungeongame.exe
} else {
    Write-Error "No suitable compiler found. Install MSVC (cl.exe) or g++ and try again."
}

if ($LASTEXITCODE -eq 0) { Write-Host "Build succeeded. Run $outdir\dungeongame.exe" }
