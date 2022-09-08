/***************************************************************
CSCI 241         Assignment 5      spring 2021

Programmer: Trevor Berggren z1906236

Date Due: 02/25/2021
***************************************************************/

#ifndef ACCOUNT_H
#define ACCOUNT_H

class account
{

private:

    char account_number[11];
    char customer_name[21];
    double balance;

public:

    account();
    const char* get_account_number()const;
    double get_balance();
    void process_deposit(double);
    bool process_withdrawal(double);
    void print();

};

#endif