#ifndef HASHING_H
#define HASHING_H

#include <iostream>
#include <string>
#include <iomanip>
#include "utils.h"

using namespace std;

#define TABLE_SIZE 10

// ============== HASH TABLE WITH CHAINING ==============

struct HashNode {
    int key;
    string value;
    HashNode* next;
    
    HashNode(int k, string v) {
        key = k;
        value = v;
        next = nullptr;
    }
};

class HashTableChaining {
private:
    HashNode* table[TABLE_SIZE];
    int collisionCount;
    
    int hashFunction(int key) {
        return key % TABLE_SIZE;
    }
    
public:
    HashTableChaining() {
        for(int i = 0; i < TABLE_SIZE; i++) {
            table[i] = nullptr;
        }
        collisionCount = 0;
    }
    
    void insert(int key, string value) {
        int index = hashFunction(key);
        
        cout << "\n  Inserting key=" << key << ", value=\"" << value << "\"\n";
        cout << "  Hash function: " << key << " % " << TABLE_SIZE << " = " << index << "\n";
        
        HashNode* newNode = new HashNode(key, value);
        
        if(table[index] == nullptr) {
            table[index] = newNode;
            cout << "  ✅ Inserted at index " << index << " (no collision)\n";
        } else {
            cout << "  ⚠️  Collision at index " << index << "!\n";
            cout << "  Resolving using Chaining (Linked List)\n";
            
            collisionCount++;
            
            HashNode* temp = table[index];
            while(temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
            
            cout << "  ✅ Added to chain at index " << index << "\n";
        }
    }
    
    string search(int key) {
        int index = hashFunction(key);
        
        cout << "\n🔍 Searching for key=" << key << "\n";
        cout << "  Hash function: " << key << " % " << TABLE_SIZE << " = " << index << "\n";
        
        HashNode* temp = table[index];
        int steps = 0;
        
        while(temp != nullptr) {
            steps++;
            if(temp->key == key) {
                cout << "  ✅ Found in " << steps << " step(s): \"" << temp->value << "\"\n";
                return temp->value;
            }
            temp = temp->next;
        }
        
        cout << "  ❌ Not found after " << steps << " step(s)\n";
        return "";
    }
    
    void remove(int key) {
        int index = hashFunction(key);
        
        cout << "\n🗑️  Deleting key=" << key << "\n";
        cout << "  Hash function: " << key << " % " << TABLE_SIZE << " = " << index << "\n";
        
        HashNode* temp = table[index];
        HashNode* prev = nullptr;
        
        while(temp != nullptr && temp->key != key) {
            prev = temp;
            temp = temp->next;
        }
        
        if(temp == nullptr) {
            cout << "  ❌ Key not found!\n";
            return;
        }
        
        if(prev == nullptr) {
            table[index] = temp->next;
        } else {
            prev->next = temp->next;
        }
        
        delete temp;
        cout << "  ✅ Deleted successfully!\n";
    }
    
    void display() {
        cout << "\n  Hash Table (Chaining):\n";
        cout << "  ══════════════════════════════════════════════\n";
        
        for(int i = 0; i < TABLE_SIZE; i++) {
            cout << "  [" << i << "] → ";
            
            if(table[i] == nullptr) {
                cout << "NULL\n";
            } else {
                HashNode* temp = table[i];
                while(temp != nullptr) {
                    cout << "(" << temp->key << "," << temp->value << ")";
                    if(temp->next != nullptr) {
                        cout << " → ";
                    }
                    temp = temp->next;
                }
                cout << " → NULL\n";
            }
        }
        
        cout << "  ══════════════════════════════════════════════\n";
        cout << "  Total Collisions: " << collisionCount << "\n\n";
    }
    
    ~HashTableChaining() {
        for(int i = 0; i < TABLE_SIZE; i++) {
            HashNode* temp = table[i];
            while(temp != nullptr) {
                HashNode* toDelete = temp;
                temp = temp->next;
                delete toDelete;
            }
        }
    }
};

// ============== HASH TABLE WITH LINEAR PROBING ==============

struct LinearProbingEntry {
    int key;
    string value;
    bool isOccupied;
    bool isDeleted;
    
