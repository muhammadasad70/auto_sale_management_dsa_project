#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

struct str {
    int ordernumber;
    int quantityordered;
    string status;
    double sales;
    string product_type;
    string customer_Name;
    string address;
    string city;
    string phoneNo;

    str* next;
};

str* first = NULL;

struct BSTNode {
    str* data;
    BSTNode* left;
    BSTNode* right;
};

BSTNode* root = NULL;

void addNode(int order, int quantity, const string& status, double sale, const string& product, const string& customer, const string& addr, const string& c, const string& phone) {
    str* newNode = new str();
    newNode->ordernumber = order;
    newNode->quantityordered = quantity;
    newNode->status = status;
    newNode->sales = sale;
    newNode->product_type = product;
    newNode->customer_Name = customer;
    newNode->address = addr;
    newNode->city = c;
    newNode->phoneNo = phone;
    newNode->next = NULL;

    if (first == NULL) {
        first = newNode;
    } else {
        str* temp = first;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}
void displayBST(BSTNode* root) {
    if (root != NULL) {
        displayBST(root->left);
        cout << root->data->ordernumber << "\t";
        cout << setw(15) << left << root->data->quantityordered;
        cout << setw(27) << left << root->data->status;
        cout << setw(19) << left << root->data->sales;
        cout << setw(20) << left << root->data->product_type;
        cout << setw(30) << left << root->data->customer_Name;
        cout << setw(30) << left << root->data->address;
        cout << setw(25) << left << root->data->city;
        cout << setw(15) << left << root->data->phoneNo << endl;
        displayBST(root->right);
    }
}

BSTNode* insertBST(BSTNode* root, str* data) {
    if (root == NULL) {
        BSTNode* newNode = new BSTNode;
        newNode->data = data;
        newNode->left = newNode->right = NULL;
        return newNode;
    }

    if (data->quantityordered < root->data->quantityordered) {
        root->left = insertBST(root->left, data);
    } else {
        root->right = insertBST(root->right, data);
    }

    return root;
}

void displayByQuantityRange(BSTNode* root, int minQuantity, int maxQuantity) {
    if (root != NULL) {
        displayByQuantityRange(root->left, minQuantity, maxQuantity);
        if (root->data->quantityordered >= minQuantity && root->data->quantityordered <= maxQuantity) {
            cout << root->data->ordernumber << " " << root->data->quantityordered << " " << root->data->status << endl;
        }
        displayByQuantityRange(root->right, minQuantity, maxQuantity);
    }
}

BSTNode* removeOrder(BSTNode* root, int orderNumber, str*& removedData) {
    if (root == NULL) {
        return root;
    }

    if (orderNumber < root->data->ordernumber) {
        root->left = removeOrder(root->left, orderNumber, removedData);
    } else if (orderNumber > root->data->ordernumber) {
        root->right = removeOrder(root->right, orderNumber, removedData);
    } else {
        removedData = root->data;

        if (root->left == NULL) {
            BSTNode* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == NULL) {
            BSTNode* temp = root->left;
            delete root;
            return temp;
        }

        BSTNode* temp = root->right;
        while (temp->left != NULL) {
            temp = temp->left;
        }
        root->data = temp->data;
        root->right = removeOrder(root->right, temp->data->ordernumber, removedData);
    }
    return root;
}



void insertion() {
    ifstream file1;
    file1.open("/Users/masad/Desktop/data_Structure_calss/project/complete_project/Auto Sales data.csv");
    if (!file1.is_open()) {
        cout << "Error opening file." << endl;
        return;
    }
    string line, word;
    vector<string> eachLineData;
    int noOfLines = 0;

    while (!file1.eof()) {
        if (noOfLines != 0) {
            getline(file1, line);
            stringstream strSplit(line);
            while (getline(strSplit, word, ',')) {
                eachLineData.push_back(word);
            }
            if (eachLineData.size() >= 10) {
                stringstream s0(eachLineData[0]);
                stringstream s1(eachLineData[1]);
                stringstream s4(eachLineData[4]);

                int ordernumberTemp;
                s0 >> ordernumberTemp;
                int quantityorderTemp;
                s1 >> quantityorderTemp;
                int salesTemp;
                s4 >> salesTemp;

                str* curr = new str();
                curr->ordernumber = ordernumberTemp;
                curr->quantityordered = quantityorderTemp;
                curr->status = eachLineData[7];
                curr->sales = salesTemp;
                curr->product_type = eachLineData[8];
                curr->customer_Name = eachLineData[11];
                curr->address = eachLineData[13];
                curr->city = eachLineData[14];
                curr->phoneNo = eachLineData[12];

                root = insertBST(root, curr); // Build BST during insertion
            }
            eachLineData.clear();
        }
        noOfLines++;
    }
    file1.close();
}
void displayMenu() {
    cout << "\n************ Menu ************" << endl;
    cout << "1. Display Full Dataset" << endl;
    cout << "2. Display Orders within Quantity Range 10 to 20" << endl;
    cout << "3. Remove Order Number 5" << endl;
    cout << "4. Displaying Full BST Dataset after removing Order Number 5" << endl;
    cout << "5.Exit."<<endl;
    cout << "*******************************" << endl;
    cout << "Enter your choice: ";
}

void menuOperations() {
    str* removedData = NULL;
    int choice;

    do {
        displayMenu();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                cout << "\nDisplaying Full Dataset:" << endl;
                displayBST(root);
                break;
            case 2:
                cout << "\nDisplaying Orders within Quantity Range 10 to 20:" << endl;
                displayByQuantityRange(root, 10, 20);
                break;
            case 3:
                cout << "\nRemoving Order Number 5:" << endl;
                root = removeOrder(root, 5, removedData);

                if (removedData != NULL) {
                    cout << "\nRemoved Data:" << endl;
                    cout << removedData->ordernumber << "\t";
                    cout << setw(15) << left << removedData->quantityordered;
                    cout << setw(27) << left << removedData->status;
                    cout << setw(19) << left << removedData->sales;
                    cout << setw(20) << left << removedData->product_type;
                    cout << setw(30) << left << removedData->customer_Name;
                    cout << setw(30) << left << removedData->address;
                    cout << setw(25) << left << removedData->city;
                    cout << setw(15) << left << removedData->phoneNo << endl;
                }
                break;
            case 4:
                cout << "\nDisplaying Full BST Dataset after removing Order Number 5:" << endl;
                displayBST(root);
                break;
            case 5:
                cout<<"Exiting...."<<endl;
                break;
            default:
                cout << "Invalid choice! Please enter a valid option." << endl;
                break;
        }
    } while (choice != 5);
}

int main() {
    insertion();
    menuOperations();
    return 0;
}

