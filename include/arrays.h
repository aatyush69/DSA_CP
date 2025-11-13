#ifndef ARRAYS_H
#define ARRAYS_H

#include <iostream>
#include <iomanip>
#include "utils.h"

using namespace std;

// Forward declarations
void arrayMenu();
void demonstrateSearching();
void demonstrateSorting();
void demonstrateSparseMatrix();

// Searching Algorithms
int linearSearch(int arr[], int size, int key) {
    cout << "\n\n";
    cout << "  ** LINEAR SEARCH - Sequential Search **\n\n";
    printSeparator(70, '-');
    cout << "\n  Searching for: " << key << "\n\n";
    
    for(int i = 0; i < size; i++) {
        cout << "  Step " << (i+1) << ": Checking index " << i << " --> ";
        visualizeArray(arr, size, i);
        cout << "\n";
        
        if(arr[i] == key) {
            cout << "\n  ** FOUND at index " << i << "! **\n\n";
            printSeparator(70, '-');
            return i;
        }
    }
    cout << "\n  ** NOT FOUND! **\n\n";
    printSeparator(70, '-');
    return -1;
}

int binarySearch(int arr[], int size, int key) {
    cout << "\n\n";
    cout << "  ** BINARY SEARCH - Divide & Conquer **\n\n";
    printSeparator(70, '-');
    cout << "\n  Searching for: " << key << " (Array must be sorted)\n\n";
    
    int left = 0, right = size - 1;
    int step = 1;
    
    while(left <= right) {
        int mid = left + (right - left) / 2;
        
        cout << "  Step " << step++ << ": Left=" << left << ", Mid=" << mid << ", Right=" << right;
        cout << " --> arr[" << mid << "]=" << arr[mid] << "\n";
        
        if(arr[mid] == key) {
            cout << "\n  ** FOUND at index " << mid << "! **\n\n";
            printSeparator(70, '-');
            return mid;
        } else if(arr[mid] < key) {
            cout << "              " << key << " > " << arr[mid] << ", search RIGHT half\n\n";
            left = mid + 1;
        } else {
            cout << "              " << key << " < " << arr[mid] << ", search LEFT half\n\n";
            right = mid - 1;
        }
    }
    cout << "\n  ** NOT FOUND! **\n\n";
    printSeparator(70, '-');
    return -1;
}

// Sorting Algorithms
void bubbleSort(int arr[], int size) {
    cout << "\n🔄 BUBBLE SORT - Adjacent Element Comparison\n";
    printSeparator();
    cout << "  Initial: ";
    visualizeArray(arr, size);
    
    int swapCount = 0;
    for(int i = 0; i < size - 1; i++) {
        bool swapped = false;
        cout << "\n  Pass " << (i+1) << ":\n";
        
        for(int j = 0; j < size - i - 1; j++) {
            if(arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
                swapped = true;
                swapCount++;
                cout << "    Swap: arr[" << j << "] ↔ arr[" << (j+1) << "]";
                visualizeArray(arr, size);
            }
        }
        
        if(!swapped) {
            cout << "    No swaps needed! Array is sorted.\n";
            break;
        }
    }
    
    cout << "\n  ✅ Sorted: ";
    visualizeArray(arr, size);
    cout << "  Total swaps: " << swapCount << "\n";
    cout << "  Time Complexity: O(n²)\n";
}