    LinearProbingEntry() {
        key = -1;
        value = "";
        isOccupied = false;
        isDeleted = false;
    }
};

class HashTableLinearProbing {
private:
    LinearProbingEntry table[TABLE_SIZE];
    int collisionCount;
    int size;
    
    int hashFunction(int key) {
        return key % TABLE_SIZE;
    }
    
public:
    HashTableLinearProbing() {
        collisionCount = 0;
        size = 0;
    }
    
    void insert(int key, string value) {
        if(size >= TABLE_SIZE) {
            cout << "  ❌ Hash table is full!\n";
            return;
        }
        
        int index = hashFunction(key);
        int originalIndex = index;
        int probes = 0;
        
        cout << "\n  Inserting key=" << key << ", value=\"" << value << "\"\n";
        cout << "  Hash function: " << key << " % " << TABLE_SIZE << " = " << index << "\n";
        
        while(table[index].isOccupied && !table[index].isDeleted) {
            if(table[index].key == key) {
                cout << "  ⚠️  Key already exists! Updating value.\n";
                table[index].value = value;
                return;
            }
            
            if(probes == 0) {
                cout << "  ⚠️  Collision at index " << index << "!\n";
                cout << "  Resolving using Linear Probing\n";
                collisionCount++;
            }
            
            probes++;
            index = (originalIndex + probes) % TABLE_SIZE;
            cout << "  Probe " << probes << ": Try index " << index << "\n";
            
            if(index == originalIndex) {
                cout << "  ❌ Table is full (cycled back)!\n";
                return;
            }
        }
        
        table[index].key = key;
        table[index].value = value;
        table[index].isOccupied = true;
        table[index].isDeleted = false;
        size++;
        
        if(probes > 0) {
            cout << "  ✅ Inserted at index " << index << " after " << probes << " probe(s)\n";
        } else {
            cout << "  ✅ Inserted at index " << index << " (no collision)\n";
        }
    }
    
    string search(int key) {
        int index = hashFunction(key);
        int originalIndex = index;
        int probes = 0;
        
        cout << "\n🔍 Searching for key=" << key << "\n";
        cout << "  Hash function: " << key << " % " << TABLE_SIZE << " = " << index << "\n";
        
        while(table[index].isOccupied || table[index].isDeleted) {
            if(table[index].isOccupied && !table[index].isDeleted && table[index].key == key) {
                cout << "  ✅ Found at index " << index << " after " << probes << " probe(s): \"" 
                     << table[index].value << "\"\n";
                return table[index].value;
            }
            
            probes++;
            index = (originalIndex + probes) % TABLE_SIZE;
            
            if(index == originalIndex) {
                break;
            }
        }
        
        cout << "  ❌ Not found after " << probes << " probe(s)\n";
        return "";
    }
    
    void remove(int key) {
        int index = hashFunction(key);
        int originalIndex = index;
        int probes = 0;
        
        cout << "\n🗑️  Deleting key=" << key << "\n";
        
        while(table[index].isOccupied || table[index].isDeleted) {
            if(table[index].isOccupied && !table[index].isDeleted && table[index].key == key) {
                table[index].isDeleted = true;
                table[index].isOccupied = false;
                size--;
                cout << "  ✅ Deleted from index " << index << "\n";
                return;
            }
            
            probes++;
            index = (originalIndex + probes) % TABLE_SIZE;
            
            if(index == originalIndex) {
                break;
            }
        }
        
        cout << "  ❌ Key not found!\n";
    }
    
