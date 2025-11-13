#ifndef GRAPHS_H
#define GRAPHS_H

#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <iomanip>
#include "utils.h"

using namespace std;

#define MAX_VERTICES 20

// ============== GRAPH (Adjacency Matrix) ==============

class Graph {
private:
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
    int numVertices;
    bool visited[MAX_VERTICES];
    
    void resetVisited() {
        for(int i = 0; i < numVertices; i++) {
            visited[i] = false;
        }
    }
    
    void DFSHelper(int vertex) {
        visited[vertex] = true;
        cout << vertex << " ";
        
        for(int i = 0; i < numVertices; i++) {
            if(adjMatrix[vertex][i] == 1 && !visited[i]) {
                cout << "\n  → From " << vertex << " to " << i;
                DFSHelper(i);
            }
        }
    }
    
public:
    Graph(int vertices) {
        numVertices = vertices;
        
        // Initialize matrix with 0
        for(int i = 0; i < numVertices; i++) {
            for(int j = 0; j < numVertices; j++) {
                adjMatrix[i][j] = 0;
            }
            visited[i] = false;
        }
    }
    
    void addEdge(int src, int dest, bool isDirected = false) {
        if(src >= numVertices || dest >= numVertices) {
            cout << "  ❌ Invalid vertex!\n";
            return;
        }
        
        adjMatrix[src][dest] = 1;
        
        if(!isDirected) {
            adjMatrix[dest][src] = 1;
        }
        
        cout << "  ✅ Edge added: " << src;
        cout << (isDirected ? " → " : " ↔ ");
        cout << dest << "\n";
    }
    
    void removeEdge(int src, int dest, bool isDirected = false) {
        if(src >= numVertices || dest >= numVertices) {
            cout << "  ❌ Invalid vertex!\n";
            return;
        }
        
        adjMatrix[src][dest] = 0;
        
        if(!isDirected) {
            adjMatrix[dest][src] = 0;
        }
        
        cout << "  ✅ Edge removed: " << src << " - " << dest << "\n";
    }
    
    void displayMatrix() {
        cout << "\n  Adjacency Matrix:\n\n";
        cout << "     ";
        
        for(int i = 0; i < numVertices; i++) {
            cout << setw(3) << i;
        }
        cout << "\n";
        
        printSeparator(5 + numVertices * 3);
        
        for(int i = 0; i < numVertices; i++) {
            cout << "  " << setw(2) << i << "│";
            for(int j = 0; j < numVertices; j++) {
                cout << setw(3) << adjMatrix[i][j];
            }
            cout << "\n";
        }
        cout << "\n";
    }
    
    void BFS(int startVertex) {
        if(startVertex >= numVertices) {
            cout << "  ❌ Invalid start vertex!\n";
            return;
        }
        
        resetVisited();
        
        cout << "\n🔍 BFS (Breadth-First Search) Traversal:\n";
        printSeparator();
        cout << "  Starting from vertex " << startVertex << "\n\n";
        
        queue<int> q;
        visited[startVertex] = true;
        q.push(startVertex);
        
        cout << "  Traversal order: ";
        int step = 1;
        
        while(!q.empty()) {
            int current = q.front();
            q.pop();
            
            cout << current << " ";
            
            cout << "\n  Step " << step++ << ": Visiting " << current << "\n";
            cout << "  → Adding neighbors to queue: ";
            
            bool hasNeighbors = false;
            for(int i = 0; i < numVertices; i++) {
                if(adjMatrix[current][i] == 1 && !visited[i]) {
                    visited[i] = true;
                    q.push(i);
                    cout << i << " ";
                    hasNeighbors = true;
                }
            }
            
            if(!hasNeighbors) {
                cout << "(none)";
            }
            cout << "\n\n";
        }
        
        cout << "\n  Time Complexity: O(V + E)\n";
        cout << "  Space Complexity: O(V) for queue\n";
        cout << "  Use Case: Shortest path, level-order processing\n";
    }
    
