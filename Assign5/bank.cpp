/***************************************************************
CSCI 241         Assignment 5      spring 2021

Programmer: Trevor Berggren z1906236

Date Due: 02/25/2021
***************************************************************/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <string> 
#include "bank.h"

using namespace std;

// default constuctor
// Sets c strings to none and account data to 0
bank::bank(){
    strcpy(bank_name, "None");
    account_data = 0;

}

/********************************************************************************
 * returns nothing void
 * @param string 
 * passing the file
 * reads account information
 *
 ********************************************************************************/
void bank:: read_accounts(const string& file_name){


    ifstream acc_file;              // file name

    // Open the input file and test for failure.
    acc_file.open(file_name);           // opens the file
    if (!acc_file)                      // prints error if the file cannot be opened 
    {
        cerr << "Error - unable to open input file " << file_name << endl;
        exit(1);
    }
    // Read an entire Course object worth of bytes into the Course object
    // that was used to call the read_accounts() member function.
    acc_file.read((char*) this, sizeof(bank));
    acc_file.close();

    int i, j, min;
    account temp;

        // sorts the data from the file 
    for (i = 0; i < account_data; i++)
    {
        min = i;

        for (j = i + 1; j < account_data; j++)
        {
            if (strcmp(account_array[j].get_account_number(), account_array[min].get_account_number()) < 0)
                min = j;
    

        }
        //swaps the data around
        temp = account_array[i];
        account_array[i] = account_array[min];
        account_array[min] = temp;
    }
    

}


    
/********************************************************************************
 * returns nothing void
 * @param string 
 * passing the file
 * processes account information and changes with withdrawals and deposits 
 *
 ********************************************************************************/
void bank:: process_transactions(const string& file_name){

    char date[6];
    char account_number[11];
    char type[2];
    double amount;

    ifstream trans_file;                                       // declares the file to be used

    // Open the input file and test for failure.
    trans_file.open(file_name);
    if (!trans_file)
    {
        cerr << "Error - unable to open input file " << file_name << endl;
        exit(1);
    }   

    // Prints the headers for the report
    cout <<"Transaction Report"<<endl;
    cout << "Date"<<"     " <<"Account";
    cout <<"     "<< "Type"<<"    "<< "Amount\t" <<"New Balance\n";
    cout << fixed << setprecision(2);

    while (trans_file >> date)                  // loop runs while there is information still in the file
    {
        cout<<date<<"    ";                     // prints the date

        // Read remaining data of the transaction record and prints them out
        trans_file >> account_number;
        cout << account_number << "   ";
        trans_file >> type;
        cout << type << "     ";
        trans_file >> amount;
        cout << "$" << amount << "       ";

        
        // Process this transaction.

        // declares and assigns index to a function to search for a account using account number
        int index = search_for_account(account_number);
        if (index == -1)                        // prints if a invalid account number is used
        {
            cout << "*** Invalid account number ***" << endl;
        } 
        else 
        {

            // checks to see if the type is a withdrawal or deposit
            // then calls the right function and prints accordingly
            if (strcmp(type, "D") == 0)             
            {
                account_array[index].process_deposit(amount);
                cout << "$" << account_array[index].get_balance() << endl;
            } 
            else 
            {
                if (account_array[index].process_withdrawal(amount))
                {
                    cout << "$" << account_array[index].get_balance() << endl;
                }
                else
                    cout << "*** Insufficient funds ***\n";
            }
        }
        
    }
    // close the file
    trans_file.close();
}

/********************************************************************************
 * returns mid or -1 depending if the account was found
 * @param char account number 
 * passes the account number in question
 * searhces for the account number 
 *
 ********************************************************************************/
int bank:: search_for_account(const char* account_number)const {

    int low = 0;
    int high = account_data - 1;
    int mid;

    // loop runs with low is less than or equal to high
    //searches for account number in account_array
    while (low<= high) {
        mid = (low + high) / 2;

        if (strcmp(account_number,account_array[mid].get_account_number()) == 0 ){

            return mid;
        }

        if (strcmp(account_number,account_array[mid].get_account_number()) < 0 )
            high = mid -1;
        else
            low = mid + 1;
    }

    return -1;
    }
    
/********************************************************************************
 * returns nothing
 * no paramaters
 * prints account information
 *
 ********************************************************************************/
void bank::print(){

    cout <<"Account Listing for " << bank_name<<endl<<endl;

    for (int i = 0; i < account_data; i++)
    {
        account_array[i].print();
        cout << endl;
    }
}