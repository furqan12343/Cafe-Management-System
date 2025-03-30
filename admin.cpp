#include"admin.h"
#include<iostream>
#include<fstream>
#include<cstring>
#include<iomanip>
using namespace std;
#define ANSI_COLOR_RED_BOLD "\033[1;31m"
#define ANSI_COLOR_RESET "\033[0m"


void startMenu();
void employ();

void displaystock(char** item, int* price, int* quantity, int n) 
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
            
            out<<"Low Stock Alert! "<<item[k]<<" Quantity is Below Threshold "<<threshold<<endl;
        }

        cout<<setw(15)<<left<<item[k]<<setw(15)<<left<<price[k]<<setw(15)<<left<<quantity[k]<<endl;
        out.close();
        // Reset Back To Default Colors
        cout<<ANSI_COLOR_RESET;
    }
}


void Addstock(char** item, int* quantity, int* price, int n) 
{
    //Opening the file both in reading and writing form.
    fstream out("stocks.txt", ios::out | ios::app);

    char itemname[30];
    cout<<"Enter item name: "<<endl;
    cin>>itemname;
    cout<<"Enter price: "<<endl;
    cin>>price[0];
    cout<<"Enter quantity: "<<endl;
    cin>>quantity[0];
    

    out<<itemname<<' '<<price[0]<<' '<<quantity[0]<<endl;
    out.close();

    // Update the arrays with the new item that admin will enter
    char** newitem=new char*[n + 1];
    int* newquant= new int[n + 1];
    int* newprice=new int[n + 1];

    for (int i=0;i<n;i++)
    {
        newitem[i]=item[i];
        newquant[i]=quantity[i];
        newprice[i]=price[i];
    }

    newitem[n] = new char[strlen(itemname) + 1];
    strcpy(newitem[n], itemname);
    newquant[n]=quantity[0];
    newprice[n]=price[0];
     
    cout<<"Item Added Susscesfully"<<endl;

    // Clean up old arrays
    delete[] item;
    delete[] quantity;
    delete[] price;

    // Update pointers
    item=newitem;
    quantity=newquant;
    price=newprice;
    n++;
}



void removestock(char** item, int* quantity, int* price, int n) 
{
    char itemname[20];
    cout<<"Enter Item name to remove: "<<endl;
    cin>>itemname;

    // Open the file for reading
    ifstream in("stocks.txt");

    int i=0;
    while (i<n && in>>item[i]>>price[i]>>quantity[i])
    {
        if (strcmp(item[i], itemname)==0)
        {
            break;
        }
        i++;
    }

    if (i==n)
    {
        cout<<"Item not found in stock." << endl;
        return;
    }

    cout<<"Found at location: "<<i<<endl;

    // Open a temporary file for writing
    ofstream out("temp.txt");
 
    //Updating and Writing the data Back.
    for (int a=0;a<n;a++) 
    {
        if (a==i)
        {
            continue;
        }
        out<<item[a]<<' '<<quantity[a]<<' '<<price[a]<<endl;
    }

    in.close();
    out.close();

    // Rename the temporary file with the original file
    if (rename("temp.txt", "stocks.txt")!=0)
     {
        cout<<"Unable to rename the temporary file." << endl;
        return;
    }

    cout<<"Item removed successfully."<<endl;
}

void order( char** item, int* quantity, int* price, int n)
{

    char search[30];
    cout<<"Enter the food you want to buy:"<<endl;
    cin>>search;
    
    fstream in("stocks.txt", ios::in);
    fstream temp("temp.txt", ios::out);
    
    if (!in)
    {
        cout<<"Error in opening File"<<endl;
        return;
    }

    // Reading the data from file and Searching.
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

        // moiving the pointer to start of file.
        in.seekg(0, ios::beg);

        for (int j=0;j<n;j++) 
        {
            temp<<item[j]<<' '<<price[j]<<' '<<quantity[j]<<endl;
        }

        in.close();
        temp.close();

        //Remaing the File.
        if (rename("temp.txt", "stocks.txt")!=0) 
        {
            cout<<"Unable to rename the temp file"<<endl;
            return;
        }
    }
    else
    {
        cout<<"Invalid quantity or insufficient stock."<<endl;
    }
}

