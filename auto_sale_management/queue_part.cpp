#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

struct str
{
    
    int ordernumber;
    int quantityordered;
    int daysleft;
    string status;
    double sales;
    string product_type;
    string customer_Name;
    string address;
    string city;
    string phoneNo;

    str* next;
    str* prev;
};

str* first=NULL;
str* last=NULL;

class PriorityQueue
{
public:
    str* front;
    str *frontSalesAsc;
    str *frontQuantityDesc;

public:
     PriorityQueue() : front(nullptr), frontSalesAsc(nullptr), frontQuantityDesc(nullptr) {}

    void enqueue(str* order)
    {
        str* newNode = new str(*order);
        if (front == nullptr || order->daysleft < front->daysleft)
        {
            newNode->next = front;
            front = newNode;
        }
        else
        {
            str* curr = front;
            while (curr->next != nullptr && order->daysleft >= curr->next->daysleft)
            {
                curr = curr->next;
            }
            newNode->next = curr->next;
            curr->next = newNode;
        }
    }
    

    str* dequeue()
    {
        if (isEmpty())
        {
            return nullptr;
        }

        str* removedNode = front->next;
        front->next = front->next->next;
        removedNode->next = nullptr;
        return removedNode;
    }


    bool isEmpty() const
    {
        return front == nullptr;
    }


    void displayQueue()
    {
        str* curr = front;
        while (curr != nullptr)
        {
            cout << "Order Number: " << curr->ordernumber << "\tDays Left: " << curr->daysleft << endl;
            curr = curr->next;
        }
        cout << "-------------------------" << endl;
    }

    void enqueueSalesAsc(str *order)
    {
        str *newNode = new str(*order);
        if (frontSalesAsc == nullptr || order->sales < frontSalesAsc->sales)
        {
            newNode->next = frontSalesAsc;
            frontSalesAsc = newNode;
        }
        else
        {
            str *curr = frontSalesAsc;
            while (curr->next != nullptr && order->sales >= curr->next->sales)
            {
                curr = curr->next;
            }
            newNode->next = curr->next;
            curr->next = newNode;
        }
    }


    void enqueueQuantityDesc(str *order)
    {
        str *newNode = new str(*order);
        if (frontQuantityDesc == nullptr || order->quantityordered > frontQuantityDesc->quantityordered)
        {
            newNode->next = frontQuantityDesc;
            frontQuantityDesc = newNode;
        }
        else
        {
            str *curr = frontQuantityDesc;
            while (curr->next != nullptr && order->quantityordered <= curr->next->quantityordered)
            {
                curr = curr->next;
            }
            newNode->next = curr->next;
            curr->next = newNode;
        }
    }


    str *dequeueSalesAsc()
    {
        if (isEmptySalesAsc())
        {
            return nullptr;
        }

        str *removedNode = frontSalesAsc;
        frontSalesAsc = frontSalesAsc->next;
        removedNode->next = nullptr;
        return removedNode;
    }

    str *dequeueQuantityDesc()
    {
        if (isEmptyQuantityDesc())
        {
            return nullptr;
        }

        str *removedNode = frontQuantityDesc;
        frontQuantityDesc = frontQuantityDesc->next;
        removedNode->next = nullptr;
        return removedNode;
    }
    bool isEmptySalesAsc() const
    {
        return frontSalesAsc == nullptr;
    }

    bool isEmptyQuantityDesc() const
    {
        return frontQuantityDesc == nullptr;
    }

    void displayQueueSalesAsc()
    {
        str *curr = frontSalesAsc;
        while (curr != nullptr)
        {
            cout << "Order Number: " << curr->ordernumber << "\tSales: " << curr->sales << endl;
            curr = curr->next;
        }
        cout << "-------------------------" << endl;
    }

    // Function to display the contents of the priority queue for quantity
    void displayQueueQuantityDesc()
    {
        str *curr = frontQuantityDesc;
        while (curr != nullptr)
        {
            cout << "Order Number: " << curr->ordernumber << "\tQuantity Ordered: " << curr->quantityordered << endl;
            curr = curr->next;
        }
        cout << "-------------------------" << endl;
    }
};

PriorityQueue priorityQueue;

