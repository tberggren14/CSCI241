/***************************************************************
CSCI 241         Assignment 9      spring 2021

Programmer: Trevor Berggren z1906236

Date Due: 04/01/2021
***************************************************************/

#ifndef SIMPLESIM_H
#define SIMPLESIM_H

class simplesim
{
private:

    int memory[100];
    int accumulator = 0;
    int instruction_counter = 0;
    int instruction_register = 0;
    int operation_code = 0;
    int operand = 0;

    bool not_valid_word(int) const;

public:

    simplesim();
    bool load_program();
    void execute_program();
    void dump() const;
};

#endif
