/***************************************************************
CSCI 241         Assignment 9      spring 2021

Programmer: Trevor Berggren z1906236

Date Due: 04/01/2021
***************************************************************/

#ifndef MYSTACK_H
#define MYSTACK_H
#include <iostream>

class mystack
{
    private:

    size_t stk_size = 0;
    size_t stk_capacity = 0;
    char* stack_array = nullptr;

    public:

    mystack() = default;
    mystack(const mystack&);
    ~mystack();
    mystack& operator=(const mystack&);
    size_t capacity() const;
    size_t size() const;
    bool empty() const;
    void clear();
    void reserve(size_t );
    const char& top() const;
    void push(char);
    void pop();
};
#endif
