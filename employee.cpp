#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
#define ANSI_COLOR_RED_BOLD "\033[1;31m"
#define ANSI_COLOR_RESET "\033[0m"


void generatebill(char** item, int* price, int* quantity, int n, char** orderedItems, int* orderedQuantity, int orderedItemCount);

void takeorder(char** item, int* price, int* quantity, int n)
{
    const int max=5;  // Customer can PLace max 5 stock Item at One time. 
    char food[30];
    int quant;
    
    // Create arrays to store customer orders
    char** orderitems=new char*[max];
    int* orderquant=new int[max];
    int c=0;

    do 
    {
        cout<<"HELLO SIR!"<<endl;
        cout<<"Which Thing do you want to Buy Sir!....... (Enter 'E' to finish ordering and For Generating total Bill)"<<endl;
        cin>>food;

        if (strcmp(food, "E")==0)
        {
            break;
        }

        // Open the  Stock file for reading and writing
        fstream in("stocks.txt", ios::in | ios::out);
        int i=0;

        while (i<n&& in>>item[i]>>price[i]>>quantity[i]) 
       {
            //Comparing The stock item with Customer Input.
            if (strcmp(item[i], food)==0) 
            {
                cout<<"Item found "<<item[i]<<" | Price: "<<price[i]<<" | Quantity: "<<quantity[i]<<endl;
                break;
            }
            i++;
        }

        if (i==n) 
        {
            cout<<"Item not found."<<endl;
            cout<<"Check Item Name Again."<<endl;
            continue;
        }

        cout<<"Enter the quantity of Food you want to Eat SIR!: "<<endl;
        cin>>quant;

        if (quant>0 && quant<=quantity[i]) 
        {
        
            cout<<"Order placed successfully! Thank you."<<endl;
            quantity[i] -= quant;

            // Store order details in arrays So That to store the Customer order details in order file.
            orderitems[c]=new char[30];
            strcpy(orderitems[c], food);
            orderquant[c]=quant;
            c++;

            // Move the file pointer to the beginning of File.
            in.clear();
            in.seekp(0, ios::beg);
          
            //Updating the Data in Stock File
            for (int j=0;j<n;j++) 
            {
                in<<item[j]<<' '<<price[j]<<' '<<quantity[j]<<endl;
            }

            in.close();
        }
        else 
        {
            cout<<"Invalid quantity or insufficient stock."<<endl;
        }

    }while (c<max);

    // generating the bill of all items customer has order
    generatebill(item, price, quantity, n, orderitems, orderquant, c);

    // Deleting the Dynamic Arrays And Eqaul Them to NULL.
    for (int i=0;i<c;i++)
    {
        delete[] orderitems[i];
    }
    
    // Clean up memory
    delete[] orderitems;
    orderitems=NULL;
    delete[] orderquant;
    orderquant=NULL;
}

void generatebill(char** item, int* price, int* quantity, int n, char** orderitems, int* orderquant, int c)
{
    cout<<"Please Wait A second Sir"<<endl;
    cout<<"Our Computer is Generating Your Bill"<<endl;
    cout<<"Thank You For Your Corporation"<<endl;
    int bill=0;

    cout<<"======================================================"<<endl;
    cout<<"Item\t\tPrice\t\tQuantity\tTotal"<<endl;
    cout<<"======================================================"<<endl;
    
    // Double Loops For generating bill.
    for (int i=0;i<c;++i)
    {
        for (int j=0;j<n;++j) 
        {
            if (strcmp(orderitems[i], item[j])==0)
            {
                double totalprice = price[j] * orderquant[i];
                bill += totalprice;

                cout<<item[j]<< "\t\t"<<price[j]<<"\t\t"<<orderquant[i]<<"\t\t"<<totalprice<<endl;
                break;
            }
        }
    }

    cout<<"======================================================"<<endl;
    cout<<"Total Bill: "<<bill<<endl;
    cout<<"======================================================"<<endl;
}

void searchitems(char** item, int* price, int* quantity, int n)
{
    char search[30];

    cout<<"Enter the item names you want to search"<<endl;
    cin>>search;
    
    //Opening File For Reading
    ifstream in("stocks.txt");

    if (!in) 
    {
        cout<<"Error in opening File"<<endl;
        return;
    }

   
    int i=0;
    while (i<n && in>>item[i]>>price[i]>>quantity[i])
    {
        //Comparing The stock item with Customer Input.
        if (strcmp(item[i], search)==0)
        {
            cout<<"Item found "<<item[i]<<" | Price: "<<price[i]<<" | Quantity: "<<quantity[i]<<endl;
            break;
        }
        i++;
    }

    if (i==n) 
    {
        cout<<"Item not found."<<endl;
        cout<<"Check Item Name Again."<<endl;
        return;
    }
}

