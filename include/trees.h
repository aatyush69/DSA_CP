#ifndef TREES_H
#define TREES_H

#include <iostream>
#include <queue>
#include <algorithm>
#include "utils.h"

using namespace std;

// ============== BINARY TREE ==============

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

class BinaryTree {
private:
    TreeNode* root;
    
    void inorderHelper(TreeNode* node) {
        if(node == nullptr) return;
        
        inorderHelper(node->left);
        cout << node->data << " ";
        inorderHelper(node->right);
    }
    
    void preorderHelper(TreeNode* node) {
        if(node == nullptr) return;
        
        cout << node->data << " ";
        preorderHelper(node->left);
        preorderHelper(node->right);
    }
    
    void postorderHelper(TreeNode* node) {
        if(node == nullptr) return;
        
        postorderHelper(node->left);
        postorderHelper(node->right);
        cout << node->data << " ";
    }
    
    void printTreeHelper(TreeNode* node, string prefix, bool isLeft) {
        if(node == nullptr) return;
        
        cout << prefix;
        cout << (isLeft ? "├──" : "└──");
        cout << node->data << "\n";
        
        if(node->left != nullptr || node->right != nullptr) {
            if(node->left != nullptr) {
                printTreeHelper(node->left, prefix + (isLeft ? "│   " : "    "), true);
            } else {
                cout << prefix << (isLeft ? "│   " : "    ") << "├──(null)\n";
            }
            
            if(node->right != nullptr) {
                printTreeHelper(node->right, prefix + (isLeft ? "│   " : "    "), false);
            } else {
                cout << prefix << (isLeft ? "│   " : "    ") << "└──(null)\n";
            }
        }
    }
    
    int heightHelper(TreeNode* node) {
        if(node == nullptr) return 0;
        return 1 + max(heightHelper(node->left), heightHelper(node->right));
    }
    
    int countNodesHelper(TreeNode* node) {
        if(node == nullptr) return 0;
        return 1 + countNodesHelper(node->left) + countNodesHelper(node->right);
    }
    
public:
    BinaryTree() {
        root = nullptr;
    }
    
    TreeNode* getRoot() {
        return root;
    }
    
    void createSampleTree() {
        root = new TreeNode(1);
        root->left = new TreeNode(2);
        root->right = new TreeNode(3);
        root->left->left = new TreeNode(4);
        root->left->right = new TreeNode(5);
        root->right->left = new TreeNode(6);
        root->right->right = new TreeNode(7);
        
        cout << "  ✅ Sample tree created!\n";
    }
    
    void inorderTraversal() {
        cout << "\n  📊 Inorder (Left-Root-Right): ";
        inorderHelper(root);
        cout << "\n  Use case: BST gives sorted output\n";
    }
    
    void preorderTraversal() {
        cout << "\n  📊 Preorder (Root-Left-Right): ";
        preorderHelper(root);
        cout << "\n  Use case: Create copy of tree\n";
    }
    
    void postorderTraversal() {
        cout << "\n  📊 Postorder (Left-Right-Root): ";
        postorderHelper(root);
        cout << "\n  Use case: Delete tree, evaluate expression tree\n";
    }
    
    void levelOrderTraversal() {
        if(root == nullptr) {
            cout << "\n  Tree is empty!\n";
            return;
        }
        
        cout << "\n  📊 Level Order (Breadth-First): ";
        queue<TreeNode*> q;
        q.push(root);
        
        while(!q.empty()) {
            TreeNode* current = q.front();
            q.pop();
            
            cout << current->data << " ";
            
            if(current->left != nullptr)
                q.push(current->left);
            if(current->right != nullptr)
                q.push(current->right);
        }
        cout << "\n  Use case: Level-wise processing\n";
    }
    
    void visualize() {
        cout << "\n  Tree Structure:\n\n";
        if(root == nullptr) {
            cout << "  (empty)\n";
            return;
        }
        
        printTreeHelper(root, "  ", false);
        cout << "\n";
    }
    
    int height() {
        return heightHelper(root);
    }
    
    int countNodes() {
        return countNodesHelper(root);
    }
};

// ============== BINARY SEARCH TREE ==============

class BST {
private:
    TreeNode* root;
    
    TreeNode* insertHelper(TreeNode* node, int value) {
        if(node == nullptr) {
            return new TreeNode(value);
        }
        
        if(value < node->data) {
            node->left = insertHelper(node->left, value);
        } else if(value > node->data) {
            node->right = insertHelper(node->right, value);
        }
        
        return node;
    }
    
