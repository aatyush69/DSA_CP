#!/bin/bash
# DSA Course Project - Linux/Mac Compilation Script

echo "========================================"
echo "DSA Fundamentals - Compilation Script"
echo "========================================"
echo ""

echo "Compiling the program..."
g++ -o dsa_program main.cpp -I./include

if [ $? -eq 0 ]; then
    echo ""
    echo "========================================"
    echo "Compilation Successful!"
    echo "========================================"
    echo ""
    echo "Run the program using: ./dsa_program"
    echo ""
    
    # Ask if user wants to run the program
    read -p "Do you want to run the program now? (y/n): " run
    if [ "$run" = "y" ] || [ "$run" = "Y" ]; then
        echo ""
        echo "Starting DSA Learning Program..."
        echo ""
        ./dsa_program
    fi
else
    echo ""
    echo "========================================"
    echo "Compilation Failed!"
    echo "========================================"
    echo "Please check for errors above."
    echo "Make sure g++ is installed."
fi

echo ""