void viewonlineorder(char** item, int* price, int* quantity, int n)
{
   fstream on("order.txt",ios::in);
   int i=0;
   
   // Reading online orders from order file.
   while(on>>item[i]>>quantity[i])
   {
     cout<<"Item :"<<item[i]<<"  "<<"Quantity :"<<quantity[i]<<endl;
     i++;   
   }
   on.close();

}

void startwork() 
{
    cout<<"***************************************************************************************************************"<<endl;
    cout<<"**********************************************HELLO EMPLOYEE***************************************************"<<endl;
    cout<<"*******************************************WELCOME BACK TO WORK************************************************"<<endl;

    char** item;
    int* price;
    int* quantity;
    int n=0;

    // Opening the stock file for reading.
    fstream snake("stocks.txt", ios::in);

    char ch;
    while (snake.get(ch)) 
    {
        if (ch=='\n')
            n++;
    }

    snake.close();
  
    // Making Dynamic Arrays
    item=new char*[n];

    for (int i=0;i<n;i++)
    {
        item[i]=new char[20];
    }

    price=new int[n];
    quantity=new int[n];

    int choice;
do
{
    cout<<"Cafe Management System"<<endl;
    cout<<"1. Take Order"<<endl;
    cout<<"2. Search Items"<<endl;
    cout<<"3. View Online Orders"<<endl;
    cout<<"4. Exit"<<endl;
    cout<<"Enter your choice: "<<endl;
    cin>>choice;

    switch (choice) 
    {
        case 1:
        {
            takeorder(item, price, quantity, n);
            break;
        }    

        case 2:
        {
            searchitems(item, price, quantity, n);
            break;
        }
        
        case 3:
        {
            viewonlineorder(item, price, quantity, n);
            break;
        }
           
        case 4:
        {
             cout<<"Exiting Program, Good BYE!"<<endl;
             break;
        }         

        default:
            cout<<"Invalid choice. Please try again."<<endl;
            
   }
   
}while(choice!=4);


    //Deleting the Dynamic and Equaling pointers to NULL.
    for (int i=0;i<n;i++)
    {
        delete[] item[i];
    }

    delete[] item;
    item=NULL;
    delete[] price;
    price=NULL;
    delete[] quantity;
    quantity=NULL;
}

void processEmployee() 
{
    int n=0;
    char** name;
    int* pass;
  
    //Opening the File in Readind Form
    fstream employ("employ.txt",ios::in);

    if (!employ) 
    {
        cout<<"Invalid Text File Name"<<endl;
        cout<<"Check Text File Name Again"<<endl;
        return;
    }
    
    //Reading Each Line of File and finding End of Line
    char ch;
    while (employ.get(ch))
    {
        if (ch=='\n')
        {
            n++;
        }
    }

    name=new char*[n];
    pass=new int[n];

    //MOiving the Pointer to First Line.
    employ.clear();
    employ.seekg(0);

    for (int i=0;i<n;++i) 
    {
        name[i]=new char[50];
    }

    char id[50];
    int pin; // Assuming a single integer for password

    cout<<"Enter your username: "<<endl;
    cin>>id;
    cout<<"Enter password: "<<endl;
    cin>>pin;

    int i=0;
    while (i<n && employ>>name[i]>>pass[i]) 
    {
        if (strcmp(name[i], id)==0)
        {
            if (pass[i]==pin)
            {
                cout<<"You have logged in successfully"<<endl;
                startwork();
            } 
            else
            {
                cout<<"Incorrect Password Provided"<<endl;
                cout<<"Please recheck the password again"<<endl;
            }
            break; // Exit the loop after username and password matches
        }
        i++;
    }

    if (i==n)
    {
        cout<<"Incorrect ID Provided"<<endl;
    }
    
    // Deleting the Dynamic Arrays And Eqaul Them to NULL.  
    for (int j=0;j<n;j++) 
    {
        delete[] name[j];
    }

    delete[] name;
    name=NULL;
    delete[] pass;
    pass=NULL;

    employ.close();
}

