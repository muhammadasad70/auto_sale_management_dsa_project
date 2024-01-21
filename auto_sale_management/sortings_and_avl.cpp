#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <climits>
#include <algorithm>

using namespace std;

const int MAX_ORDERS = 1000;  // Assuming a maximum of 1000 orders, adjust as needed

// Define a structure to represent an order
struct Order {
    int orderNumber;
    int quantityOrdered;
    float priceEach;
    // Add additional attributes as needed
};

// Function to read data from a CSV file and store it in an array of orders
int readDataFromCSV(const string& filename, Order orders[]) {
    ifstream file(filename.c_str());
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

// Function to print orders
void printOrders(const Order orders[], int orderCount) {
    for (int i = 0; i < orderCount; ++i) {
        const Order& order = orders[i];
        cout << "Order Number: " << order.orderNumber << " Quantity: " << order.quantityOrdered
             << " Price Each: " << order.priceEach << "\n";
    }
}

// Bubble Sort
void bubbleSort(Order orders[], int orderCount) {
    for (int i = 0; i < orderCount - 1; ++i) {
        for (int j = 0; j < orderCount - i - 1; ++j) {
            if (orders[j].priceEach > orders[j + 1].priceEach) {
                swap(orders[j], orders[j + 1]);
            }
        }
    }
}

// Merge Sort
void merge(Order orders[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    Order L[n1], R[n2];

    for (int i = 0; i < n1; ++i) {
        L[i] = orders[l + i];
    }
    for (int j = 0; j < n2; ++j) {
        R[j] = orders[m + 1 + j];
    }

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i].priceEach <= R[j].priceEach) {
            orders[k++] = L[i++];
        } else {
            orders[k++] = R[j++];
        }
    }

    while (i < n1) {
        orders[k++] = L[i++];
    }

    while (j < n2) {
        orders[k++] = R[j++];
    }
}

void mergeSort(Order orders[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(orders, l, m);
        mergeSort(orders, m + 1, r);
        merge(orders, l, m, r);
    }
}

// Selection Sort
void selectionSort(Order orders[], int orderCount) {
    for (int i = 0; i < orderCount - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < orderCount; ++j) {
            if (orders[j].priceEach < orders[minIndex].priceEach) {
                minIndex = j;
            }
        }
        swap(orders[i], orders[minIndex]);
    }
}

// Hashing (Simple example, can be improved based on specific requirements)
class HashTable {
public:
    explicit HashTable(int size) : table(new Order*[size]), size(size) {
        for (int i = 0; i < size; ++i) {
            table[i] = nullptr;
        }
    }

    void insert(const Order& order) {
        int index = hashFunction(order.orderNumber);
        if (table[index] == nullptr) {
            table[index] = new Order(order);
        } else {
            // Handle collision as needed
            // For simplicity, you might want to use a different index
        }
    }

    void print() {
        for (int i = 0; i < size; ++i) {
            cout << "Bucket " << i << ": ";
            if (table[i] != nullptr) {
                cout << table[i]->orderNumber << " ";
            }
            cout << endl;
        }
    }

    void clear() {
        // Implementation of clear function
        // You may need to traverse the table and clear each bucket
        // ...
    }

    ~HashTable() {
        for (int i = 0; i < size; ++i) {
            delete table[i];
        }
        delete[] table;
    }

private:
    Order** table;
    int size;

    int hashFunction(int key) {
        return key % size;
    }
};

// AVL Tree (Simple example, can be improved based on specific requirements)
struct AVLNode {
    Order order;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(const Order& order) : order(order), left(nullptr), right(nullptr), height(1) {}
};

int getHeight(AVLNode* node) {
    return (node != nullptr) ? node->height : 0;
}

int getBalance(AVLNode* node) {
    return (node != nullptr) ? getHeight(node->left) - getHeight(node->right) : 0;
}

AVLNode* rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

AVLNode* rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

AVLNode* insertAVL(AVLNode* node, const Order& order) {
    if (node == nullptr) {
        return new AVLNode(order);
    }

    if (order.priceEach < node->order.priceEach) {
        node->left = insertAVL(node->left, order);
    } else if (order.priceEach > node->order.priceEach) {
        node->right = insertAVL(node->right, order);
    } else {
        // Duplicate price, handle as needed
        return node;
    }

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    int balance = getBalance(node);

    // Left Heavy
    if (balance > 1) {
        if (order.priceEach < node->left->order.priceEach) {
            // Left-Left Case
            return rotateRight(node);
        } else {
            // Left-Right Case
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
    }

    // Right Heavy
    if (balance < -1) {
        if (order.priceEach > node->right->order.priceEach) {
            // Right-Right Case
            return rotateLeft(node);
        } else {
            // Right-Left Case
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
    }

    return node;
}

void printInOrder(AVLNode* root) {
    if (root != nullptr) {
        printInOrder(root->left);
        cout << root->order.priceEach << " ";
        printInOrder(root->right);
    }
}

// Function to display the menu and get user's choice
int displayMenu() {
    cout << "\nMenu:\n";
    cout << "1. Bubble Sort\n";
    cout << "2. Merge Sort\n";
    cout << "3. Selection Sort\n";
    cout << "4. Hashing\n";
    cout << "5. AVL Tree\n";
    cout << "0. Exit\n";
    cout << "Enter your choice: ";

    int choice;
    cin >> choice;
    return choice;
}

// Function to clear AVL tree
void clearAVL(AVLNode* node) {
    if (node != nullptr) {
        clearAVL(node->left);
        clearAVL(node->right);
        delete node;
    }
}

int main() {
    // Replace "your_dataset.csv" with the actual file name
    string filename = "/Users/masad/Desktop/data_Structure_calss/project/complete_project/Auto Sales data.csv";
    Order orders[MAX_ORDERS];
    int numOrders = readDataFromCSV(filename, orders);

    int choice;
    HashTable hashTable(10); // Declare hashTable outside the switch statement
    AVLNode* avlRoot = nullptr; // Declare avlRoot outside the switch statement

    do {
        choice = displayMenu();

        switch (choice) {
            case 1:
                cout << "Before Bubble Sort:\n";
                printOrders(orders, numOrders);
                bubbleSort(orders, numOrders);
                cout << "\nAfter Bubble Sort:\n";
                printOrders(orders, numOrders);
                break;
            case 2:
                cout << "Before Merge Sort:\n";
                printOrders(orders, numOrders);
                mergeSort(orders, 0, numOrders - 1);
                cout << "\nAfter Merge Sort:\n";
                printOrders(orders, numOrders);
                break;
            case 3:
                cout << "Before Selection Sort:\n";
                printOrders(orders, numOrders);
                selectionSort(orders, numOrders);
                cout << "\nAfter Selection Sort:\n";
                printOrders(orders, numOrders);
                break;
            case 4:
                // Hashing
                hashTable.clear(); // Clear the hashTable before reusing it
                for (int i = 0; i < numOrders; ++i) {
                    hashTable.insert(orders[i]);
                }
                cout << "\nHash Table:\n";
                hashTable.print();
                break;
            case 5:
                // AVL Tree
                if (avlRoot != nullptr) {
                    // Clear the AVL tree before reusing it
                    clearAVL(avlRoot);
                }
                avlRoot = nullptr;
                for (int i = 0; i < numOrders; ++i) {
                    avlRoot = insertAVL(avlRoot, orders[i]);
                }
                cout << "\nAVL Tree (In-order traversal):\n";
                printInOrder(avlRoot);
                cout << endl;
                break;
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}