void handleCafeStock( char** item, int* quantity, int* price, int n) 
{
    int choice;
    cout<<"Do you Want to"<<endl;
    cout<<"1. Display"<<endl;
    cout<<"2. Add"<<endl;
    cout<<"3. Remove"<<endl;
    cout<<"4. Exit"<<endl;
    cin>>choice;

    switch (choice) 
    {
        case 1: 
        {
            displaystock( item, price, quantity, n);
            break;
        }
        
        case 2: 
        {
            Addstock(item, quantity, price, n);
            break;
        }
        
        case 3: 
        {
            removestock(item, quantity, price, n);
            break;
        }
        
        case 4:
        {
            cout<<"Good BYE!"<<endl;
            break;
        }
        
        default:
            cout<<"Invalid choice. Please try again.";
    }
}

void notif()
{
    const int size = 200;
    char note[size];
    
    //Opening the file in writing file.
    ofstream n("notification.txt", ios::app);
    
    cout<<"Enter Notification Here"<<endl;
    cin.ignore();
    cin.getline(note, size, '\n');

    n<<note<<endl;

    cout<<"\tSIR!\t"<<endl;
    cout<<"Notification has been generated successfully"<<endl;
}

void removeemployee(const char emp[])
{
    ifstream in("employ.txt");
    ofstream temp("temp.txt");

    char name[5][40];
    int pin[5];

    int i=0;
    // Reading data from file.
    while (i<5 && in>>name[i]>>pin[i]) 
    {
        if (strcmp(name[i], emp)==0)
        {
            i--; 
        }
        
        i++;
    }

    in.close();
    
    //Updating the data in Stock File.
    for (int j=0;j<i;j++)
    {
        temp<<name[j]<<' '<<pin[j]<<endl;
    }
    temp.close();
     
    //Renaming the Temp File. 
    if (rename("temp.txt", "employ.txt")!=0) 
    {
        cout<<"Unable to rename the temporary file."<<endl;        
        return;
    }

    cout<<"Employee removed successfully."<<endl;
}

void addemploy() 
{
    char name[40];
    int pin;
    char choice1;
    
    // Opening The File in Writing And Append Form
    fstream out("employ.txt", ios::out | ios::app);
    do 
    {
        cout<<"Enter the name of employ: "<<endl;
        cin>>name;
        cout<<"Please Give employ a Password: " << endl;
        cin>>pin;
        
        // Writng data in the file.
        out<<name<<' '<<pin<<endl;
        cout<<"Empoly added successfully"<<endl;
        cout<<"Do you want enter more employs? (y/n)";
        cin>>choice1;
    } 
    while (choice1=='y' || choice1=='Y');

    out.close();
}

void employ() 
{
    int choice;
    cout<<"Enter The Choice"<<endl;
    cout<<"1. You Want Add Employee\n"<<endl;
    cout<<"\tOR\t"<<endl;
    cout<<"2. Remove Employee"<<endl;
    cout<<"3. Exit"<<endl;
    cin>>choice;
  
    switch (choice) 
    {
        case 1:
        {
            addemploy();
            break;
        }
        
        case 2:
        {
            char emp[50];
            cout<<"Enter the name of employee" << endl;
            cin>>emp;
            removeemployee(emp); //Calling the Function.
            break;
        }
        
        default:
            cout<<"Invalid Choice"<<endl;
    }
}

void seenotif()
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

void seecomplains()
{
    const int size = 200;
    char comp[size];
    
    //Opening The Complain File in Read Form.
    fstream com("complaints.txt", ios::in);
    if (!com)
    {
        cout<<"File does not open"<<endl;
        cout<<"Check file name"<<endl;
    }
    
    while (com.getline(comp, size))
    {
        cout<<comp<<endl;
    }
    com.close();
}

