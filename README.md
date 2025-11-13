# DSA FUNDAMENTALS - COMPREHENSIVE LEARNING PROGRAM
## Course Project: Interactive Data Structures & Algorithms Visualizer

### 📚 Project Overview
This is a complete menu-driven C++ program designed to help students learn and visualize fundamental Data Structures and Algorithms concepts. It covers the entire DSA syllabus with interactive demonstrations and visualizations.

### ✨ Features

#### 1. **Arrays, Searching & Sorting**
- Linear Search and Binary Search with step-by-step visualization
- Sorting Algorithms:
  - Bubble Sort
  - Selection Sort
  - Insertion Sort
  - Merge Sort
  - Quick Sort
- Sparse Matrix representation and operations
- 2D Array operations
- Time complexity analysis for each algorithm

#### 2. **Stacks**
- Stack operations (Push, Pop, Peek)
- Visual representation of stack with pointer locations
- Expression conversion (Infix to Postfix)
- Postfix expression evaluation
- Recursion demonstration using stack
- Applications in real-world problems

#### 3. **Queues**
- Simple Queue (FIFO)
- Circular Queue (Ring Buffer)
- Priority Queue
- Deque (Double-Ended Queue)
- Visual representation of all queue types
- Real-world applications

#### 4. **Linked Lists**
- Singly Linked List with all operations
- Doubly Linked List with bidirectional traversal
- Circular Linked List
- Polynomial operations using linked lists
- Memory address visualization
- Comparison of all list types

#### 5. **Trees**
- Binary Tree with all traversals (Inorder, Preorder, Postorder, Level-order)
- Binary Search Tree (BST) with insert, search, delete
- AVL Tree with automatic balancing and rotation visualization
- Min Heap with heapify operations
- Expression Tree demonstration
- Tree property calculations (height, node count)

#### 6. **Graphs**
- Graph representation using Adjacency Matrix
- Graph representation using Adjacency List
- BFS (Breadth-First Search) with step-by-step visualization
- DFS (Depth-First Search) - both recursive and iterative
- Graph properties and connectivity checking
- Real-world applications (Social networks, GPS, etc.)

#### 7. **Hashing**
- Hash Table with Chaining (Linked List)
- Hash Table with Linear Probing
- Hash Table with Quadratic Probing
- Hash Table with Double Hashing
- Collision visualization and resolution
- Load factor calculation
- Performance comparison

#### 8. **Algorithm Complexity Analysis**
- Big-O notation for all algorithms
- Time complexity comparison
- Space complexity analysis
- Best, Average, and Worst case scenarios

### 🗂️ Project Structure
```
DSA_CP/
│
├── main.cpp                 # Main program entry point
│
├── include/
│   ├── utils.h             # Utility functions (screen handling, etc.)
│   ├── arrays.h            # Arrays, searching, and sorting
│   ├── stack_queue.h       # Stack and Queue implementations
│   ├── linked_list.h       # All types of linked lists
│   ├── trees.h             # Binary Trees, BST, AVL, Heap
│   ├── graphs.h            # Graph implementations and traversals
│   └── hashing.h           # Hash tables and collision resolution
│
├── compile.bat             # Windows compilation script
├── compile.sh              # Linux/Mac compilation script
└── README.md               # This file
```

### 🚀 How to Compile and Run

#### **Windows (PowerShell or Command Prompt):**
```powershell
# Compile the program
g++ -o dsa_program main.cpp -I./include

# Run the program
./dsa_program
```

Or use the batch file:
```powershell
./compile.bat
```

#### **Linux/Mac:**
```bash
# Compile the program
g++ -o dsa_program main.cpp -I./include

# Run the program
./dsa_program
```

Or use the shell script:
```bash
chmod +x compile.sh
./compile.sh
```

### 📋 Prerequisites
- C++ compiler (g++/MinGW recommended)
- Basic understanding of C++ programming
- Command line interface (Terminal/PowerShell)

### 🎓 Learning Path
1. Start with **Arrays and Sorting** to understand basic algorithms
2. Move to **Stacks and Queues** to learn linear data structures
3. Progress to **Linked Lists** for dynamic memory management
4. Study **Trees** for hierarchical data organization
5. Explore **Graphs** for complex relationships
6. Learn **Hashing** for efficient data retrieval
7. Review **Complexity Analysis** to understand performance

### 📖 Syllabus Coverage

#### Section 1: Introduction to Data Structures and Complexity ✅
- Abstract Data Types
- Classification of data structures
- Big-O, Big-Ω, Big-Θ notations
- Time-space trade-off
- Recursion basics and applications

#### Section 2: Arrays and Searching & Sorting Techniques ✅
- 1D and 2D arrays
- Sparse matrix representation
- Linear search, Binary search
- Bubble, Selection, Insertion, Merge, Quick sort
- Time complexity analysis

#### Section 3: Stacks and Queues ✅
- Stack operations and applications
- Expression evaluation
- Infix to postfix conversion
- Recursion using stack
- Queue operations (Circular, Priority, Deque)

#### Section 4: Linked Lists ✅
- Singly, Doubly, Circular linked lists
- All operations (insert, delete, traverse, search)
- Polynomial operations
- Memory management

#### Section 5: Trees ✅
- Binary trees, BST, AVL trees
- Tree traversals
- Expression trees, Heap trees
- Applications

#### Section 6: Graphs and Hashing ✅
- Graph representation (Adjacency list/matrix)
- BFS, DFS
- Hash tables
- Collision resolution techniques

### 🎯 Key Features for Learning
- **Interactive**: Menu-driven interface for hands-on learning
- **Visual**: ASCII-based visualization of data structures
- **Step-by-step**: Detailed execution traces for algorithms
- **Comprehensive**: Covers entire syllabus
- **Educational**: Includes use cases and applications
- **Comparative**: Side-by-side algorithm comparisons

### 💡 Tips for Using This Program
1. Start each module with the "Create Sample" option to see pre-loaded examples
2. Follow the step-by-step outputs to understand algorithm flow
3. Try different inputs to see how algorithms behave
4. Use the comparison features to understand trade-offs
5. Read the application sections to understand real-world usage

### 📝 Sample Usage
```
Main Menu → Arrays, Searching & Sorting → Sorting Algorithms
→ Choose Merge Sort → Enter array elements
→ Watch the step-by-step divide and conquer process
→ See the final sorted array with complexity analysis
```

### 🔧 Customization
- Adjust `MAX_SIZE` in header files for larger data structures
- Modify `TABLE_SIZE` in hashing.h for different hash table sizes
- Extend implementations with additional features as needed

### 🐛 Troubleshooting
- **Compilation errors**: Ensure g++ is installed and in PATH
- **Include errors**: Make sure you're in the correct directory
- **Runtime errors**: Check input constraints (array size, vertex count, etc.)

### 📚 Learning Resources
- Review time complexity after each operation
- Compare different implementations (Matrix vs List for graphs)
- Test edge cases (empty structures, single elements, etc.)
- Experiment with different input sizes

### 🎓 Course Project Submission
This project demonstrates:
- Understanding of all major DSA concepts
- Implementation skills in C++
- Ability to visualize and explain algorithms
- Comprehensive coverage of course syllabus
- Interactive learning tool development

### 👨‍💻 Author
**Vishwakarma Institute of Technology**
DSA Fundamentals Course Project

### 📄 License
Educational use - Course Project

---

**Happy Learning! 🚀**

For questions or improvements, feel free to extend this codebase as part of your learning journey!