    void DFS(int startVertex) {
        if(startVertex >= numVertices) {
            cout << "  ❌ Invalid start vertex!\n";
            return;
        }
        
        resetVisited();
        
        cout << "\n🔍 DFS (Depth-First Search) Traversal:\n";
        printSeparator();
        cout << "  Starting from vertex " << startVertex << "\n\n";
        cout << "  Traversal order: ";
        
        DFSHelper(startVertex);
        
        cout << "\n\n  Time Complexity: O(V + E)\n";
        cout << "  Space Complexity: O(V) for recursion stack\n";
        cout << "  Use Case: Cycle detection, topological sort\n";
    }
    
    void DFS_Iterative(int startVertex) {
        if(startVertex >= numVertices) {
            cout << "  ❌ Invalid start vertex!\n";
            return;
        }
        
        resetVisited();
        
        cout << "\n🔍 DFS (Iterative using Stack):\n";
        printSeparator();
        cout << "  Starting from vertex " << startVertex << "\n\n";
        
        stack<int> s;
        s.push(startVertex);
        
        cout << "  Traversal order: ";
        int step = 1;
        
        while(!s.empty()) {
            int current = s.top();
            s.pop();
            
            if(!visited[current]) {
                visited[current] = true;
                cout << current << " ";
                
                cout << "\n  Step " << step++ << ": Visiting " << current << "\n";
                cout << "  → Pushing neighbors to stack: ";
                
                bool hasNeighbors = false;
                for(int i = numVertices - 1; i >= 0; i--) {
                    if(adjMatrix[current][i] == 1 && !visited[i]) {
                        s.push(i);
                        cout << i << " ";
                        hasNeighbors = true;
                    }
                }
                
                if(!hasNeighbors) {
                    cout << "(none)";
                }
                cout << "\n\n";
            }
        }
        
        cout << "\n";
    }
    
    void visualize() {
        cout << "\n  Graph Visualization:\n\n";
        
        for(int i = 0; i < numVertices; i++) {
            cout << "  Vertex " << i << " → ";
            
            bool hasEdges = false;
            for(int j = 0; j < numVertices; j++) {
                if(adjMatrix[i][j] == 1) {
                    cout << j << " ";
                    hasEdges = true;
                }
            }
            
            if(!hasEdges) {
                cout << "(no edges)";
            }
            
            cout << "\n";
        }
        cout << "\n";
    }
    
    bool isConnected() {
        resetVisited();
        DFSHelper(0);
        
        for(int i = 0; i < numVertices; i++) {
            if(!visited[i]) {
                return false;
            }
        }
        return true;
    }
    
    int countEdges() {
        int count = 0;
        for(int i = 0; i < numVertices; i++) {
            for(int j = 0; j < numVertices; j++) {
                if(adjMatrix[i][j] == 1) {
                    count++;
                }
            }
        }
        return count / 2; // For undirected graph
    }
};

// ============== GRAPH (Adjacency List) ==============

class GraphList {
private:
    vector<int> adjList[MAX_VERTICES];
    int numVertices;
    bool visited[MAX_VERTICES];
    
    void resetVisited() {
        for(int i = 0; i < numVertices; i++) {
            visited[i] = false;
        }
    }
    
    void DFSHelper(int vertex) {
        visited[vertex] = true;
        cout << vertex << " ";
        
        for(int neighbor : adjList[vertex]) {
            if(!visited[neighbor]) {
                DFSHelper(neighbor);
            }
        }
    }
    
public:
    GraphList(int vertices) {
        numVertices = vertices;
        for(int i = 0; i < numVertices; i++) {
            visited[i] = false;
        }
    }
    
    void addEdge(int src, int dest, bool isDirected = false) {
        if(src >= numVertices || dest >= numVertices) {
            cout << "  ❌ Invalid vertex!\n";
            return;
        }
        
        adjList[src].push_back(dest);
        
        if(!isDirected) {
            adjList[dest].push_back(src);
        }
        
        cout << "  ✅ Edge added: " << src;
        cout << (isDirected ? " → " : " ↔ ");
        cout << dest << "\n";
    }
    
    void display() {
        cout << "\n  Adjacency List Representation:\n\n";
        
        for(int i = 0; i < numVertices; i++) {
            cout << "  [" << i << "] → ";
            
            if(adjList[i].empty()) {
                cout << "NULL";
            } else {
                for(int j = 0; j < adjList[i].size(); j++) {
                    cout << adjList[i][j];
                    if(j < adjList[i].size() - 1) {
                        cout << " → ";
                    }
                }
            }
            cout << "\n";
        }
        cout << "\n";
    }
    