    TreeNode* searchHelper(TreeNode* node, int value, int& steps) {
        steps++;
        
        if(node == nullptr || node->data == value) {
            return node;
        }
        
        cout << "  Step " << steps << ": At node " << node->data;
        
        if(value < node->data) {
            cout << " → Go LEFT (searching for " << value << ")\n";
            return searchHelper(node->left, value, steps);
        } else {
            cout << " → Go RIGHT (searching for " << value << ")\n";
            return searchHelper(node->right, value, steps);
        }
    }
    
    TreeNode* findMin(TreeNode* node) {
        while(node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
    
    TreeNode* deleteHelper(TreeNode* node, int value) {
        if(node == nullptr) return node;
        
        if(value < node->data) {
            node->left = deleteHelper(node->left, value);
        } else if(value > node->data) {
            node->right = deleteHelper(node->right, value);
        } else {
            // Node found - delete it
            
            // Case 1: No child
            if(node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            }
            // Case 2: One child
            else if(node->left == nullptr) {
                TreeNode* temp = node->right;
                delete node;
                return temp;
            } else if(node->right == nullptr) {
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }
            // Case 3: Two children
            else {
                TreeNode* temp = findMin(node->right);
                node->data = temp->data;
                node->right = deleteHelper(node->right, temp->data);
            }
        }
        return node;
    }
    
    void inorderHelper(TreeNode* node) {
        if(node == nullptr) return;
        inorderHelper(node->left);
        cout << node->data << " ";
        inorderHelper(node->right);
    }
    
    void printTreeHelper(TreeNode* node, string prefix, bool isLeft) {
        if(node == nullptr) return;
        
        cout << prefix;
        cout << (isLeft ? "├──" : "└──");
        cout << node->data << "\n";
        
        if(node->left != nullptr || node->right != nullptr) {
            if(node->left != nullptr) {
                printTreeHelper(node->left, prefix + (isLeft ? "│   " : "    "), true);
            }
            if(node->right != nullptr) {
                printTreeHelper(node->right, prefix + (isLeft ? "│   " : "    "), false);
            }
        }
    }
    
public:
    BST() {
        root = nullptr;
    }
    
    void insert(int value) {
        cout << "  Inserting " << value << "...\n";
        root = insertHelper(root, value);
        cout << "  ✅ Inserted successfully!\n";
    }
    
    bool search(int value) {
        cout << "\n🔍 Searching for " << value << ":\n";
        int steps = 0;
        TreeNode* result = searchHelper(root, value, steps);
        
        if(result != nullptr) {
            cout << "  ✅ Found in " << steps << " steps!\n";
            cout << "  Time Complexity: O(log n) average, O(n) worst\n";
            return true;
        } else {
            cout << "  ❌ Not found after " << steps << " steps\n";
            return false;
        }
    }
    
    void remove(int value) {
        cout << "\n🗑️  Deleting " << value << "...\n";
        root = deleteHelper(root, value);
        cout << "  ✅ Deleted successfully!\n";
    }
    
    void display() {
        cout << "\n  BST (Inorder - Sorted): ";
        inorderHelper(root);
        cout << "\n";
    }
    
    void visualize() {
        cout << "\n  Binary Search Tree:\n\n";
        if(root == nullptr) {
            cout << "  (empty)\n";
            return;
        }
        
        printTreeHelper(root, "  ", false);
        cout << "\n  Property: Left < Root < Right\n\n";
    }
};

// ============== AVL TREE ==============

struct AVLNode {
    int data;
    AVLNode* left;
    AVLNode* right;
    int height;
    
    AVLNode(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

class AVLTree {
private:
    AVLNode* root;
    
    int height(AVLNode* node) {
        return node == nullptr ? 0 : node->height;
    }
    
    int getBalance(AVLNode* node) {
        return node == nullptr ? 0 : height(node->left) - height(node->right);
    }
    
    AVLNode* rightRotate(AVLNode* y) {
        cout << "    → Right Rotation at node " << y->data << "\n";
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;
        
        x->right = y;
        y->left = T2;
        
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;
        
        return x;
    }
    
    AVLNode* leftRotate(AVLNode* x) {
        cout << "    → Left Rotation at node " << x->data << "\n";
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;
        
        y->left = x;
        x->right = T2;
        
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        
        return y;
    }
    
    AVLNode* insertHelper(AVLNode* node, int value) {
        if(node == nullptr) {
            return new AVLNode(value);
        }
        
        if(value < node->data) {
            node->left = insertHelper(node->left, value);
        } else if(value > node->data) {
            node->right = insertHelper(node->right, value);
        } else {
            return node; // Duplicate values not allowed
        }
        
        node->height = 1 + max(height(node->left), height(node->right));
        
        int balance = getBalance(node);
        
        // Left Left Case
        if(balance > 1 && value < node->left->data) {
            cout << "    ⚖️  Imbalance detected: Left-Left case\n";
            return rightRotate(node);
        }
        
        // Right Right Case
        if(balance < -1 && value > node->right->data) {
            cout << "    ⚖️  Imbalance detected: Right-Right case\n";
            return leftRotate(node);
        }
        
        // Left Right Case
        if(balance > 1 && value > node->left->data) {
            cout << "    ⚖️  Imbalance detected: Left-Right case\n";
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        
        // Right Left Case
        if(balance < -1 && value < node->right->data) {
            cout << "    ⚖️  Imbalance detected: Right-Left case\n";
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        
        return node;
    }
    
    void inorderHelper(AVLNode* node) {
        if(node == nullptr) return;
        inorderHelper(node->left);
        cout << node->data << "(h:" << node->height << ",b:" << getBalance(node) << ") ";
        inorderHelper(node->right);
    }
    
    void printTreeHelper(AVLNode* node, string prefix, bool isLeft) {
        if(node == nullptr) return;
        
        cout << prefix;
        cout << (isLeft ? "├──" : "└──");
        cout << node->data << " [h:" << node->height << ", b:" << getBalance(node) << "]\n";
        
        if(node->left != nullptr || node->right != nullptr) {
            if(node->left != nullptr) {
                printTreeHelper(node->left, prefix + (isLeft ? "│   " : "    "), true);
            }
            if(node->right != nullptr) {
                printTreeHelper(node->right, prefix + (isLeft ? "│   " : "    "), false);
            }
        }
    }
    
public:
    AVLTree() {
        root = nullptr;
    }
    
    void insert(int value) {
        cout << "  Inserting " << value << "...\n";
        root = insertHelper(root, value);
        cout << "  ✅ Inserted and balanced!\n";
    }
    
    void display() {
        cout << "\n  AVL Tree (with height & balance factor):\n  ";
        inorderHelper(root);
        cout << "\n";
    }
    
    void visualize() {
        cout << "\n  AVL Tree (Self-Balancing):\n\n";
        if(root == nullptr) {
            cout << "  (empty)\n";
            return;
        }
        
        printTreeHelper(root, "  ", false);
        cout << "\n  h: height, b: balance factor (-1, 0, +1)\n";
        cout << "  Property: |balance| ≤ 1 for all nodes\n\n";
    }
};

// ============== HEAP ==============

class MinHeap {
private:
    int arr[100];
    int size;
    
    void heapifyUp(int index) {
        if(index == 0) return;
        
        int parent = (index - 1) / 2;
        
        if(arr[index] < arr[parent]) {
            swap(arr[index], arr[parent]);
            heapifyUp(parent);
        }
    }
    
    void heapifyDown(int index) {
        int smallest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        
        if(left < size && arr[left] < arr[smallest]) {
            smallest = left;
        }
        
        if(right < size && arr[right] < arr[smallest]) {
            smallest = right;
        }
        
        if(smallest != index) {
            swap(arr[index], arr[smallest]);
            heapifyDown(smallest);
        }
    }
    
public:
    MinHeap() {
        size = 0;
    }
    
    void insert(int value) {
        if(size >= 100) {
            cout << "  ❌ Heap is full!\n";
            return;
        }
        
        arr[size] = value;
        heapifyUp(size);
        size++;
        
        cout << "  ✅ Inserted " << value << "\n";
        visualize();
    }
    
    int extractMin() {
        if(size == 0) {
            cout << "  ❌ Heap is empty!\n";
            return -1;
        }
        
        int minValue = arr[0];
        arr[0] = arr[size - 1];
        size--;
        
        heapifyDown(0);
        
        cout << "  ✅ Extracted min: " << minValue << "\n";
        visualize();
        return minValue;
    }
    
    void visualize() {
        cout << "\n  Min Heap (Array representation):\n  ";
        
        for(int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        
        cout << "\n\n  Tree view:\n";
        
        if(size == 0) {
            cout << "  (empty)\n";
            return;
        }
        
        int level = 0;
        int nodesInLevel = 1;
        int nodesPrinted = 0;
        
        for(int i = 0; i < size; ) {
            cout << "  Level " << level << ": ";
            
            for(int j = 0; j < nodesInLevel && i < size; j++, i++) {
                cout << arr[i] << " ";
                nodesPrinted++;
            }
            
            cout << "\n";
            level++;
            nodesInLevel *= 2;
        }
        
        cout << "  Property: Parent ≤ Children\n\n";
    }
};

void treeMenu() {
    int choice;
    
    while(true) {
        printHeader("TREES - Hierarchical Data Structures");
        cout << "\n  1. Binary Tree & Traversals\n";
        cout << "  2. Binary Search Tree (BST)\n";
        cout << "  3. AVL Tree (Self-Balancing)\n";
        cout << "  4. Heap Tree (Min Heap)\n";
        cout << "  5. Expression Tree Demo\n";
        cout << "  6. Tree Terminology & Concepts\n";
        cout << "  0. Back to Main Menu\n";
        printSeparator();
        cout << "  Enter choice: ";
        cin >> choice;
        
        switch(choice) {
            case 1: {
                printHeader("BINARY TREE & TRAVERSALS");
                
                BinaryTree bt;
                bt.createSampleTree();
                bt.visualize();
                
                cout << "\n📚 TREE TRAVERSALS:\n";
                printSeparator();
                
                bt.inorderTraversal();
                bt.preorderTraversal();
                bt.postorderTraversal();
                bt.levelOrderTraversal();
                
                cout << "\n📊 Tree Properties:\n";
                cout << "  Height: " << bt.height() << "\n";
                cout << "  Total Nodes: " << bt.countNodes() << "\n";
                
                pauseScreen();
                break;
            }
            
            case 2: {
                BST bst;
                int bstChoice, value;
                
                while(true) {
                    printHeader("BINARY SEARCH TREE");
                    cout << "\n  1. Insert Node\n";
                    cout << "  2. Search Node\n";
                    cout << "  3. Delete Node\n";
                    cout << "  4. Display (Inorder)\n";
                    cout << "  5. Visualize Tree\n";
                    cout << "  6. Create Sample BST\n";
                    cout << "  0. Back\n";
                    printSeparator();
                    cout << "  Enter choice: ";
                    cin >> bstChoice;
                    
                    if(bstChoice == 0) break;
                    
                    switch(bstChoice) {
                        case 1:
                            cout << "\n📥 Enter value: ";
                            cin >> value;
                            bst.insert(value);
                            pauseScreen();
                            break;
                        case 2:
                            cout << "\n📥 Enter value to search: ";
                            cin >> value;
                            bst.search(value);
                            pauseScreen();
                            break;
                        case 3:
                            cout << "\n📥 Enter value to delete: ";
                            cin >> value;
                            bst.remove(value);
                            pauseScreen();
                            break;
                        case 4:
                            bst.display();
                            pauseScreen();
                            break;
                        case 5:
                            bst.visualize();
                            pauseScreen();
                            break;
                        case 6:
                            bst.insert(50);
                            bst.insert(30);
                            bst.insert(70);
                            bst.insert(20);
                            bst.insert(40);
                            bst.insert(60);
                            bst.insert(80);
                            bst.visualize();
                            pauseScreen();
                            break;
                        default:
                            cout << "\n❌ Invalid choice!\n";
                            pauseScreen();
                    }
                }
                break;
            }
            
            case 3: {
                AVLTree avl;
                int avlChoice, value;
                
                while(true) {
                    printHeader("AVL TREE (Self-Balancing BST)");
                    cout << "\n  1. Insert Node (Auto-balancing)\n";
                    cout << "  2. Display Tree\n";
                    cout << "  3. Visualize Tree\n";
                    cout << "  4. Demo Rotations\n";
                    cout << "  0. Back\n";
                    printSeparator();
                    cout << "  Enter choice: ";
                    cin >> avlChoice;
                    
                    if(avlChoice == 0) break;
                    
                    switch(avlChoice) {
                        case 1:
                            cout << "\n📥 Enter value: ";
                            cin >> value;
                            avl.insert(value);
                            pauseScreen();
                            break;
                        case 2:
                            avl.display();
                            pauseScreen();
                            break;
                        case 3:
                            avl.visualize();
                            pauseScreen();
                            break;
                        case 4: {
                            cout << "\n🔄 AVL Rotation Demo:\n";
                            printSeparator();
                            cout << "\n  Inserting sequence: 10, 20, 30\n";
                            cout << "  This will cause Right-Right imbalance\n\n";
                            
                            {
                                AVLTree demo;
                                demo.insert(10);
                                demo.insert(20);
                                demo.insert(30);
                                demo.visualize();
                            }
                            
                            pauseScreen();
                            break;
                        }
                        default:
                            cout << "\n❌ Invalid choice!\n";
                            pauseScreen();
                    }
                }
                break;
            }
            
            case 4: {
                MinHeap heap;
                int heapChoice, value;
                
                while(true) {
                    printHeader("MIN HEAP");
                    cout << "\n  1. Insert Element\n";
                    cout << "  2. Extract Minimum\n";
                    cout << "  3. Visualize Heap\n";
                    cout << "  4. Create Sample Heap\n";
                    cout << "  0. Back\n";
                    printSeparator();
                    cout << "  Enter choice: ";
                    cin >> heapChoice;
                    
                    if(heapChoice == 0) break;
                    
                    switch(heapChoice) {
                        case 1:
                            cout << "\n📥 Enter value: ";
                            cin >> value;
                            heap.insert(value);
                            pauseScreen();
                            break;
                        case 2:
                            heap.extractMin();
                            pauseScreen();
                            break;
                        case 3:
                            heap.visualize();
                            pauseScreen();
                            break;
                        case 4:
                            heap.insert(50);
                            heap.insert(30);
                            heap.insert(70);
                            heap.insert(20);
                            heap.insert(40);
                            heap.insert(60);
                            heap.visualize();
                            pauseScreen();
                            break;
                        default:
                            cout << "\n❌ Invalid choice!\n";
                            pauseScreen();
                    }
                }
                break;
            }
            
            case 5: {
                printHeader("EXPRESSION TREE");
                cout << "\n📝 Example: (a + b) * (c - d)\n\n";
                cout << "  Expression Tree Structure:\n\n";
                cout << "          *\n";
                cout << "        /   \\\n";
                cout << "       +     -\n";
                cout << "      / \\   / \\\n";
                cout << "     a   b c   d\n\n";
                
                cout << "  Traversals:\n";
                printSeparator(40);
                cout << "  Inorder   (Infix):    a + b * c - d\n";
                cout << "  Preorder  (Prefix):   * + a b - c d\n";
                cout << "  Postorder (Postfix):  a b + c d - *\n\n";
                
                cout << "  💡 Use Case: Expression evaluation in compilers\n";
                
                pauseScreen();
                break;
            }
            
            case 6: {
                printHeader("TREE TERMINOLOGY & CONCEPTS");
                cout << "\n📚 TREE TERMINOLOGIES:\n";
                printSeparator();
                cout << "\n  • Root: Topmost node (no parent)\n";
                cout << "  • Leaf: Node with no children\n";
                cout << "  • Height: Longest path from root to leaf\n";
                cout << "  • Depth: Path length from root to node\n";
                cout << "  • Level: Depth + 1\n";
                cout << "  • Degree: Number of children of a node\n";
                cout << "  • Subtree: Tree formed by a node and descendants\n";
                
                cout << "\n🌳 TYPES OF TREES:\n";
                printSeparator();
                cout << "\n  1. Binary Tree: Max 2 children per node\n";
                cout << "  2. Binary Search Tree: Left < Root < Right\n";
                cout << "  3. AVL Tree: Self-balancing BST\n";
                cout << "  4. Heap: Complete binary tree (min/max property)\n";
                cout << "  5. B-Tree: Multi-way tree for databases\n";
                cout << "  6. Trie: Prefix tree for strings\n";
                
                cout << "\n🎯 APPLICATIONS:\n";
                printSeparator();
                cout << "\n  • File Systems: Directory hierarchy\n";
                cout << "  • Databases: B-trees for indexing\n";
                cout << "  • Compilers: Expression trees, syntax trees\n";
                cout << "  • AI: Decision trees, game trees\n";
                cout << "  • Networks: Routing algorithms\n";
                
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
