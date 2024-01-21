#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stack>
using namespace std;

struct Order {
    int ordernumber;
    int quantityordered;
    string status;
    double sales;
    string product_type;
    string customer_Name;
    string address;
    string city;
    string phoneNo;
    Order* next;

};

void printOrder(const Order& order) {
    cout << "Order Number: " << order.ordernumber << endl;
    cout << "Quantity Ordered: " << order.quantityordered << endl;
    cout << "Status: " << order.status << endl;
    cout << "Sales: " << order.sales << endl;
    cout << "Product Type: " << order.product_type << endl;
    cout << "Customer Name: " << order.customer_Name << endl;
    cout << "Address: " << order.address << endl;
    cout << "City: " << order.city << endl;
    cout << "Phone Number: " << order.phoneNo << endl;
    cout << "-----------------------------" << endl;
}

void printOrderHistory(stack<Order>& orderHistory) {
    if (orderHistory.empty()) {
        cout << "Order history is empty." << endl;
        return;
    }

    cout << "Order History:" << endl;
    cout << "-----------------------------" << endl;

    stack<Order> tempStack = orderHistory;
    while (!tempStack.empty()) {
        printOrder(tempStack.top());
        tempStack.pop();
    }
}

void insertion(stack<Order>& orderHistory) {
    ifstream file1;
    file1.open("/Users/masad/Desktop/data_Structure_calss/project/complete_project/Auto Sales data.csv");
    if (!file1.is_open()) {
        cout << "Error opening file." << endl;
        return;
    }

    string line, word;
    vector<string> eachLineData;
    int noOfLines = 0;

    while (getline(file1, line)) {
        stringstream strSplit(line);

        while (getline(strSplit, word, ',')) {
            eachLineData.push_back(word);
        }

        if (eachLineData.size() >= 10) {
            Order newOrder;
            stringstream s0(eachLineData[0]);
            stringstream s1(eachLineData[1]);
            stringstream s4(eachLineData[4]);

            s0 >> newOrder.ordernumber;
            s1 >> newOrder.quantityordered;
            s4 >> newOrder.sales;

            newOrder.status = eachLineData[7];
            newOrder.product_type = eachLineData[8];
            newOrder.customer_Name = eachLineData[11];
            newOrder.address = eachLineData[13];
            newOrder.city = eachLineData[14];
            newOrder.phoneNo = eachLineData[12];

            orderHistory.push(newOrder);
        }
        eachLineData.clear();
        noOfLines++;
    }

    file1.close();

    cout << "\nOrder history after insertion:\n";
    printOrderHistory(orderHistory);
}

void addToOrderHistory(stack<Order>& orderHistory, const Order& newOrder) {
    orderHistory.push(newOrder);
    cout << "\nOrder added successfully!\n";
    printOrderHistory(orderHistory);
}

void undoLastOrderEntry(stack<Order>& orderHistory) {
    if (!orderHistory.empty()) {
        orderHistory.pop();
        cout << "Last order entry undone.\n";
        printOrderHistory(orderHistory);
    } else {
        cout << "No actions to undo.\n";
    }
}

Order inputNewOrder() {
    Order newOrder;

    cout << "Enter Order Number: ";
    cin >> newOrder.ordernumber;

    cout << "Enter Quantity Ordered: ";
    cin >> newOrder.quantityordered;

    cout << "Enter Status: ";
    cin.ignore();
    getline(cin, newOrder.status);

    cout << "Enter Sales: ";
    cin >> newOrder.sales;

    cout << "Enter Product Type: ";
    cin.ignore();
    getline(cin, newOrder.product_type);

    cout << "Enter Customer Name: ";
    getline(cin, newOrder.customer_Name);

    cout << "Enter Address: ";
    getline(cin, newOrder.address);

    cout << "Enter City: ";
    getline(cin, newOrder.city);

    cout << "Enter Phone Number: ";
    getline(cin, newOrder.phoneNo);

    return newOrder;
}

int main() {
    cout << "\t\t\t\t\t\t\t\t\t\t\t\tWelcome to our code";
    cout << "\n************";

    stack<Order> orderHistory;
    insertion(orderHistory);

    int choice;
    do {
        cout << "\n\n\t\t\t\t\t\t\t\t\t\tFollowing is our Dataset about orders placed\n\n";
        cout << "1. Display Order History\n";
        cout << "2. Add a New Order\n";
        cout << "3. Undo Last Order Entry\n";
        cout << "4. Exit\n\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                printOrderHistory(orderHistory);
                break;
            case 2: {
                Order newOrder = inputNewOrder();
                addToOrderHistory(orderHistory, newOrder);
                break;
            }
            case 3:
                undoLastOrderEntry(orderHistory);
                break;
            case 4:
                cout << "\nExiting...\n";
                break;
            default:
                cout << "\nInvalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}


