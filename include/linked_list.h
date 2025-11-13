#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>
#include "utils.h"

using namespace std;

// ============== SINGLY LINKED LIST ==============

struct Node {
    int data;
    Node* next;
    
    Node(int val) {
        data = val;
        next = nullptr;
    }
};

class SinglyLinkedList {
private:
    Node* head;
    
public:
    SinglyLinkedList() {
        head = nullptr;
    }
    
    void insertAtBeginning(int value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
        
        cout << "  ✅ Inserted " << value << " at beginning\n";
        visualize();
    }
    
    void insertAtEnd(int value) {
        Node* newNode = new Node(value);
        
        if(head == nullptr) {
            head = newNode;
        } else {
            Node* temp = head;
            while(temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        
        cout << "  ✅ Inserted " << value << " at end\n";
        visualize();
    }
    
    void insertAtPosition(int value, int pos) {
        if(pos < 1) {
            cout << "  ❌ Invalid position!\n";
            return;
        }
        
        if(pos == 1) {
            insertAtBeginning(value);
            return;
        }
        
        Node* newNode = new Node(value);
        Node* temp = head;
        
        for(int i = 1; i < pos - 1 && temp != nullptr; i++) {
            temp = temp->next;
        }
        
        if(temp == nullptr) {
            cout << "  ❌ Position out of bounds!\n";
            delete newNode;
            return;
        }
        
        newNode->next = temp->next;
        temp->next = newNode;
        
        cout << "  ✅ Inserted " << value << " at position " << pos << "\n";
        visualize();
    }
    
    void deleteFromBeginning() {
        if(head == nullptr) {
            cout << "  ❌ List is empty!\n";
            return;
        }
        
        Node* temp = head;
        head = head->next;
        int value = temp->data;
        delete temp;
        
        cout << "  ✅ Deleted " << value << " from beginning\n";
        visualize();
    }
    
    void deleteFromEnd() {
        if(head == nullptr) {
            cout << "  ❌ List is empty!\n";
            return;
        }
        
        if(head->next == nullptr) {
            int value = head->data;
            delete head;
            head = nullptr;
            cout << "  ✅ Deleted " << value << " from end\n";
            visualize();
            return;
        }
        
        Node* temp = head;
        while(temp->next->next != nullptr) {
            temp = temp->next;
        }
        
        int value = temp->next->data;
        delete temp->next;
        temp->next = nullptr;
        
        cout << "  ✅ Deleted " << value << " from end\n";
        visualize();
    }
    
    bool search(int value) {
        Node* temp = head;
        int pos = 1;
        
        cout << "\n🔍 Searching for " << value << ":\n";
        
        while(temp != nullptr) {
            cout << "  Position " << pos << ": " << temp->data;
            
            if(temp->data == value) {
                cout << " ← Found! ✅\n";
                return true;
            }
            
            cout << " → Next\n";
            temp = temp->next;
            pos++;
        }
        
        cout << "  ❌ Not found!\n";
        return false;
    }
    
    void reverse() {
        Node* prev = nullptr;
        Node* current = head;
        Node* next = nullptr;
        
        cout << "\n🔄 Reversing list:\n";
        visualize();
        
        while(current != nullptr) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        
        head = prev;
        cout << "\n  After reversal:\n";
        visualize();
    }
    
    void visualize() {
        cout << "\n  Singly Linked List:\n";
        cout << "  HEAD";
        
        if(head == nullptr) {
            cout << " → NULL (Empty list)\n\n";
            return;
        }
        
        Node* temp = head;
        while(temp != nullptr) {
            cout << " → [" << temp->data << "|•]";
            temp = temp->next;
        }
        cout << " → NULL\n";
        
        // Show memory addresses
        cout << "  Mem:  ";
        temp = head;
        while(temp != nullptr) {
            cout << "  " << temp << "  ";
            temp = temp->next;
        }
        cout << "\n\n";
    }
    
    int getLength() {
        int count = 0;
        Node* temp = head;
        while(temp != nullptr) {
            count++;
            temp = temp->next;
        }
        return count;
    }
    
    ~SinglyLinkedList() {
        while(head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// ============== DOUBLY LINKED LIST ==============

struct DNode {
    int data;
    DNode* prev;
    DNode* next;
    
    DNode(int val) {
        data = val;
        prev = nullptr;
        next = nullptr;
    }
};

class DoublyLinkedList {
private:
    DNode* head;
    
public:
    DoublyLinkedList() {
        head = nullptr;
    }
    
    void insertAtBeginning(int value) {
        DNode* newNode = new DNode(value);
        
        if(head == nullptr) {
            head = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        
        cout << "  ✅ Inserted " << value << " at beginning\n";
        visualize();
    }
    
    void insertAtEnd(int value) {
        DNode* newNode = new DNode(value);
        
        if(head == nullptr) {
            head = newNode;
        } else {
            DNode* temp = head;
            while(temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->prev = temp;
        }
        
        cout << "  ✅ Inserted " << value << " at end\n";
        visualize();
    }
    
    void deleteNode(int value) {
        if(head == nullptr) {
            cout << "  ❌ List is empty!\n";
            return;
        }
        
        DNode* temp = head;
        
        while(temp != nullptr && temp->data != value) {
            temp = temp->next;
        }
        
        if(temp == nullptr) {
            cout << "  ❌ Value not found!\n";
            return;
        }
        
        if(temp == head) {
            head = head->next;
            if(head != nullptr) {
                head->prev = nullptr;
            }
        } else {
            if(temp->prev != nullptr) {
                temp->prev->next = temp->next;
            }
            if(temp->next != nullptr) {
                temp->next->prev = temp->prev;
            }
        }
        
        delete temp;
        cout << "  ✅ Deleted " << value << "\n";
        visualize();
    }
    
    void visualize() {
        cout << "\n  Doubly Linked List:\n";
        cout << "  HEAD";
        
        if(head == nullptr) {
            cout << " ⇄ NULL (Empty list)\n\n";
            return;
        }
        
        DNode* temp = head;
        while(temp != nullptr) {
            cout << " ⇄ [" << temp->data << "]";
            temp = temp->next;
        }
        cout << " ⇄ NULL\n";
        
        cout << "  (Each node has prev and next pointers)\n\n";
    }
    
    void traverseBackward() {
        if(head == nullptr) {
            cout << "  ❌ List is empty!\n";
            return;
        }
        
        DNode* temp = head;
        while(temp->next != nullptr) {
            temp = temp->next;
        }
        
        cout << "\n  Backward Traversal:\n  ";
        while(temp != nullptr) {
            cout << temp->data << " ← ";
            temp = temp->prev;
        }
        cout << "HEAD\n";
    }
    
    ~DoublyLinkedList() {
        while(head != nullptr) {
            DNode* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// ============== CIRCULAR LINKED LIST ==============

class CircularLinkedList {
private:
    Node* head;
    
public:
    CircularLinkedList() {
        head = nullptr;
    }
    
    void insert(int value) {
        Node* newNode = new Node(value);
        
        if(head == nullptr) {
            head = newNode;
            newNode->next = head; // Point to itself
        } else {
            Node* temp = head;
            while(temp->next != head) {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->next = head;
        }
        
        cout << "  ✅ Inserted " << value << "\n";
        visualize();
    }
    
    void deleteNode(int value) {
        if(head == nullptr) {
            cout << "  ❌ List is empty!\n";
            return;
        }
        
        Node* temp = head;
        Node* prev = nullptr;
        
        // If head needs to be deleted
        if(head->data == value) {
            // Find last node
            while(temp->next != head) {
                temp = temp->next;
            }
            
            if(head == head->next) { // Only one node
                delete head;
                head = nullptr;
            } else {
                temp->next = head->next;
                Node* toDelete = head;
                head = head->next;
                delete toDelete;
            }
            
            cout << "  ✅ Deleted " << value << "\n";
            visualize();
            return;
        }
        
        // Search for node
        prev = head;
        temp = head->next;
        
        while(temp != head && temp->data != value) {
            prev = temp;
            temp = temp->next;
        }
        
        if(temp == head) {
            cout << "  ❌ Value not found!\n";
            return;
        }
        
        prev->next = temp->next;
        delete temp;
        
        cout << "  ✅ Deleted " << value << "\n";
        visualize();
    }
    
    void visualize() {
        cout << "\n  Circular Linked List:\n";
        
        if(head == nullptr) {
            cout << "  EMPTY\n\n";
            return;
        }
        
        cout << "  ";
        Node* temp = head;
        do {
            cout << "[" << temp->data << "] → ";
            temp = temp->next;
        } while(temp != head);
        
        cout << "(back to HEAD)\n";
        cout << "  ↑________________________|\n\n";
    }
    
    ~CircularLinkedList() {
        if(head == nullptr) return;
        
        Node* temp = head;
        Node* next;
        
        do {
            next = temp->next;
            delete temp;
            temp = next;
        } while(temp != head);
    }
};

// ============== POLYNOMIAL OPERATIONS ==============

struct PolyNode {
    int coeff;
    int exp;
    PolyNode* next;
    
    PolyNode(int c, int e) {
        coeff = c;
        exp = e;
        next = nullptr;
    }
};

class Polynomial {
private:
    PolyNode* head;
    
public:
    Polynomial() {
        head = nullptr;
    }
    
    void insert(int coeff, int exp) {
        PolyNode* newNode = new PolyNode(coeff, exp);
        
        if(head == nullptr || exp > head->exp) {
            newNode->next = head;
            head = newNode;
        } else {
            PolyNode* temp = head;
            while(temp->next != nullptr && temp->next->exp > exp) {
                temp = temp->next;
            }
            newNode->next = temp->next;
            temp->next = newNode;
        }
    }
    
    void display() {
        if(head == nullptr) {
            cout << "0";
            return;
        }
        
        PolyNode* temp = head;
        bool first = true;
        
        while(temp != nullptr) {
            if(!first && temp->coeff > 0) {
                cout << " + ";
            } else if(temp->coeff < 0) {
                cout << " - ";
            }
            
            if(abs(temp->coeff) != 1 || temp->exp == 0) {
                cout << abs(temp->coeff);
            }
            
            if(temp->exp > 0) {
                cout << "x";
                if(temp->exp > 1) {
                    cout << "^" << temp->exp;
                }
            }
            
            temp = temp->next;
            first = false;
        }
    }
    
    Polynomial add(Polynomial& p2) {
        Polynomial result;
        PolyNode* p1Ptr = head;
        PolyNode* p2Ptr = p2.head;
        
        while(p1Ptr != nullptr && p2Ptr != nullptr) {
            if(p1Ptr->exp == p2Ptr->exp) {
                int sumCoeff = p1Ptr->coeff + p2Ptr->coeff;
                if(sumCoeff != 0) {
                    result.insert(sumCoeff, p1Ptr->exp);
                }
                p1Ptr = p1Ptr->next;
                p2Ptr = p2Ptr->next;
            } else if(p1Ptr->exp > p2Ptr->exp) {
                result.insert(p1Ptr->coeff, p1Ptr->exp);
                p1Ptr = p1Ptr->next;
            } else {
                result.insert(p2Ptr->coeff, p2Ptr->exp);
                p2Ptr = p2Ptr->next;
            }
        }
        
        while(p1Ptr != nullptr) {
            result.insert(p1Ptr->coeff, p1Ptr->exp);
            p1Ptr = p1Ptr->next;
        }
        
        while(p2Ptr != nullptr) {
            result.insert(p2Ptr->coeff, p2Ptr->exp);
            p2Ptr = p2Ptr->next;
        }
        
        return result;
    }
};

void polynomialDemo() {
    printHeader("POLYNOMIAL OPERATIONS");
    
    Polynomial p1, p2;
    
    cout << "\n📝 Creating Polynomial 1:\n";
    int terms;
    cout << "  Enter number of terms: ";
    cin >> terms;
    
    for(int i = 0; i < terms; i++) {
        int coeff, exp;
        cout << "  Term " << (i+1) << " - Coefficient: ";
        cin >> coeff;
        cout << "  Term " << (i+1) << " - Exponent: ";
        cin >> exp;
        p1.insert(coeff, exp);
    }
    
    cout << "\n📝 Creating Polynomial 2:\n";
    cout << "  Enter number of terms: ";
    cin >> terms;
    
    for(int i = 0; i < terms; i++) {
        int coeff, exp;
        cout << "  Term " << (i+1) << " - Coefficient: ";
        cin >> coeff;
        cout << "  Term " << (i+1) << " - Exponent: ";
        cin >> exp;
        p2.insert(coeff, exp);
    }
    
    cout << "\n📊 Polynomial 1: ";
    p1.display();
    cout << "\n📊 Polynomial 2: ";
    p2.display();
    
    cout << "\n\n➕ Addition:\n";
    Polynomial result = p1.add(p2);
    cout << "  Result: ";
    result.display();
    cout << "\n";
    
    pauseScreen();
}

void linkedListMenu() {
    int choice;
    
    while(true) {
        printHeader("LINKED LISTS");
        cout << "\n  1. Singly Linked List\n";
        cout << "  2. Doubly Linked List\n";
        cout << "  3. Circular Linked List\n";
        cout << "  4. Polynomial Operations\n";
        cout << "  5. Compare All List Types\n";
        cout << "  0. Back to Main Menu\n";
        printSeparator();
        cout << "  Enter choice: ";
        cin >> choice;
        
        switch(choice) {
            case 1: {
                SinglyLinkedList sll;
                int slChoice, value, pos;
                
                while(true) {
                    printHeader("SINGLY LINKED LIST");
                    cout << "\n  1. Insert at Beginning\n";
                    cout << "  2. Insert at End\n";
                    cout << "  3. Insert at Position\n";
                    cout << "  4. Delete from Beginning\n";
                    cout << "  5. Delete from End\n";
                    cout << "  6. Search\n";
                    cout << "  7. Reverse List\n";
                    cout << "  8. Display List\n";
                    cout << "  0. Back\n";
                    printSeparator();
                    cout << "  Enter choice: ";
                    cin >> slChoice;
                    
                    if(slChoice == 0) break;
                    
                    switch(slChoice) {
                        case 1:
                            cout << "\n📥 Enter value: ";
                            cin >> value;
                            sll.insertAtBeginning(value);
                            pauseScreen();
                            break;
                        case 2:
                            cout << "\n📥 Enter value: ";
                            cin >> value;
                            sll.insertAtEnd(value);
                            pauseScreen();
                            break;
                        case 3:
                            cout << "\n📥 Enter value: ";
                            cin >> value;
                            cout << "📥 Enter position: ";
                            cin >> pos;
                            sll.insertAtPosition(value, pos);
                            pauseScreen();
                            break;
                        case 4:
                            sll.deleteFromBeginning();
                            pauseScreen();
                            break;
                        case 5:
                            sll.deleteFromEnd();
                            pauseScreen();
                            break;
                        case 6:
                            cout << "\n📥 Enter value to search: ";
                            cin >> value;
                            sll.search(value);
                            pauseScreen();
                            break;
                        case 7:
                            sll.reverse();
                            pauseScreen();
                            break;
                        case 8:
                            sll.visualize();
                            cout << "  Length: " << sll.getLength() << "\n";
                            pauseScreen();
                            break;
                        default:
                            cout << "\n❌ Invalid choice!\n";
                            pauseScreen();
                    }
                }
                break;
            }
            
            case 2: {
                DoublyLinkedList dll;
                int dlChoice, value;
                
                while(true) {
                    printHeader("DOUBLY LINKED LIST");
                    cout << "\n  1. Insert at Beginning\n";
                    cout << "  2. Insert at End\n";
                    cout << "  3. Delete Node\n";
                    cout << "  4. Display Forward\n";
                    cout << "  5. Display Backward\n";
                    cout << "  0. Back\n";
                    printSeparator();
                    cout << "  Enter choice: ";
                    cin >> dlChoice;
                    
                    if(dlChoice == 0) break;
                    
                    switch(dlChoice) {
                        case 1:
                            cout << "\n📥 Enter value: ";
                            cin >> value;
                            dll.insertAtBeginning(value);
                            pauseScreen();
                            break;
                        case 2:
                            cout << "\n📥 Enter value: ";
                            cin >> value;
                            dll.insertAtEnd(value);
                            pauseScreen();
                            break;
                        case 3:
                            cout << "\n📥 Enter value to delete: ";
                            cin >> value;
                            dll.deleteNode(value);
                            pauseScreen();
                            break;
                        case 4:
                            dll.visualize();
                            pauseScreen();
                            break;
                        case 5:
                            dll.traverseBackward();
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
                CircularLinkedList cll;
                int clChoice, value;
                
                while(true) {
                    printHeader("CIRCULAR LINKED LIST");
                    cout << "\n  1. Insert\n";
                    cout << "  2. Delete\n";
                    cout << "  3. Display\n";
                    cout << "  0. Back\n";
                    printSeparator();
                    cout << "  Enter choice: ";
                    cin >> clChoice;
                    
                    if(clChoice == 0) break;
                    
                    switch(clChoice) {
                        case 1:
                            cout << "\n📥 Enter value: ";
                            cin >> value;
                            cll.insert(value);
                            pauseScreen();
                            break;
                        case 2:
                            cout << "\n📥 Enter value to delete: ";
                            cin >> value;
                            cll.deleteNode(value);
                            pauseScreen();
                            break;
                        case 3:
                            cll.visualize();
                            pauseScreen();
                            break;
                        default:
                            cout << "\n❌ Invalid choice!\n";
                            pauseScreen();
                    }
                }
                break;
            }
            
            case 4:
                polynomialDemo();
                break;
                
            case 5: {
                printHeader("COMPARISON: Linked List Types");
                cout << "\n╔══════════════════════╦══════════════╦══════════════╦══════════════╗\n";
                cout << "║ Operation            ║   Singly     ║   Doubly     ║   Circular   ║\n";
                cout << "╠══════════════════════╬══════════════╬══════════════╬══════════════╣\n";
                cout << "║ Insert at Beginning  ║     O(1)     ║     O(1)     ║     O(1)     ║\n";
                cout << "║ Insert at End        ║     O(n)     ║     O(1)*    ║     O(n)     ║\n";
                cout << "║ Delete from Begin    ║     O(1)     ║     O(1)     ║     O(1)     ║\n";
                cout << "║ Delete from End      ║     O(n)     ║     O(1)*    ║     O(n)     ║\n";
                cout << "║ Search               ║     O(n)     ║     O(n)     ║     O(n)     ║\n";
                cout << "║ Reverse Traversal    ║     No       ║     Yes      ║     Yes**    ║\n";
                cout << "║ Memory per Node      ║   1 pointer  ║  2 pointers  ║  1 pointer   ║\n";
                cout << "╚══════════════════════╩══════════════╩══════════════╩══════════════╝\n";
                cout << "\n  * With tail pointer\n";
                cout << "  ** Can traverse circularly\n";
                
                cout << "\n💡 USE CASES:\n";
                cout << "  • Singly: Simple, memory efficient, one-direction traversal\n";
                cout << "  • Doubly: Bidirectional traversal, easier deletion\n";
                cout << "  • Circular: Round-robin scheduling, music playlist\n";
                
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