    void BFS(int startVertex) {
        if(startVertex >= numVertices) {
            cout << "  ❌ Invalid start vertex!\n";
            return;
        }
        
        resetVisited();
        
        cout << "\n🔍 BFS Traversal (using Adjacency List):\n";
        printSeparator();
        cout << "  Starting from vertex " << startVertex << "\n";
        cout << "  Traversal order: ";
        
        queue<int> q;
        visited[startVertex] = true;
        q.push(startVertex);
        
        while(!q.empty()) {
            int current = q.front();
            q.pop();
            cout << current << " ";
            
            for(int neighbor : adjList[current]) {
                if(!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << "\n";
    }
    
    void DFS(int startVertex) {
        if(startVertex >= numVertices) {
            cout << "  ❌ Invalid start vertex!\n";
            return;
        }
        
        resetVisited();
        
        cout << "\n🔍 DFS Traversal (using Adjacency List):\n";
        printSeparator();
        cout << "  Starting from vertex " << startVertex << "\n";
        cout << "  Traversal order: ";
        
        DFSHelper(startVertex);
        cout << "\n";
    }
};

// ============== MENU FUNCTIONS ==============

void createSampleGraph(Graph& g) {
    cout << "\n  Creating sample graph...\n\n";
    cout << "  Graph structure:\n";
    cout << "        0\n";
    cout << "       / \\\n";
    cout << "      1   2\n";
    cout << "     / \\ / \\\n";
    cout << "    3   4   5\n\n";
    
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 4);
    g.addEdge(2, 5);
}

void graphApplications() {
    printHeader("GRAPH APPLICATIONS");
    
    cout << "\n🌐 REAL-WORLD APPLICATIONS:\n";
    printSeparator();
    
    cout << "\n  1. SOCIAL NETWORKS\n";
    cout << "     • Users as vertices, friendships as edges\n";
    cout << "     • Find mutual friends, suggest connections\n";
    cout << "     • BFS: Find degree of separation\n";
    
    cout << "\n  2. WEB CRAWLING\n";
    cout << "     • Web pages as vertices, hyperlinks as edges\n";
    cout << "     • DFS/BFS: Crawl and index web pages\n";
    
    cout << "\n  3. GPS & NAVIGATION\n";
    cout << "     • Locations as vertices, roads as edges\n";
    cout << "     • Shortest path algorithms (Dijkstra, A*)\n";
    
    cout << "\n  4. NETWORK ROUTING\n";
    cout << "     • Routers as vertices, connections as edges\n";
    cout << "     • Find optimal paths for data transmission\n";
    
    cout << "\n  5. DEPENDENCY RESOLUTION\n";
    cout << "     • Tasks/modules as vertices, dependencies as edges\n";
    cout << "     • Topological sort for build order\n";
    
    cout << "\n  6. RECOMMENDATION SYSTEMS\n";
    cout << "     • Users/items as vertices, preferences as edges\n";
    cout << "     • Find similar users or recommend items\n";
    
    cout << "\n  7. CIRCUIT DESIGN\n";
    cout << "     • Components as vertices, wires as edges\n";
    cout << "     • Detect cycles, optimize layout\n";
    
    cout << "\n📊 ALGORITHM COMPARISON:\n";
    printSeparator();
    cout << "\n  BFS vs DFS:\n";
    cout << "  ┌─────────────────┬──────────────┬──────────────┐\n";
    cout << "  │   Property      │     BFS      │     DFS      │\n";
    cout << "  ├─────────────────┼──────────────┼──────────────┤\n";
    cout << "  │ Data Structure  │    Queue     │    Stack     │\n";
    cout << "  │ Memory          │    O(V)      │    O(V)      │\n";
    cout << "  │ Shortest Path   │     Yes      │     No       │\n";
    cout << "  │ Complete Tree   │   Better     │   Worse      │\n";
    cout << "  │ Best For        │  Level-wise  │  Deep paths  │\n";
    cout << "  └─────────────────┴──────────────┴──────────────┘\n";
    
    pauseScreen();
}

void graphMenu() {
    int choice;
    
    while(true) {
        printHeader("GRAPHS - Vertices & Edges");
        cout << "\n  1. Graph using Adjacency Matrix\n";
        cout << "  2. Graph using Adjacency List\n";
        cout << "  3. BFS vs DFS Comparison\n";
        cout << "  4. Graph Applications\n";
        cout << "  5. Graph Terminology\n";
        cout << "  0. Back to Main Menu\n";
        printSeparator();
        cout << "  Enter choice: ";
        cin >> choice;
        
        switch(choice) {
            case 1: {
                int vertices;
                cout << "\n📥 Enter number of vertices: ";
                cin >> vertices;
                
                if(vertices > MAX_VERTICES) {
                    cout << "  ❌ Maximum " << MAX_VERTICES << " vertices allowed!\n";
                    pauseScreen();
                    break;
                }
                
                Graph g(vertices);
                int gChoice;
                
                while(true) {
                    printHeader("GRAPH - ADJACENCY MATRIX");
                    cout << "\n  1. Add Edge\n";
                    cout << "  2. Remove Edge\n";
                    cout << "  3. Display Matrix\n";
                    cout << "  4. Visualize Graph\n";
                    cout << "  5. BFS Traversal\n";
                    cout << "  6. DFS Traversal (Recursive)\n";
                    cout << "  7. DFS Traversal (Iterative)\n";
                    cout << "  8. Create Sample Graph\n";
                    cout << "  9. Graph Properties\n";
                    cout << "  0. Back\n";
                    printSeparator();
                    cout << "  Enter choice: ";
                    cin >> gChoice;
                    
                    if(gChoice == 0) break;
                    
                    int src, dest, start;
                    bool directed;
                    
                    switch(gChoice) {
                        case 1:
                            cout << "\n📥 Enter source vertex: ";
                            cin >> src;
                            cout << "📥 Enter destination vertex: ";
                            cin >> dest;
                            cout << "📥 Is directed? (1=Yes, 0=No): ";
                            cin >> directed;
                            g.addEdge(src, dest, directed);
                            pauseScreen();
                            break;
                            
                        case 2:
                            cout << "\n📥 Enter source vertex: ";
                            cin >> src;
                            cout << "📥 Enter destination vertex: ";
                            cin >> dest;
                            cout << "📥 Is directed? (1=Yes, 0=No): ";
                            cin >> directed;
                            g.removeEdge(src, dest, directed);
                            pauseScreen();
                            break;
                            
                        case 3:
                            g.displayMatrix();
                            pauseScreen();
                            break;
                            
                        case 4:
                            g.visualize();
                            pauseScreen();
                            break;
                            
                        case 5:
                            cout << "\n📥 Enter starting vertex: ";
                            cin >> start;
                            g.BFS(start);
                            pauseScreen();
                            break;
                            
                        case 6:
                            cout << "\n📥 Enter starting vertex: ";
                            cin >> start;
                            g.DFS(start);
                            pauseScreen();
                            break;
                            
                        case 7:
                            cout << "\n📥 Enter starting vertex: ";
                            cin >> start;
                            g.DFS_Iterative(start);
                            pauseScreen();
                            break;
                            
                        case 8:
                            createSampleGraph(g);
                            g.visualize();
                            pauseScreen();
                            break;
                            
                        case 9:
                            cout << "\n📊 Graph Properties:\n";
                            printSeparator();
                            cout << "  Vertices: " << vertices << "\n";
                            cout << "  Edges: " << g.countEdges() << "\n";
                            cout << "  Connected: " << (g.isConnected() ? "Yes" : "No") << "\n";
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
                int vertices;
                cout << "\n📥 Enter number of vertices: ";
                cin >> vertices;
                
                if(vertices > MAX_VERTICES) {
                    cout << "  ❌ Maximum " << MAX_VERTICES << " vertices allowed!\n";
                    pauseScreen();
                    break;
                }
                
                GraphList gl(vertices);
                int glChoice;
                
                while(true) {
                    printHeader("GRAPH - ADJACENCY LIST");
                    cout << "\n  1. Add Edge\n";
                    cout << "  2. Display List\n";
                    cout << "  3. BFS Traversal\n";
                    cout << "  4. DFS Traversal\n";
                    cout << "  5. Create Sample Graph\n";
                    cout << "  0. Back\n";
                    printSeparator();
                    cout << "  Enter choice: ";
                    cin >> glChoice;
                    
                    if(glChoice == 0) break;
                    
                    int src, dest, start;
                    bool directed;
                    
                    switch(glChoice) {
                        case 1:
                            cout << "\n📥 Enter source vertex: ";
                            cin >> src;
                            cout << "📥 Enter destination vertex: ";
                            cin >> dest;
                            cout << "📥 Is directed? (1=Yes, 0=No): ";
                            cin >> directed;
                            gl.addEdge(src, dest, directed);
                            pauseScreen();
                            break;
                            
                        case 2:
                            gl.display();
                            pauseScreen();
                            break;
                            
                        case 3:
                            cout << "\n📥 Enter starting vertex: ";
                            cin >> start;
                            gl.BFS(start);
                            pauseScreen();
                            break;
                            
                        case 4:
                            cout << "\n📥 Enter starting vertex: ";
                            cin >> start;
                            gl.DFS(start);
                            pauseScreen();
                            break;
                            
                        case 5:
                            cout << "\n  Creating sample graph...\n";
                            gl.addEdge(0, 1);
                            gl.addEdge(0, 2);
                            gl.addEdge(1, 3);
                            gl.addEdge(1, 4);
                            gl.addEdge(2, 4);
                            gl.addEdge(2, 5);
                            gl.display();
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
                printHeader("BFS vs DFS COMPARISON");
                
                cout << "\n  Creating demo graph for comparison...\n";
                Graph demo(6);
                createSampleGraph(demo);
                demo.visualize();
                
                demo.BFS(0);
                cout << "\n";
                printSeparator();
                
                demo.DFS(0);
                
                pauseScreen();
                break;
            }
            
            case 4:
                graphApplications();
                break;
                
            case 5: {
                printHeader("GRAPH TERMINOLOGY");
                
                cout << "\n📚 BASIC TERMS:\n";
                printSeparator();
                cout << "\n  • Vertex (Node): Fundamental unit\n";
                cout << "  • Edge: Connection between two vertices\n";
                cout << "  • Degree: Number of edges connected to vertex\n";
                cout << "  • Path: Sequence of vertices connected by edges\n";
                cout << "  • Cycle: Path that starts and ends at same vertex\n";
                cout << "  • Connected Graph: Path exists between any two vertices\n";
                
                cout << "\n🔢 GRAPH TYPES:\n";
                printSeparator();
                cout << "\n  1. Undirected: Edges have no direction (A ↔ B)\n";
                cout << "  2. Directed (Digraph): Edges have direction (A → B)\n";
                cout << "  3. Weighted: Edges have weights/costs\n";
                cout << "  4. Unweighted: All edges equal weight\n";
                cout << "  5. Cyclic: Contains at least one cycle\n";
                cout << "  6. Acyclic (DAG): No cycles\n";
                cout << "  7. Complete: Every vertex connected to every other\n";
                cout << "  8. Sparse: Few edges (E << V²)\n";
                cout << "  9. Dense: Many edges (E ≈ V²)\n";
                
                cout << "\n📊 REPRESENTATION COMPARISON:\n";
                printSeparator();
                cout << "\n  ┌────────────────┬─────────────┬─────────────┐\n";
                cout << "  │   Operation    │   Matrix    │    List     │\n";
                cout << "  ├────────────────┼─────────────┼─────────────┤\n";
                cout << "  │ Space          │    O(V²)    │   O(V+E)    │\n";
                cout << "  │ Add Edge       │    O(1)     │    O(1)     │\n";
                cout << "  │ Remove Edge    │    O(1)     │    O(V)     │\n";
                cout << "  │ Check Edge     │    O(1)     │    O(V)     │\n";
                cout << "  │ Get Neighbors  │    O(V)     │   O(deg)    │\n";
                cout << "  │ Best For       │ Dense Graph │Sparse Graph │\n";
                cout << "  └────────────────┴─────────────┴─────────────┘\n";
                
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
