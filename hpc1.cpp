#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <omp.h>

using namespace std;

const int MAX_THREADS = 16; // Maximum number of threads to be used

// Graph class to represent an undirected graph
class Graph {
    int V; // number of vertices
    vector<int>* adj; // adjacency list
public:
    Graph(int V);
    void addEdge(int v, int w);
    void bfs(int start);
    void dfs(int start);
};

// Constructor to initialize a graph with V vertices
Graph::Graph(int V) {
    this->V = V;
    adj = new vector<int>[V];
}

// Function to add an edge between vertices v and w
void Graph::addEdge(int v, int w) {
    adj[v].push_back(w);
    adj[w].push_back(v);
}

// Breadth First Search algorithm
void Graph::bfs(int start) {
    // Mark all the vertices as not visited
    bool* visited = new bool[V];
    for(int i = 0; i < V; i++)
        visited[i] = false;

    // Create a queue for BFS
    queue<int> q;

    // Mark the current node as visited and enqueue it
    visited[start] = true;
    q.push(start);

    while(!q.empty()) {
        // Dequeue a vertex from queue and print it
        int s;
        #pragma omp critical
        {
            s = q.front();
            q.pop();
        }

        cout << s << " ";

        // Get all adjacent vertices of the dequeued vertex s.
        // If an adjacent has not been visited, then mark it visited and enqueue it
        #pragma omp parallel for num_threads(MAX_THREADS)
        for(int i = 0; i < adj[s].size(); i++) {
            int v = adj[s][i];
            if(!visited[v]) {
                #pragma omp critical
                {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
    }

    delete[] visited;
}
// Depth First Search algorithm
void Graph::dfs(int start) {
    // Mark all the vertices as not visited
    bool* visited = new bool[V];
    for(int i = 0; i < V; i++)
        visited[i] = false;

    // Create a stack for DFS
    stack<int> s;

    // Push the current source node
    s.push(start);

    while(!s.empty()) {
        // Pop a vertex from stack and print it
        int v;
        #pragma omp critical
        {
            v = s.top();
            s.pop();
        }

        cout << v << " ";

        // Print if not visited and mark as visited
        if(!visited[v]) {
            #pragma omp critical
            {
                visited[v] = true;
            }
        }

        // Get all adjacent vertices of the popped vertex v.
        // If an adjacent has not been visited, then push it to the stack in reverse order
        #pragma omp parallel for num_threads(MAX_THREADS)
        for(int i = adj[v].size() - 1; i >= 0; i--) {
            int u = adj[v][i];
            if(!visited[u]) {
                #pragma omp critical
                {
                    s.push(u);
                }
            }
        }
    }

    delete[] visited;
}


int main() {
    Graph g(7); // create a graph with 7 vertices
    g.addEdge(0, 1); // root node
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);
    g.addEdge(2, 6);


    // Call BFS and display complete traversal route
cout << "BFS Traversal: ";
g.bfs(0);
cout << endl;

// Call DFS and display complete traversal route
cout << "DFS Traversal: ";
g.dfs(0);
cout << endl;

return 0;
}
