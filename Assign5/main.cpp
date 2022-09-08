/***************************************************************
CSCI 241         Assignment 5      spring 2021

Programmer: Trevor Berggren z1906236

Date Due: 02/25/2021
***************************************************************/

#include "bank.h"

int main()
{
    bank b;             // bank object
    b.read_accounts("accounts");        // calls read account function passing it accounts file
    b.print();                          // prints the results
    b.process_transactions("transactions.txt");     // calls the process transcation and passes it transaction file
    b.print();                          // prints the results

    return 0;
}