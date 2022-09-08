/***************************************************************
CSCI 241         Assignment 5      spring 2021

Programmer: Trevor Berggren z1906236

Date Due: 02/25/2021
***************************************************************/

#ifndef BANK_H
#define BANK_H

#include <string>
#include "account.h"

class bank
{
    private:

char bank_name[31];
account account_array[20];
int account_data;

public:

bank();
void read_accounts(const std::string& );
void process_transactions(const std::string& );
void print();
int search_for_account(const char*)const;

};

#endif