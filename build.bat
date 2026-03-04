@echo off
rem Generic Windows build script accepting environment variables or
rem command-line overrides for SRCDIR, APP, and INCDIR.
setlocal

if "%SRCDIR%"=="" set SRCDIR=dungeongame\src
if "%APP%"=="" set APP=dungeongame
if "%INCDIR%"=="" set INCDIR=dungeongame\include

if not exist build\bin mkdir build\bin

where cl >nul 2>&1
if %errorlevel%==0 (
    echo Building with MSVC (cl.exe)...
    cl /nologo /EHsc /std:c++17 /I %INCDIR% %SRCDIR%\*.cpp /Fe:build\bin\%APP%.exe
) else (
    where g++ >nul 2>&1
    if %errorlevel%==0 (
        echo Building with g++...
        g++ -std=c++17 -I %INCDIR% %SRCDIR%\*.cpp -o build\bin\%APP%.exe
    ) else (
        echo No suitable compiler found. Install MSVC (cl.exe) or g++.
        exit /b 1
    )
)

if %errorlevel% equ 0 (
    echo Build succeeded. Launching build\bin\%APP%.exe
    build\bin\%APP%.exe
) else (
    echo Build failed.
)
