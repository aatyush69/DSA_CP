/*
 * DSA FUNDAMENTALS - COMPREHENSIVE LEARNING PROGRAM
 * Course Project: Menu-Driven Data Structures & Algorithms Visualizer
 * 
 * This program demonstrates fundamental concepts of:
 * - Arrays, Searching & Sorting
 * - Stacks & Queues
 * - Linked Lists
 * - Trees (Binary Trees, BST, AVL)
 * - Graphs (BFS, DFS)
 * - Hashing
 */

#include <iostream>
#include <cstdlib>
#include "include/utils.h"
#include "include/arrays.h"
#include "include/linked_list.h"
#include "include/trees.h"
#include "include/graphs.h"
#include "include/hashing.h"

using namespace std;

void stackMenu();
void queueMenu();

void displayMainMenu() {
    clearScreen();
    cout << "\n╔════════════════════════════════════════════════════════════╗\n";
    cout << "║       DSA FUNDAMENTALS - INTERACTIVE LEARNING TOOL        ║\n";
    cout << "╚════════════════════════════════════════════════════════════╝\n";
    cout << "\n  MAIN MENU:\n";
    cout << "  ──────────────────────────────────────────────────────────\n";
    cout << "  1. Arrays, Searching & Sorting Algorithms\n";
    cout << "  2. Stacks - Operations & Applications\n";
    cout << "  3. Queues - Types & Operations\n";
    cout << "  4. Linked Lists - All Types\n";
    cout << "  5. Trees - Binary Trees, BST, AVL\n";
    cout << "  6. Graphs - BFS, DFS & Traversals\n";
    cout << "  7. Hashing - Hash Tables & Collision Resolution\n";
    cout << "  8. Algorithm Complexity Analysis\n";
    cout << "  0. Exit Program\n";
    cout << "  ──────────────────────────────────────────────────────────\n";
    cout << "  Enter your choice: ";
}

void complexityAnalysisMenu() {
    clearScreen();
    cout << "\n╔════════════════════════════════════════════════════════════╗\n";
    cout << "║           ALGORITHM COMPLEXITY ANALYSIS                   ║\n";
    cout << "╚════════════════════════════════════════════════════════════╝\n";
    
    cout << "\n📊 TIME COMPLEXITY COMPARISON:\n";
    cout << "  ═══════════════════════════════════════════════════════════\n";
    cout << "  SORTING ALGORITHMS:\n";
    cout << "  • Bubble Sort:    O(n²) - Best: O(n), Worst: O(n²)\n";
    cout << "  • Selection Sort: O(n²) - Best: O(n²), Worst: O(n²)\n";
    cout << "  • Insertion Sort: O(n²) - Best: O(n), Worst: O(n²)\n";
    cout << "  • Merge Sort:     O(n log n) - All cases\n";
    cout << "  • Quick Sort:     O(n log n) - Worst: O(n²)\n";
    cout << "\n  SEARCHING ALGORITHMS:\n";
    cout << "  • Linear Search:  O(n)\n";
    cout << "  • Binary Search:  O(log n) - Requires sorted array\n";
    cout << "\n  DATA STRUCTURE OPERATIONS:\n";
    cout << "  • Array Access:   O(1)\n";
    cout << "  • Stack Push/Pop: O(1)\n";
    cout << "  • Queue Enq/Deq:  O(1)\n";
    cout << "  • Linked List Insert/Delete: O(1) at head, O(n) at tail\n";
    cout << "  • BST Operations: O(log n) average, O(n) worst\n";
    cout << "  • AVL Operations: O(log n) - Guaranteed\n";
    cout << "  • Hash Table:     O(1) average, O(n) worst\n";
    cout << "\n  GRAPH TRAVERSALS:\n";
    cout << "  • BFS:            O(V + E) - V: vertices, E: edges\n";
    cout << "  • DFS:            O(V + E)\n";
    cout << "  ═══════════════════════════════════════════════════════════\n";
    
    cout << "\n📈 SPACE COMPLEXITY:\n";
    cout << "  • In-place algorithms: O(1) - Bubble, Selection, Insertion\n";
    cout << "  • Merge Sort: O(n) - Requires auxiliary space\n";
    cout << "  • Quick Sort: O(log n) - Recursive stack space\n";
    
    pauseScreen();
}

int main() {
    int choice;
    
    while(true) {
        displayMainMenu();
        cin >> choice;
        
        if(cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\n❌ Invalid input! Please enter a number.\n";
            pauseScreen();
            continue;
        }
        
        switch(choice) {
            case 1:
                arrayMenu();
                break;
            case 2:
                stackMenu();
                break;
            case 3:
                queueMenu();
                break;
            case 4:
                linkedListMenu();
                break;
            case 5:
                treeMenu();
                break;
            case 6:
                graphMenu();
                break;
            case 7:
                hashingMenu();
                break;
            case 8:
                complexityAnalysisMenu();
                break;
            case 0:
                cout << "\n✅ Thank you for using DSA Learning Tool!\n";
                cout << "   Keep practicing and learning! 🚀\n\n";
                return 0;
            default:
                cout << "\n❌ Invalid choice! Please select 0-8.\n";
                pauseScreen();
        }
    }
    
    return 0;
}



void stackMenu(){ std::cout<<"\n[Stack module temporarily unavailable]\n"; pauseScreen(); }
void queueMenu(){ std::cout<<"\n[Queue module temporarily unavailable]\n"; pauseScreen(); }