    void display() {
        cout << "\n  Hash Table (Linear Probing):\n";
        cout << "  ════════════════════════════════════════\n";
        
        for(int i = 0; i < TABLE_SIZE; i++) {
            cout << "  [" << i << "] → ";
            
            if(!table[i].isOccupied && !table[i].isDeleted) {
                cout << "EMPTY\n";
            } else if(table[i].isDeleted) {
                cout << "DELETED\n";
            } else {
                cout << "(" << table[i].key << ", \"" << table[i].value << "\")\n";
            }
        }
        
        cout << "  ════════════════════════════════════════\n";
        cout << "  Size: " << size << "/" << TABLE_SIZE << "\n";
        cout << "  Load Factor: " << fixed << setprecision(2) 
             << (float)size / TABLE_SIZE << "\n";
        cout << "  Total Collisions: " << collisionCount << "\n\n";
    }
};

// ============== HASH TABLE WITH QUADRATIC PROBING ==============

class HashTableQuadraticProbing {
private:
    LinearProbingEntry table[TABLE_SIZE];
    int collisionCount;
    int size;
    
    int hashFunction(int key) {
        return key % TABLE_SIZE;
    }
    
public:
    HashTableQuadraticProbing() {
        collisionCount = 0;
        size = 0;
    }
    
    void insert(int key, string value) {
        if(size >= TABLE_SIZE) {
            cout << "  ❌ Hash table is full!\n";
            return;
        }
        
        int index = hashFunction(key);
        int originalIndex = index;
        int i = 0;
        
        cout << "\n  Inserting key=" << key << ", value=\"" << value << "\"\n";
        cout << "  Hash function: " << key << " % " << TABLE_SIZE << " = " << index << "\n";
        
        while(table[index].isOccupied && !table[index].isDeleted) {
            if(table[index].key == key) {
                cout << "  ⚠️  Key already exists! Updating value.\n";
                table[index].value = value;
                return;
            }
            
            if(i == 0) {
                cout << "  ⚠️  Collision at index " << index << "!\n";
                cout << "  Resolving using Quadratic Probing\n";
                collisionCount++;
            }
            
            i++;
            index = (originalIndex + i * i) % TABLE_SIZE;
            cout << "  Probe " << i << ": (h + " << i << "²) % " << TABLE_SIZE 
                 << " = index " << index << "\n";
            
            if(i >= TABLE_SIZE) {
                cout << "  ❌ Cannot find empty slot!\n";
                return;
            }
        }
        
        table[index].key = key;
        table[index].value = value;
        table[index].isOccupied = true;
        table[index].isDeleted = false;
        size++;
        
        if(i > 0) {
            cout << "  ✅ Inserted at index " << index << " after " << i << " probe(s)\n";
        } else {
            cout << "  ✅ Inserted at index " << index << " (no collision)\n";
        }
    }
    
    void display() {
        cout << "\n  Hash Table (Quadratic Probing):\n";
        cout << "  ════════════════════════════════════════\n";
        
        for(int i = 0; i < TABLE_SIZE; i++) {
            cout << "  [" << i << "] → ";
            
            if(!table[i].isOccupied && !table[i].isDeleted) {
                cout << "EMPTY\n";
            } else if(table[i].isDeleted) {
                cout << "DELETED\n";
            } else {
                cout << "(" << table[i].key << ", \"" << table[i].value << "\")\n";
            }
        }
        
        cout << "  ════════════════════════════════════════\n";
        cout << "  Size: " << size << "/" << TABLE_SIZE << "\n";
        cout << "  Total Collisions: " << collisionCount << "\n\n";
    }
};

// ============== DOUBLE HASHING ==============

class HashTableDoubleHashing {
private:
    LinearProbingEntry table[TABLE_SIZE];
    int collisionCount;
    int size;
    
    int hashFunction1(int key) {
        return key % TABLE_SIZE;
    }
    
    int hashFunction2(int key) {
        return 7 - (key % 7); // Secondary hash function
    }
    
public:
    HashTableDoubleHashing() {
        collisionCount = 0;
        size = 0;
    }
    
