@echo off
rem Simple Windows build script using g++ (MinGW/MSYS or MSVC's g++)





)  echo Build failed.) else (  echo Build succeeded. Run build\bin\dungeongame.exenif not exist build\bin mkdir build\bin
ng++ -std=c++17 -I dungeongame\include dungeongame\src\*.cpp -o build\bin\dungeongame.exe
nif %errorlevel% equ 0 (