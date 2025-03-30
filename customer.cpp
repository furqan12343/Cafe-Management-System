#include"customer.h"
#include<iostream>
#include<fstream>
#include<cstring>
#include<iomanip>

// ANSI escape codes for text formatting
#define ANSI_COLOR_RED_BOLD "\033[1;31m"
#define ANSI_COLOR_RESET "\033[0m"

using namespace std;

void display(char** item, int* price, int* quantity, int n) 
{
    int threshold=10; //A certain Number after Which Stock will Give alert Sign.
    
    // Opening File in Read Form.
    fstream in("stocks.txt", ios::in);
    fstream out("notification.txt",ios::out|ios::app);

    if (!in||!out) 
    {
        cout<<"Error In opening the File"<<endl;
        return;
    }

    // Reading The data from Stock file.
    int i=0;
    while (i<n && in>>item[i]>>price[i]>>quantity[i])
    {
        i++;
    }

    in.close();

    cout<<"Data read from file in arrays:"<<endl;
    cout<<setw(15)<<left<<"Item"<<setw(15)<<left<<"Price"<<setw(15)<<left<<"Quantity"<<endl;
    cout<<"--------------------------------------------------"<<endl;

    // Displaying The Stock in Output.
    for (int k=0;k<n;k++) 
    {
        // Check if quantity is below the threshold
        if (quantity[k]<threshold) 
        {
            // Apply formatting for bold red text
            cout<<ANSI_COLOR_RED_BOLD;
            
            out<<"Low Stock Alert "<<item[k]<<"Quantity is Below Threshold"<<quantity[k]<<endl;
        }

        cout<<setw(15)<<left<<item[k]<<setw(15)<<left<<price[k]<<setw(15)<<left<<quantity[k]<<endl;

        // Reset Back To Default Colors
        cout<<ANSI_COLOR_RESET;
    }
}


