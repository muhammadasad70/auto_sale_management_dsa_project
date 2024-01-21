#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <climits>
#include <queue>

using namespace std;

const int MAX_ORDERS = 100;  // Assuming a maximum of 100 orders, adjust as needed
const int INF = INT_MAX;

// Define a structure to represent an order
struct Order {
    int orderNumber;
    int quantityOrdered;
    float priceEach;
    // Add additional attributes as needed
};

// Define a class to represent the graph
class OrderGraph {
public:
    int numOrders;
    int adjacencyMatrix[MAX_ORDERS][MAX_ORDERS];

    OrderGraph(int n) : numOrders(n) {
        for (int i = 0; i < numOrders; ++i) {
            for (int j = 0; j < numOrders; ++j) {
                adjacencyMatrix[i][j] = INF;
            }
        }
    }

    void addEdge(int u, int v, int weight) {
        adjacencyMatrix[u][v] = weight;
        adjacencyMatrix[v][u] = weight;  // Assuming an undirected graph
    }

    void primMST() {
        int parent[MAX_ORDERS];
        int key[MAX_ORDERS];
        bool inMST[MAX_ORDERS];

        for (int i = 0; i < numOrders; ++i) {
            key[i] = INF;
            inMST[i] = false;
        }

        key[0] = 0;  // Start with the first order

        for (int count = 0; count < numOrders - 1; ++count) {
            int u = minKey(key, inMST);
            inMST[u] = true;

            for (int v = 0; v < numOrders; ++v) {
                if (!inMST[v] && adjacencyMatrix[u][v] < key[v]) {
                    parent[v] = u;
                    key[v] = adjacencyMatrix[u][v];
                }
            }
        }

        printMST(parent);
    }

    void dijkstra(int start) {
        int dist[MAX_ORDERS];
        bool visited[MAX_ORDERS];

        for (int i = 0; i < numOrders; ++i) {
            dist[i] = INF;
            visited[i] = false;
        }

        dist[start] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
        pq.push(make_pair(0, start));

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            for (int v = 0; v < numOrders; ++v) {
                int weight = adjacencyMatrix[u][v];
                if (!visited[v] && dist[v] > dist[u] + weight) {
                    dist[v] = dist[u] + weight;
                    pq.push(make_pair(dist[v], v));
                }
            }
        }

        printDijkstra(start, dist);
    }

private:
    int minKey(const int key[], const bool inMST[]) {
        int min = INF, min_index = -1;

        for (int v = 0; v < numOrders; ++v) {
            if (!inMST[v] && key[v] < min) {
                min = key[v];
                min_index = v;
            }
        }

        return min_index;
    }

    void printMST(const int parent[]) {
        cout << "Minimum Spanning Tree:\n";
        for (int v = 1; v < numOrders; ++v) {
            cout << "Edge: " << parent[v] << " - " << v << "  Weight: " << adjacencyMatrix[parent[v]][v] << "\n";
        }
    }

    void printDijkstra(int start, const int dist[]) {
        cout << "Shortest Paths from Order " << start << " (Dijkstra's Algorithm):\n";
        for (int i = 0; i < numOrders; ++i) {
            cout << "Order " << start << " to Order " << i << ": Distance = " << dist[i] << "\n";
        }
    }
};

// Function to read data from a CSV file and store it in an array of orders
int readDataFromCSV(const string& filename, Order orders[]) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return 0;
    }

    int orderCount = 0;
    string line;
    while (getline(file, line) && orderCount < MAX_ORDERS) {
        istringstream iss(line);
        string token;

        try {
            getline(iss, token, ',');
            orders[orderCount].orderNumber = stoi(token);

            getline(iss, token, ',');
            orders[orderCount].quantityOrdered = stoi(token);

            getline(iss, token, ',');
            orders[orderCount].priceEach = stof(token);
            // ... read other attributes

            orderCount++;
        } catch (const std::exception& e) {
            cerr << "Error converting to numeric value: " << e.what() << endl;
            // Handle the error as needed
        }
    }

    file.close();
    return orderCount;
}
int main() {
    // Replace "your_dataset.csv" with the actual file name
    string filename = "/Users/masad/Desktop/data_Structure_calss/project/complete_project/Auto Sales data.csv";
    Order orders[MAX_ORDERS];
    int numOrders = readDataFromCSV(filename, orders);

    OrderGraph orderGraph(numOrders);

    // Populate the graph with edges based on the price differences between orders
    for (int i = 0; i < numOrders; ++i) {
        for (int j = i + 1; j < numOrders; ++j) {
            int weight = abs(orders[i].priceEach - orders[j].priceEach);
            orderGraph.addEdge(i, j, weight);
        }
    }

    int option;
    do {
        cout << "Choose an option:\n";
        cout << "1. Run Prim's algorithm\n";
        cout << "2. Run Dijkstra's algorithm from Order 0\n";
        cout << "0. Exit\n";
        cout << "Enter your choice (0, 1, or 2): ";
        cin >> option;

        switch (option) {
            case 1:
                // Run Prim's algorithm and print the Minimum Spanning Tree
                orderGraph.primMST();
                break;
            case 2:
                // Run Dijkstra's algorithm from Order 0
                orderGraph.dijkstra(0);
                break;
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid option. Please choose 0, 1, or 2.\n";
        }
    } while (option != 0);

    return 0;
}