    void insert(int key, string value) {
        if(size >= TABLE_SIZE) {
            cout << "  ❌ Hash table is full!\n";
            return;
        }
        
        int h1 = hashFunction1(key);
        int h2 = hashFunction2(key);
        int index = h1;
        int i = 0;
        
        cout << "\n  Inserting key=" << key << ", value=\"" << value << "\"\n";
        cout << "  Hash1: " << key << " % " << TABLE_SIZE << " = " << h1 << "\n";
        cout << "  Hash2: 7 - (" << key << " % 7) = " << h2 << "\n";
        
        while(table[index].isOccupied && !table[index].isDeleted) {
            if(table[index].key == key) {
                cout << "  ⚠️  Key already exists! Updating value.\n";
                table[index].value = value;
                return;
            }
            
            if(i == 0) {
                cout << "  ⚠️  Collision at index " << index << "!\n";
                cout << "  Resolving using Double Hashing\n";
                collisionCount++;
            }
            
            i++;
            index = (h1 + i * h2) % TABLE_SIZE;
            cout << "  Probe " << i << ": (" << h1 << " + " << i << " * " << h2 
                 << ") % " << TABLE_SIZE << " = " << index << "\n";
            
            if(i >= TABLE_SIZE) {
                cout << "  ❌ Cannot find empty slot!\n";
                return;
            }
        }
        
        table[index].key = key;
        table[index].value = value;
        table[index].isOccupied = true;
        table[index].isDeleted = false;
        size++;
        
        if(i > 0) {
            cout << "  ✅ Inserted at index " << index << " after " << i << " probe(s)\n";
        } else {
            cout << "  ✅ Inserted at index " << index << " (no collision)\n";
        }
    }
    