void removecomplains()
{
    fstream rem("complaints.txt", ios::in);
    fstream tem("temp.txt", ios::out); //Opening Tem File in Write Form.
  
    char name[50];
    char complain[200];
    char customer[50];
  
    cout<<"Enter The name of customer which complain do you want to remove SIR!"<<endl;
    cin>>customer;

    while (rem>>name>>complain)
    {
        if (strcmp(name, customer)!=0)
        {
            tem<<name<< " " <<complain<<endl<<endl;
        }
    }
  
    //Closing all Files.
    rem.close();
    tem.close();
  
    // Renaming The file.
    if (rename("temp.txt", "complaints.txt")!=0)
    {
        cout<<"Error In renaming files"<<endl;
    }
  
    cout<<"Complaint Remove Succesfully"<<endl;
}

void handlecomplains()
{
    int choice;
    cout<<"Enter your choice"<<endl;
    cout<<"1.See Complains"<<endl;
    cout<<"2.Remove Complains"<<endl;
    cin>>choice;
  
    switch (choice)
    {
        case 1:
        {
            seecomplains(); ///////////////////
            break;                            //
        }                                     //
                                              //////// Calling THE FUCNTIONS.
        case 2:                               //
        {                                     //
            removecomplains(); /////////////////
            break;        
        }
    
        default:
            cout << "Invalid Choice" << endl;
    }
}

void startMenu() 
{
    char** item;
    int* price;
    int* quantity;
    int n=0;

    fstream snake("stocks.txt", ios::in);

    char ch;
    while (snake.get(ch))
    {
        if (ch=='\n')  
            n++;
    }
     
    snake.close();  

    // Making Dyanmic Arrays.
    item=new char*[n];
    
    for (int i=0;i<n;i++)
    {
        item[i]=new char[30];
    }
    
    price=new int[n];
    quantity=new int[n];
    
    int choice;
    
    //Applying Do While Loop So that Program should Not Close.
do
{    

    cout<<"\n\tCafe Administrator Menu:\t\n";
    cout<<"1. Handle Cafe Stock"<<endl;
    cout<<"2. Generate Notifications"<<endl;
    cout<<"3. Order Items"<<endl;
    cout<<"4. Manage Employees"<<endl;
    cout<<"5. Display Notifications"<<endl;
    cout<<"6. Handle Complaints"<<endl;
    cout<<"7.Exit"<<endl;
    
    cout<<"Enter your choice: "; 
    cin>>choice;

    switch (choice) 
    {
        case 1:
        {
            handleCafeStock(item, price, quantity, n);
            break;
        }
            
        case 2:
        {
            notif();
            break;
        }
        
        case 3:
        {
           order(item, price, quantity, n);
           break;
        } 
           
        case 4:
        {
             employ();
             break;
        }
        
        case 5:
        {
            seenotif();
            break;
        }
            
        case 6:
        {
          handlecomplains();
          break;
        }
      
           
        case 7:
        {
          cout<<"Exting Program, Good BYE!"<<endl;
          break;
        }           
       
        default:
            cout << "Invalid choice. Please try again.\n";
    }
 
}while(choice!=7);    
    
    // Deleting All The Dynamic Arrays.
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

void processAdmin() 
{
    bool login=false;
    string username;
    int password;
    string Admin="admin";
    const int Pin=6789;

    while (!login)
    {
    
        cout<<"\tHELLO SIR\t"<<endl;
        cout<<"WELCOME BACK TO WORK"<<endl;
        cout<<"We have LOt of WorkToday................"<<endl;

        cout<<"Enter your username: "<<endl;
        cin>>username;

        cout<<"Enter password: "<<endl;
        cin>>password;

        if ((username==Admin) && (password==Pin))
        {
            cout<<"You have logged in successfully"<<endl;
            login=true;
            startMenu();
        } 
        else
        {
            cout<<"Invalid username and Password \n Please Try again"<<endl;
        }
    }
}