void selectionSort(int arr[], int size) {
    cout << "\n🔄 SELECTION SORT - Select Minimum Element\n";
    printSeparator();
    cout << "  Initial: ";
    visualizeArray(arr, size);
    
    for(int i = 0; i < size - 1; i++) {
        int minIndex = i;
        cout << "\n  Pass " << (i+1) << ": Finding minimum from index " << i << "\n";
        
        for(int j = i + 1; j < size; j++) {
            if(arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        
        if(minIndex != i) {
            cout << "    Minimum: arr[" << minIndex << "]=" << arr[minIndex] << "\n";
            cout << "    Swap with arr[" << i << "]=" << arr[i] << "\n";
            swap(arr[i], arr[minIndex]);
            cout << "    After swap: ";
            visualizeArray(arr, size);
        }
    }
    
    cout << "\n  ✅ Sorted: ";
    visualizeArray(arr, size);
    cout << "  Time Complexity: O(n²)\n";
}

void insertionSort(int arr[], int size) {
    cout << "\n🔄 INSERTION SORT - Insert in Sorted Portion\n";
    printSeparator();
    cout << "  Initial: ";
    visualizeArray(arr, size);
    
    for(int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;
        
        cout << "\n  Step " << i << ": Insert " << key << " into sorted portion\n";
        
        while(j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
        
        cout << "    After insertion: ";
        visualizeArray(arr, size);
    }
    
    cout << "\n  ✅ Sorted: ";
    visualizeArray(arr, size);
    cout << "  Time Complexity: O(n²), Best Case: O(n)\n";
}

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    int* L = new int[n1];
    int* R = new int[n2];
    
    for(int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for(int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    
    while(i < n1 && j < n2) {
        if(L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    while(i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    while(j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    
    delete[] L;
    delete[] R;
}

void mergeSortHelper(int arr[], int left, int right, int& level) {
    if(left < right) {
        int mid = left + (right - left) / 2;
        
        mergeSortHelper(arr, left, mid, level);
        mergeSortHelper(arr, mid + 1, right, level);
        merge(arr, left, mid, right);
        
        cout << "  Level " << level++ << " merge: [" << left << " to " << right << "] → ";
        for(int i = left; i <= right; i++)
            cout << arr[i] << " ";
        cout << "\n";
    }
}

void mergeSort(int arr[], int size) {
    cout << "\n🔄 MERGE SORT - Divide & Conquer Strategy\n";
    printSeparator();
    cout << "  Initial: ";
    visualizeArray(arr, size);
    cout << "\n  Dividing and merging:\n";
    
    int level = 1;
    mergeSortHelper(arr, 0, size - 1, level);
    
    cout << "\n  ✅ Sorted: ";
    visualizeArray(arr, size);
    cout << "  Time Complexity: O(n log n)\n";
    cout << "  Space Complexity: O(n)\n";
}

int partition(int arr[], int low, int high, bool visualize = false) {
    int pivot = arr[high];
    int i = low - 1;
    
    if(visualize) {
        cout << "    Pivot: arr[" << high << "]=" << pivot << "\n";
    }
    
    for(int j = low; j < high; j++) {
        if(arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    
    return i + 1;
}

void quickSortHelper(int arr[], int low, int high, int& level) {
    if(low < high) {
        int pi = partition(arr, low, high, true);
        
        cout << "  Level " << level++ << " partition at index " << pi << ": ";
        for(int i = low; i <= high; i++)
            cout << arr[i] << " ";
        cout << "\n";
        
        quickSortHelper(arr, low, pi - 1, level);
        quickSortHelper(arr, pi + 1, high, level);
    }
}

void quickSort(int arr[], int size) {
    cout << "\n🔄 QUICK SORT - Pivot-based Partitioning\n";
    printSeparator();
    cout << "  Initial: ";
    visualizeArray(arr, size);
    cout << "\n  Partitioning steps:\n";
    
    int level = 1;
    quickSortHelper(arr, 0, size - 1, level);
    
    cout << "\n  ✅ Sorted: ";
    visualizeArray(arr, size);
    cout << "  Time Complexity: O(n log n) average, O(n²) worst\n";
}

// Sparse Matrix Operations
void demonstrateSparseMatrix() {
    printHeader("SPARSE MATRIX REPRESENTATION");
    
    int rows = 4, cols = 5;
    int matrix[4][5] = {
        {0, 0, 3, 0, 4},
        {0, 0, 5, 7, 0},
        {0, 0, 0, 0, 0},
        {0, 2, 6, 0, 0}
    };
    
    cout << "\n📊 Original Matrix (" << rows << "x" << cols << "):\n";
    for(int i = 0; i < rows; i++) {
        cout << "  ";
        for(int j = 0; j < cols; j++) {
            cout << setw(3) << matrix[i][j] << " ";
        }
        cout << "\n";
    }
    
    // Count non-zero elements
    int nonZeroCount = 0;
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            if(matrix[i][j] != 0)
                nonZeroCount++;
        }
    }
    
    // Create sparse matrix representation
    int sparseMatrix[nonZeroCount + 1][3];
    sparseMatrix[0][0] = rows;
    sparseMatrix[0][1] = cols;
    sparseMatrix[0][2] = nonZeroCount;
    
    int k = 1;
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            if(matrix[i][j] != 0) {
                sparseMatrix[k][0] = i;
                sparseMatrix[k][1] = j;
                sparseMatrix[k][2] = matrix[i][j];
                k++;
            }
        }
    }
    
    cout << "\n📋 Sparse Matrix (3-Tuple Format):\n";
    cout << "  Row  Col  Value\n";
    printSeparator(20);
    for(int i = 0; i <= nonZeroCount; i++) {
        cout << "  " << setw(3) << sparseMatrix[i][0] << "  " 
             << setw(3) << sparseMatrix[i][1] << "  " 
             << setw(5) << sparseMatrix[i][2] << "\n";
    }
    
    cout << "\n💾 Space Efficiency:\n";
    cout << "  Original: " << (rows * cols * sizeof(int)) << " bytes\n";
    cout << "  Sparse:   " << ((nonZeroCount + 1) * 3 * sizeof(int)) << " bytes\n";
    cout << "  Saved:    " << ((rows * cols - (nonZeroCount + 1) * 3) * sizeof(int)) << " bytes\n";
    
    // Transpose
    cout << "\n🔄 Simple Transpose:\n";
    int transpose[nonZeroCount + 1][3];
    transpose[0][0] = cols;
    transpose[0][1] = rows;
    transpose[0][2] = nonZeroCount;
    
    for(int i = 1; i <= nonZeroCount; i++) {
        transpose[i][0] = sparseMatrix[i][1];
        transpose[i][1] = sparseMatrix[i][0];
        transpose[i][2] = sparseMatrix[i][2];
    }
    
    cout << "  Row  Col  Value\n";
    printSeparator(20);
    for(int i = 0; i <= nonZeroCount; i++) {
        cout << "  " << setw(3) << transpose[i][0] << "  " 
             << setw(3) << transpose[i][1] << "  " 
             << setw(5) << transpose[i][2] << "\n";
    }
    
    pauseScreen();
}

void demonstrateSearching() {
    printHeader("SEARCHING ALGORITHMS DEMONSTRATION");
    
    int size;
    cout << "\n  >> Enter array size: ";
    cin >> size;
    
    int* arr = new int[size];
    cout << "  >> Enter " << size << " elements: ";
    for(int i = 0; i < size; i++) {
        cin >> arr[i];
    }
    
    int key;
    cout << "  >> Enter element to search: ";
    cin >> key;
    
    // Linear Search
    int* arrCopy = new int[size];
    for(int i = 0; i < size; i++) arrCopy[i] = arr[i];
    linearSearch(arrCopy, size, key);
    
    cout << "\n\n";
    printSeparator(70, '=');
    cout << "\n\n";
    
    // Binary Search (need sorted array)
    cout << "  For Binary Search, sorting the array first...\n\n";
    for(int i = 0; i < size - 1; i++) {
        for(int j = 0; j < size - i - 1; j++) {
            if(arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
            }
        }
    }
    
    cout << "  Sorted array: ";
    visualizeArray(arr, size);
    cout << "\n";
    binarySearch(arr, size, key);
    
    delete[] arr;
    delete[] arrCopy;
    pauseScreen();
}

void demonstrateSorting() {
    printHeader("SORTING ALGORITHMS COMPARISON");
    
    cout << "\nChoose sorting algorithm:\n";
    cout << "  1. Bubble Sort\n";
    cout << "  2. Selection Sort\n";
    cout << "  3. Insertion Sort\n";
    cout << "  4. Merge Sort\n";
    cout << "  5. Quick Sort\n";
    cout << "  6. Compare All (Same Input)\n";
    cout << "\nEnter choice: ";
    
    int choice;
    cin >> choice;
    
    int size;
    cout << "\n📥 Enter array size: ";
    cin >> size;
    
    int* arr = new int[size];
    cout << "Enter " << size << " elements: ";
    for(int i = 0; i < size; i++) {
        cin >> arr[i];
    }
    
    int* arrCopy = new int[size];
    for(int i = 0; i < size; i++) arrCopy[i] = arr[i];
    
    switch(choice) {
        case 1:
            bubbleSort(arr, size);
            break;
        case 2:
            selectionSort(arr, size);
            break;
        case 3:
            insertionSort(arr, size);
            break;
        case 4:
            mergeSort(arr, size);
            break;
        case 5:
            quickSort(arr, size);
            break;
        case 6:
            cout << "\n=== BUBBLE SORT ===";
            for(int i = 0; i < size; i++) arr[i] = arrCopy[i];
            bubbleSort(arr, size);
            
            cout << "\n\n=== SELECTION SORT ===";
            for(int i = 0; i < size; i++) arr[i] = arrCopy[i];
            selectionSort(arr, size);
            
            cout << "\n\n=== INSERTION SORT ===";
            for(int i = 0; i < size; i++) arr[i] = arrCopy[i];
            insertionSort(arr, size);
            
            cout << "\n\n=== MERGE SORT ===";
            for(int i = 0; i < size; i++) arr[i] = arrCopy[i];
            mergeSort(arr, size);
            
            cout << "\n\n=== QUICK SORT ===";
            for(int i = 0; i < size; i++) arr[i] = arrCopy[i];
            quickSort(arr, size);
            break;
        default:
            cout << "\n❌ Invalid choice!\n";
    }
    
    delete[] arr;
    delete[] arrCopy;
    pauseScreen();
}

void arrayMenu() {
    int choice;
    
    while(true) {
        printHeader("ARRAYS, SEARCHING & SORTING");
        cout << "\n  1. Searching Algorithms (Linear, Binary)\n";
        cout << "  2. Sorting Algorithms (All Types)\n";
        cout << "  3. Sparse Matrix Representation\n";
        cout << "  4. 2D Array Operations\n";
        cout << "  0. Back to Main Menu\n";
        printSeparator();
        cout << "  Enter choice: ";
        cin >> choice;
        
        switch(choice) {
            case 1:
                demonstrateSearching();
                break;
            case 2:
                demonstrateSorting();
                break;
            case 3:
                demonstrateSparseMatrix();
                break;
            case 4: {
                printHeader("2D ARRAY OPERATIONS");
                int rows, cols;
                cout << "\n📥 Enter rows and columns: ";
                cin >> rows >> cols;
                
                int** arr2d = new int*[rows];
                for(int i = 0; i < rows; i++)
                    arr2d[i] = new int[cols];
                
                cout << "Enter elements:\n";
                for(int i = 0; i < rows; i++) {
                    for(int j = 0; j < cols; j++) {
                        cout << "arr[" << i << "][" << j << "]: ";
                        cin >> arr2d[i][j];
                    }
                }
                
                cout << "\n📊 Your 2D Array:\n";
                for(int i = 0; i < rows; i++) {
                    cout << "  ";
                    for(int j = 0; j < cols; j++) {
                        cout << setw(4) << arr2d[i][j] << " ";
                    }
                    cout << "\n";
                }
                
                for(int i = 0; i < rows; i++)
                    delete[] arr2d[i];
                delete[] arr2d;
                
                pauseScreen();
                break;
            }
            case 0:
                return;
            default:
                cout << "\n❌ Invalid choice!\n";
                pauseScreen();
        }
    }
}

#endif