    void display() {
        cout << "\n  Hash Table (Double Hashing):\n";
        cout << "  ════════════════════════════════════════\n";
        
        for(int i = 0; i < TABLE_SIZE; i++) {
            cout << "  [" << i << "] → ";
            
            if(!table[i].isOccupied && !table[i].isDeleted) {
                cout << "EMPTY\n";
            } else if(table[i].isDeleted) {
                cout << "DELETED\n";
            } else {
                cout << "(" << table[i].key << ", \"" << table[i].value << "\")\n";
            }
        }
        
        cout << "  ════════════════════════════════════════\n";
        cout << "  Size: " << size << "/" << TABLE_SIZE << "\n";
        cout << "  Total Collisions: " << collisionCount << "\n\n";
    }
};

void hashingMenu() {
    int choice;
    
    while(true) {
        printHeader("HASHING - Fast Data Retrieval");
        cout << "\n  1. Hash Table with Chaining\n";
        cout << "  2. Hash Table with Linear Probing\n";
        cout << "  3. Hash Table with Quadratic Probing\n";
        cout << "  4. Hash Table with Double Hashing\n";
        cout << "  5. Compare Collision Resolution Techniques\n";
        cout << "  6. Hashing Concepts\n";
        cout << "  0. Back to Main Menu\n";
        printSeparator();
        cout << "  Enter choice: ";
        cin >> choice;
        
        switch(choice) {
            case 1: {
                HashTableChaining htc;
                int htcChoice, key;
                string value;
                
                while(true) {
                    printHeader("HASH TABLE - CHAINING");
                    cout << "\n  1. Insert\n";
                    cout << "  2. Search\n";
                    cout << "  3. Delete\n";
                    cout << "  4. Display\n";
                    cout << "  5. Insert Sample Data\n";
                    cout << "  0. Back\n";
                    printSeparator();
                    cout << "  Enter choice: ";
                    cin >> htcChoice;
                    
                    if(htcChoice == 0) break;
                    
                    switch(htcChoice) {
                        case 1:
                            cout << "\n📥 Enter key (integer): ";
                            cin >> key;
                            cout << "📥 Enter value (string): ";
                            cin.ignore();
                            getline(cin, value);
                            htc.insert(key, value);
                            pauseScreen();
                            break;
                            
                        case 2:
                            cout << "\n📥 Enter key to search: ";
                            cin >> key;
                            htc.search(key);
                            pauseScreen();
                            break;
                            
                        case 3:
                            cout << "\n📥 Enter key to delete: ";
                            cin >> key;
                            htc.remove(key);
                            pauseScreen();
                            break;
                            
                        case 4:
                            htc.display();
                            pauseScreen();
                            break;
                            
                        case 5:
                            cout << "\n  Inserting sample data...\n";
                            htc.insert(15, "Apple");
                            htc.insert(25, "Banana");
                            htc.insert(35, "Cherry");
                            htc.insert(45, "Date");
                            htc.insert(5, "Elderberry");
                            htc.display();
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
                HashTableLinearProbing htlp;
                int htlpChoice, key;
                string value;
                
                while(true) {
                    printHeader("HASH TABLE - LINEAR PROBING");
                    cout << "\n  1. Insert\n";
                    cout << "  2. Search\n";
                    cout << "  3. Delete\n";
                    cout << "  4. Display\n";
                    cout << "  5. Insert Sample Data\n";
                    cout << "  0. Back\n";
                    printSeparator();
                    cout << "  Enter choice: ";
                    cin >> htlpChoice;
                    
                    if(htlpChoice == 0) break;
                    
                    switch(htlpChoice) {
                        case 1:
                            cout << "\n📥 Enter key (integer): ";
                            cin >> key;
                            cout << "📥 Enter value (string): ";
                            cin.ignore();
                            getline(cin, value);
                            htlp.insert(key, value);
                            pauseScreen();
                            break;
                            
                        case 2:
                            cout << "\n📥 Enter key to search: ";
                            cin >> key;
                            htlp.search(key);
                            pauseScreen();
                            break;
                            
                        case 3:
                            cout << "\n📥 Enter key to delete: ";
                            cin >> key;
                            htlp.remove(key);
                            pauseScreen();
                            break;
                            
                        case 4:
                            htlp.display();
                            pauseScreen();
                            break;
                            
                        case 5:
                            cout << "\n  Inserting sample data...\n";
                            htlp.insert(15, "Apple");
                            htlp.insert(25, "Banana");
                            htlp.insert(35, "Cherry");
                            htlp.insert(45, "Date");
                            htlp.display();
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
                HashTableQuadraticProbing htqp;
                int htqpChoice, key;
                string value;
                
                while(true) {
                    printHeader("HASH TABLE - QUADRATIC PROBING");
                    cout << "\n  1. Insert\n";
                    cout << "  2. Display\n";
                    cout << "  3. Insert Sample Data\n";
                    cout << "  0. Back\n";
                    printSeparator();
                    cout << "  Enter choice: ";
                    cin >> htqpChoice;
                    
                    if(htqpChoice == 0) break;
                    
                    switch(htqpChoice) {
                        case 1:
                            cout << "\n📥 Enter key (integer): ";
                            cin >> key;
                            cout << "📥 Enter value (string): ";
                            cin.ignore();
                            getline(cin, value);
                            htqp.insert(key, value);
                            pauseScreen();
                            break;
                            
                        case 2:
                            htqp.display();
                            pauseScreen();
                            break;
                            
                        case 3:
                            cout << "\n  Inserting sample data...\n";
                            htqp.insert(15, "Apple");
                            htqp.insert(25, "Banana");
                            htqp.insert(35, "Cherry");
                            htqp.display();
                            pauseScreen();
                            break;
                            
                        default:
                            cout << "\n❌ Invalid choice!\n";
                            pauseScreen();
                    }
                }
                break;
            }
            
            case 4: {
                HashTableDoubleHashing htdh;
                int htdhChoice, key;
                string value;
                
                while(true) {
                    printHeader("HASH TABLE - DOUBLE HASHING");
                    cout << "\n  1. Insert\n";
                    cout << "  2. Display\n";
                    cout << "  3. Insert Sample Data\n";
                    cout << "  0. Back\n";
                    printSeparator();
                    cout << "  Enter choice: ";
                    cin >> htdhChoice;
                    
                    if(htdhChoice == 0) break;
                    
                    switch(htdhChoice) {
                        case 1:
                            cout << "\n📥 Enter key (integer): ";
                            cin >> key;
                            cout << "📥 Enter value (string): ";
                            cin.ignore();
                            getline(cin, value);
                            htdh.insert(key, value);
                            pauseScreen();
                            break;
                            
                        case 2:
                            htdh.display();
                            pauseScreen();
                            break;
                            
                        case 3:
                            cout << "\n  Inserting sample data...\n";
                            htdh.insert(15, "Apple");
                            htdh.insert(25, "Banana");
                            htdh.insert(35, "Cherry");
                            htdh.display();
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
                printHeader("COLLISION RESOLUTION COMPARISON");
                
                cout << "\n📊 COLLISION RESOLUTION TECHNIQUES:\n";
                printSeparator();
                
                cout << "\n┌──────────────────┬───────────────┬───────────────┬────────────────┐\n";
                cout << "│   Technique      │  Chaining     │ Linear Probing│ Quadratic Prob │\n";
                cout << "├──────────────────┼───────────────┼───────────────┼────────────────┤\n";
                cout << "│ Data Structure   │ Linked List   │     Array     │     Array      │\n";
                cout << "│ Search (Avg)     │    O(1+α)     │    O(1+α²)    │    O(1+α²)     │\n";
                cout << "│ Insert (Avg)     │    O(1)       │    O(1+α²)    │    O(1+α²)     │\n";
                cout << "│ Delete           │    Easy       │   Complex*    │    Complex*    │\n";
                cout << "│ Clustering       │    No         │     Yes       │     Less       │\n";
                cout << "│ Extra Space      │    Yes        │     No        │     No         │\n";
                cout << "│ Load Factor α    │   Can > 1     │    Must < 1   │    Must < 1    │\n";
                cout << "│ Best Use Case    │ High load     │ Low load      │ Medium load    │\n";
                cout << "└──────────────────┴───────────────┴───────────────┴────────────────┘\n";
                
                cout << "\n  * Requires marking as 'deleted' instead of actual deletion\n";
                cout << "  α (alpha) = Load Factor = n/m (n: elements, m: table size)\n";
                
                cout << "\n💡 CHOOSING A TECHNIQUE:\n";
                printSeparator();
                cout << "\n  • Chaining: When you expect high load factors\n";
                cout << "  • Linear Probing: Best cache performance, simple\n";
                cout << "  • Quadratic Probing: Reduces primary clustering\n";
                cout << "  • Double Hashing: Best distribution, no clustering\n";
                
                pauseScreen();
                break;
            }
            
            case 6: {
                printHeader("HASHING CONCEPTS");
                
                cout << "\n📚 WHAT IS HASHING?\n";
                printSeparator();
                cout << "\n  Hashing is a technique to map data of arbitrary size\n";
                cout << "  to fixed-size values (hash codes) for fast retrieval.\n";
                
                cout << "\n🔑 KEY CONCEPTS:\n";
                printSeparator();
                cout << "\n  • Hash Function: Converts key → index\n";
                cout << "    Example: h(k) = k % table_size\n";
                cout << "\n  • Hash Table: Array-based data structure\n";
                cout << "    Direct access using hash values\n";
                cout << "\n  • Collision: Two keys hash to same index\n";
                cout << "    Inevitable due to Pigeonhole Principle\n";
                cout << "\n  • Load Factor (α): n/m ratio\n";
                cout << "    Indicates how full the table is\n";
                
                cout << "\n⚡ TIME COMPLEXITY:\n";
                printSeparator();
                cout << "\n  • Average Case:\n";
                cout << "    - Insert: O(1)\n";
                cout << "    - Search: O(1)\n";
                cout << "    - Delete: O(1)\n";
                cout << "\n  • Worst Case: O(n)\n";
                cout << "    (All keys collide at same index)\n";
                
                cout << "\n🎯 APPLICATIONS:\n";
                printSeparator();
                cout << "\n  • Database Indexing\n";
                cout << "  • Caching (Web browsers, CDNs)\n";
                cout << "  • Password Storage (cryptographic hashing)\n";
                cout << "  • Compilers (Symbol tables)\n";
                cout << "  • Spell Checkers (Dictionary)\n";
                cout << "  • Blockchain (Cryptographic verification)\n";
                
                cout << "\n🛠️  GOOD HASH FUNCTION PROPERTIES:\n";
                printSeparator();
                cout << "\n  1. Fast to compute\n";
                cout << "  2. Uniform distribution\n";
                cout << "  3. Minimize collisions\n";
                cout << "  4. Use all table positions\n";
                
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