void insertion(){
    ifstream file1;
    
    file1.open("/Users/masad/Desktop/data_Structure_calss/project/complete_project/Auto Sales data.csv");
    
    if (!file1.is_open()) {
        cout << "Error opening file." << endl;
        return;
    }
    string line, word;
    vector<string> eachLineData;
    int noOfLines=0;

    while(!file1.eof()){
       
        if(noOfLines!=0){
               
                getline(file1,line);
                stringstream strSplit(line); 
                
                while(getline(strSplit,word,',')){
                   
                eachLineData.push_back(word);
                }
        if (eachLineData.size() >= 10) {
                
                stringstream s0(eachLineData[0]); 
                stringstream s1(eachLineData[1]);
                stringstream s4(eachLineData[4]);
                stringstream s5(eachLineData[6]);

                
                int ordernumberTemp;
                s0>>ordernumberTemp;
                int quantityorderTemp;
                s1>>quantityorderTemp;
                int salesTemp;
                s4>> salesTemp;
                int daysleftTemp;
                s5>> daysleftTemp;

                
                str* curr=new str();
                curr->ordernumber=ordernumberTemp;
                curr->quantityordered=quantityorderTemp;
                curr->status=eachLineData[7];
                curr->daysleft = daysleftTemp;
                curr->sales=salesTemp;
                curr->product_type=eachLineData[8];
                curr->customer_Name=eachLineData[11];
                curr->address=eachLineData[13];
                curr->city=eachLineData[14];
                curr->phoneNo=eachLineData[12];
                priorityQueue.enqueue(curr);
                priorityQueue.enqueueSalesAsc(curr);
                priorityQueue.enqueueQuantityDesc(curr);

                if(first==NULL){
                    first=last=curr;
                }else{
                    last->next=curr;   
                    last=curr;
                    last->next=NULL;
                };
        }
                eachLineData.clear();
              
        }
        noOfLines++;
        
    }
}
void displayMaxQuantityMinSalesCustomer()
{
    // Check if the quantity queue is not empty
    while (!priorityQueue.isEmptyQuantityDesc())
    {
        // Dequeue the order with maximum quantity
        str *maxQuantityOrder = priorityQueue.dequeueQuantityDesc();

        // Find the order with the minimum sales without dequeuing
        str *minSalesOrder = priorityQueue.frontSalesAsc->next;

        if (maxQuantityOrder != nullptr && minSalesOrder != nullptr &&
            maxQuantityOrder->ordernumber == minSalesOrder->ordernumber)
        {
            // Display the customer details
            cout<< maxQuantityOrder->customer_Name <<" orders "<< maxQuantityOrder->quantityordered << " in just "<<maxQuantityOrder->sales<<" $ amount "<<endl;
            cout << "Order Number: " << maxQuantityOrder->ordernumber << endl;
            cout << "Total Price :"<<maxQuantityOrder->sales<<endl;
            cout << "Quantity ordered :"<<maxQuantityOrder->quantityordered<<endl;
            cout << "Customer Name: " << maxQuantityOrder->customer_Name << endl;
            cout << "Address: " << maxQuantityOrder->address << endl;
            cout << "City: " << maxQuantityOrder->city << endl;
            cout << "Phone Number: " << maxQuantityOrder->phoneNo << endl;
            cout << "-------------------------" << endl;
        }
        
    }

    // If the quantity queue becomes empty, inform the user
    if (priorityQueue.isEmptyQuantityDesc())
    {
        cout << "\nNo more orders in descending order based on quantity.\n";
    }
}
void displayFull(){
    str* curr=first->next;
    while(curr!=NULL){
        
        
        cout << curr->ordernumber <<"\t";
        cout << setw(15) << left << curr->quantityordered;
        cout << setw(27) << left << curr->status;
        cout << setw(19) << left << curr->sales;
        cout << setw(19) << left << curr->daysleft;
        cout << setw(20) << left << curr->product_type;
        cout << setw(30) << left << curr->customer_Name;
        cout << setw(30) << left << curr->address;
        cout << setw(25) << left << curr->city;
        cout << setw(15) << left << curr->phoneNo<<endl;
        
         


        curr=curr->next;
    }

}

int main()
{
    cout << "\t\t\t\t\t\t\t\t\t\t\t\tWelcome to our code";
    cout << "\n************";

    int choice;
    str *recentProduct = nullptr; // Declare the variable outside the switch

    do
    {
        cout << "\n\n\t\t\t\t\t\t\t\t\t\tMain Menu\n";
        cout << "1. Load Data from CSV\n";
        cout << "2. Display Orders in Ascending Order based on Days Left\n";
        cout << "3. Dequeue Most Recent Product Going to Be Delivered\n";
        cout << "4. Display Orders in Ascending Order based on Sales\n";
        cout << "5. Display Orders in Descending Order based on Quantity\n";
        cout << "6. Display customer having maximum profit\n";
        cout << "7. Exit\n";
        cout << "Enter your choice (1-4): ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            insertion();
            break;

        case 2:
            cout << "\nOrders in ascending order based on days left:" << endl;
            priorityQueue.displayQueue();
            break;

        case 3:
            cout << "\nMost Recent Product Going to Be Delivered:" << endl;
            // Dequeue the most recent product going to be delivered
            recentProduct = priorityQueue.dequeue();
            if (recentProduct != nullptr)
            {
                cout << "Order Number: " << recentProduct->ordernumber << "\tDays Left: " << recentProduct->daysleft << endl;
                
            }
            else
            {
                cout << "No recent product available." << endl;
            }
            break;

         case 4:
            cout << "\nOrders in ascending order based on sales:" << endl;
            priorityQueue.displayQueueSalesAsc();
            break;

        case 5:
            cout << "\nOrders in descending order based on quantity ordered:" << endl;
            priorityQueue.displayQueueQuantityDesc();
            break;

         case 6:
            cout << "\nCustomers having maximum profit:" << endl;
            
            displayMaxQuantityMinSalesCustomer(); // Call the new function
            break;


        case 7:
            cout << "\nExiting the program.\n";
            break;

        default:
            cout << "\nInvalid choice. Please enter a number between 1 and 6.\n";
        }

    } while (choice != 7);

    return 0;
}