void placeOrder( char** item, int* price, int* quantity, int n)
{

    char search[30];
    cout<<"Enter the food you want to buy:"<<endl;
    cin>>search;
    
    fstream in("stocks.txt",ios::in);
    fstream temp("temp.txt",ios::out);
    
    if (!in)
    {
        cout<<"Error in opening stock File."<<endl;
        return;
    }

   //Reading The data from Stock file and Finding the Stock that user Want.
    int i=0;    
    while (i<n && in>>item[i]>>price[i]>>quantity[i]) 
    {
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

  
    int quant;
    cout<<"Enter the quantity you want to buy: "<<endl;
    cin>>quant;

    
    if (quant>0 && quant<=quantity[i])
    {
        cout<<"Order placed successfully! Thank you."<<endl;
        quantity[i] -= quant;

        in.seekg(0, ios::beg);

        //Updating the Stock File.
        for (int j=0;j<n;++j) 
        {
            temp<<item[j]<<' '<<price[j]<<' '<<quantity[j]<<endl;
        }

        in.close();
        temp.close();

        if (rename("temp.txt", "stocks.txt") != 0) 
        {
            cout<<"Error: Unable to rename the temporary file"<<endl;
            return;
        }
    }
    
    else
    {
        cout<<"Invalid quantity or insufficient stock."<<endl;
    }
    
}

void complaints(const char* name, const char* complain) 
{
    //Writing Complains in file.
    ofstream out("complaints.txt", ios::app);
    out<<name<<" "<<complain<<endl;
    out.close();
    
}

void seenotification() 
{
   const int size = 200;
    char note[size];
    
    //Opening the File in Read Form.
    ifstream in("notification.txt");
    if (!in)
    {
        cout<<"File does not open"<<endl;
        cout<<"Check file name"<<endl;
    }
    
    while (in.getline(note, size))
    {
        cout<<note<<endl;
    }
    in.close();
}
   

void onlineorder(char** item, int* price, int* quantity, int n)
{
    const int max=5;  // Customer can PLace max 5 stock Item at One time.
    char food[30];
    int quant;

    // Create arrays to store customer orders
    char** orderitems=new char*[max];
    int* orderquant = new int[max];
    int c=0;

    do {
        cout<<"HELLO SIR!"<<endl;
        cout<<"Which Thing do you want to Buy Sir!....... (Enter 'E' to finish online order)"<<endl;
        cin>>food;

        if (strcmp(food, "E")==0) 
        {
            break;
        }

        // Open the  Stock file for reading and writing
        fstream in("stocks.txt", ios::in | ios::out);

        int i=0;
        while (i<n && in>>item[i]>>price[i]>>quantity[i]) 
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

        cout<<"Enter the quantity of Food you want to buy: ";
        cin>>quant;

        if (quant>0 && quant<=quantity[i])
        {
            
            cout<<"Order placed successfully! Thank you."<<endl;
            quantity[i] -= quant;

            // Store order details in arrays So That to store the Customer order details in order file.
            orderitems[c]=new char[strlen(food) + 1];
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
                      
        }
         
        else
        {
            cout<<"Invalid quantity or insufficient stock."<<endl;
        }

      
        in.close();

    } while (c<max);

     cout<<"Online Order has been Place Succesfully"<<endl;
     
    // Open the order file for Storing Customer Order Details
    ofstream order("order.txt");

    // Write orders to the file
    for (int i=0; i<c;++i) 
    {
        order<<orderitems[i]<<"  "<<orderquant[i]<<endl;
    }
    order.close();
    
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

void playandwin(char** item, int* price, int* quantity, int n)
{
    srand(time(NULL));
    int n1=rand() % 20 + 1;
    int n2=rand() % 20 + 1;
    char choice1;

    cout<<"The Randomly Generated number is: "<<n1<<endl;

    cout<<"Enter H for Higher or L for Lower: ";
    cin>>choice1;

    if ((choice1=='H' && n2>n1) || (choice1=='L' && n2<n1))
    {
        cout<<"Congratulations! You Won :)"<<endl;

        // Offer the customer a free item
        char search[20];
        cout<<"Enter the item you want to search for: ";
        cin>>search;

        // Open the stock file for reading and writing
        fstream in("stocks.txt", ios::in | ios::out);

        int i=0;
        while (i<n && in>>item[i]>>price[i]>>quantity[i])
        {
            if (strcmp(item[i], search)==0)
            {
                cout << "Item found: "<<item[i]<<" | Price: "<<price[i]<<" | Quantity: "<<quantity[i]<<endl;

                // Offer one item for free
                if (quantity[i]>0)
                {
                    cout<<"You get one "<<item[i]<<" for free! Enjoy!"<<endl;
                    quantity[i]--;

                    // Move the file pointer to the beginning of File.
                    in.clear();
                    in.seekp(0, ios::beg);

                    // Updating the Data in Stock File
                    for (int j=0;j<n;j++)
                    {
                        in<<item[j]<<' '<<price[j]<<' '<<quantity[j]<<endl;
                    }
                    break;
                }
                else
                {
                    cout<<"Sorry, the item is out of stock."<<endl;
                }
            }

            i++;
        }

        // Close the stock file
        in.close();
    }
    else
    {
        cout<<"OhOh! You Lost :( "<<endl;
    }
}

void processCustomer()
{

    char** item;
    int* price;
    int* quantity;
    char head[40];
    int n=0;
    
    //Opening the File in Reading Form.
    fstream snake("stocks.txt", ios::in);

    //Reading Each Line of File and finding End of Line.
    char ch;
    while (snake.get(ch))
    {
        if (ch=='\n')  
            n++;
    }
     
    snake.close();  
    
    // Making Dyanamic arrays 
    item=new char*[n];
        
    for (int i=0;i<n;i++)
    {
        item[i]=new char[30];
    }
        
    price=new int[n];
    quantity=new int[n];

    int choice; 
do 
{
        cout<<"\t\t\tHELLO CUSTOMER\t\t\t"<<endl;
        cout<<"Choose your choice"<<endl;
        cout<<"1. Display food Items"<<endl;
        cout<<"2. Place an Order"<<endl;
        cout<<"3. See Notifications"<<endl;
        cout<<"4. Give Complaints"<<endl;
        cout<<"5. Place an Online Order"<<endl;
        cout<<"6. Play Higher and Lower and win a Free Thing"<<endl;
        cout<<"7. Exit"<<endl;
        cin>>choice;
       

        switch (choice)
   {

        case 1: 
        {
            display(item, price, quantity, n);
            break;
        }

        case 2: 
        {
            placeOrder(item, price, quantity, n);
            break;
        }

        case 3: 
        {
            seenotification();
            break;
        }

        case 4: 
        {
            char name[20];
            char complain[200];
            cout<<"Enter your name: "<<endl;
            cin>>name;

            cout << "Enter your complaint: ";
            cin.ignore();
            cin.getline(complain, 200);
            
            // Calling the Function.
            complaints(name, complain);
            cout<<"Complaint saved successfully."<<endl;
            break;
        }

        case 5: 
        {
            onlineorder(item, price, quantity, n);
            break;
        }
        case 6:
        {
           playandwin(item,price,quantity,n);
           break;
        }

        case 7: 
        {
            cout<<"Exiting the program. Goodbye!" << endl;
            break;
        }
        

        default: 
        {
            cout<<"Invalid Input";
            cout<<" Please try again"<<endl;
        }
   }

} while (choice != 7);

    // Deleting the Dynamic Arrays And Eqaul Them to NULL.   
    for (int i=0;i<n;i++)    
    {
        delete[]item[i];
    }
    
    delete[] item;
    item=NULL;
    delete[] price;
    price=NULL;
    delete[] quantity;
    quantity=NULL;
}
