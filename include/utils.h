#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <cstdlib>

// Utility functions for the DSA program

inline void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

inline void pauseScreen() {
    std::cout << "\n\nPress Enter to continue...";
    std::cin.ignore();
    std::cin.get();
}

inline void printSeparator(int length = 60, char ch = '=') {
    std::cout << "  ";
    for(int i = 0; i < length; i++) {
        std::cout << ch;
    }
    std::cout << std::endl;
}

inline void printHeader(const std::string& title) {
    clearScreen();
    std::cout << "\n\n";
    printSeparator(70, '=');
    std::cout << "  " << title << std::endl;
    printSeparator(70, '=');
    std::cout << "\n";
}

// Visualization helper to show array state
inline void visualizeArray(int arr[], int size, int highlightIndex = -1) {
    std::cout << "\n  Array: [ ";
    for(int i = 0; i < size; i++) {
        if(i == highlightIndex) {
            std::cout << ">>>" << arr[i] << "<<< ";
        } else {
            std::cout << arr[i] << " ";
        }
    }
    std::cout << "]\n";
}

// Swap function for sorting algorithms
inline void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

#endif
