#include "include.h"


using namespace std;

void run() 
{
    char op;
    int choice;
    cout<<"*******************************************************************************"<<endl;
    cout<<"*********************************WELCOME TO CDS********************************"<<endl;
    cout<<"*******************************************************************************"<<endl;
    cout << "Choose your Identity\n"<<endl;
    cout << "\t\t1. Admin\t\t"<<endl;
    cout << "\t\t2. Employee\t"<<endl;
    cout << "\t\t3. Customer\t\t"<<endl;
    cin >> choice;

    if (choice == 1) 
    {
         processAdmin();
    }
     
    else if (choice == 2) 
    {
         processEmployee();
    }
     
    else if (choice == 3) 
    {
        processCustomer();
   
    }
}




