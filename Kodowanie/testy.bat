@echo off
setlocal
cd /d "%~dp0"

where g++ >nul 2>&1
if errorlevel 1 (
    echo [BLAD] Nie znaleziono g++. Dodaj MinGW/MSYS2 do PATH.
    pause
    exit /b 1
)

if not exist "include\System_Hotelu.h" (
    echo [BLAD] Umiesc testy.cpp i testy.bat obok main.cpp, include\ i src\.
    pause
    exit /b 1
)

if /i "%~1"=="hotel" goto zwykly

echo [1/2] Kompilacja testow...
g++ -std=c++17 -Wall -Wextra -Iinclude testy.cpp src/*.cpp -o testy.exe
if errorlevel 1 (
    echo [BLAD] Kompilacja testow nie powiodla sie.
    pause
    exit /b 1
)

echo [2/2] Uruchamianie testow...
if /i "%~1"=="wszystkie" (
    testy.exe --all
) else if /i "%~1"=="menu" (
    testy.exe --menu
) else (
    testy.exe --demo
)
goto koniec

:zwykly
echo Kompilacja zwyklego programu...
g++ -std=c++17 -Wall -Wextra -Iinclude main.cpp src/*.cpp -o hotel.exe
if errorlevel 1 (
    echo [BLAD] Nie udalo sie zbudowac hotel.exe.
    pause
    exit /b 1
)
hotel.exe

:koniec
set "KOD=%errorlevel%"
echo.
if not "%KOD%"=="0" echo [UWAGA] Program zakonczyl sie kodem %KOD%.
pause
exit /b %KOD%
