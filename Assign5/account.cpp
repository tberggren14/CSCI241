/***************************************************************
CSCI 241         Assignment 5      spring 2021

Programmer: Trevor Berggren z1906236

Date Due: 02/25/2021
***************************************************************/

#include <iostream>
#include <iomanip>
#include <cstring>

#include "account.h"

using namespace std;

// default constuctor
// Sets c strings to none and balance to 0
account::account() {

    strcpy(account_number, "None");         
    strcpy(customer_name, "None");
    balance = 0;

}

/********************************************************************************
 * returns a account number 
 * no paramaters
 * const
 *
 ********************************************************************************/
const char* account::get_account_number() const {

    return account_number;

}

/********************************************************************************
 * returns a balance 
 * no paramaters
 * double
 *
 ********************************************************************************/
double account::get_balance() {

    return balance;
}

/********************************************************************************
 * returns nothing 
 * @param deposit
 * deposit + balance is the new balance
 * updates the new balance 
 *
 ********************************************************************************/
void account::process_deposit(double deposit){

    
    balance = deposit + balance;

}

/********************************************************************************
 * returns a boolean true if a valid withdraw false if not
 * @param withdraw
 * balance - withdraw is the new balance 
 *updates new balance
 * 
 ********************************************************************************/
bool account:: process_withdrawal(double withdraw){

    if (withdraw <= balance)
    {
        balance = balance - withdraw;
        return true;
    }
    else 
        return false;

}

/********************************************************************************
 * returns nothing
 * no paramaters
 * prints account information
 *
 ********************************************************************************/
void account::print(){

    cout << "Account Number: " << account_number << endl;
    cout << "Name: " << customer_name << endl;
    cout << "Balance: $" << fixed << setprecision(2) << balance<<endl;

}