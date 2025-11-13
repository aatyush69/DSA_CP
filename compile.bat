@echo off
REM DSA Course Project - Windows Compilation Script

echo ========================================
echo DSA Fundamentals - Compilation Script
echo ========================================
echo.

echo Compiling the program...
g++ -o dsa_program main.cpp -I./include

if %ERRORLEVEL% EQU 0 (
    echo.
    echo ========================================
    echo Compilation Successful!
    echo ========================================
    echo.
    echo Run the program using: dsa_program.exe
    echo.
    
    REM Ask if user wants to run the program
    set /p run="Do you want to run the program now? (Y/N): "
    if /i "%run%"=="Y" (
        echo.
        echo Starting DSA Learning Program...
        echo.
        dsa_program.exe
    )
) else (
    echo.
    echo ========================================
    echo Compilation Failed!
    echo ========================================
    echo Please check for errors above.
    echo Make sure g++ is installed and in PATH.
)

echo.
pause
