/***************************************************************
CSCI 241         Assignment 9      spring 2021

Programmer: Trevor Berggren z1906236

Date Due: 04/01/2021
***************************************************************/

#include "mystack.h"

/********************************************************************************
 * returns nothing
 * @param class object x
 * copy constructor
 *
 ********************************************************************************/
mystack::mystack(const mystack& x)
{
    // Step 1 
    // Assigning capacity and size
    stk_capacity = x.stk_capacity;
    stk_size = x.stk_size;

    // Step 2
    // if capacity is > than 0 array = capacity
    //else array is assigned a null pointer
    if (stk_capacity > 0)
        stack_array = new char[stk_capacity];
    else
        stack_array = nullptr;

    // Step 3
    // copying the stacks
    for (size_t i = 0; i < stk_size; ++i){
        stack_array[i] = x.stack_array[i];
    }

}

/********************************************************************************
 * returns nothing
 * no param
 * function deletes stack array
 ********************************************************************************/
mystack::~mystack()
{
    // deletes the stack array
     delete[] stack_array;

}

/********************************************************************************
 * returns this pointer
 * @param class object x
 * function is a overloaded copy assignment
 ********************************************************************************/
mystack& mystack::operator=(const mystack& x)
{
     if (this != &x){
        // Step 2
        // deletes the stack array
        delete[] stack_array;

        // Step 3
        // Assigning capacity and size
        stk_capacity = x.stk_capacity;
        stk_size = x.stk_size;

        // Step 4
        // if capacity is > than 0 array = capacity
    //else array is assigned a null pointer
        if (stk_capacity > 0)
            stack_array = new char[stk_capacity];
        else
            stack_array = nullptr;


        // Step 5
         // copying the stacks
        for (size_t i = 0; i < stk_size; ++i)
            stack_array[i] = x.stack_array[i];
    }
    return *this;

}

/********************************************************************************
 * returns stk_capacity
 * no param
 * function returns the capacity
 ********************************************************************************/
size_t mystack::capacity() const
{
    return stk_capacity;

}

/********************************************************************************
 * returns stk_size
 * no param
 * function returns the stack size
 ********************************************************************************/
size_t mystack::size() const
{
    return stk_size;

}

/********************************************************************************
 * returns bool
 * no param
 * function returns true if size equals 0 overwise false
 ********************************************************************************/
bool mystack::empty() const
{
     if (stk_size == 0){
        return true;
    }
    return false;

}
/********************************************************************************
 * no return
 * no param
 * function clears stack size
 ********************************************************************************/
void mystack::clear()
{
    stk_size = 0;

}

/********************************************************************************
 * no return 
 * @param n
 * function reserves capacity
 ********************************************************************************/
void mystack::reserve(size_t n)
{
    if (n < stk_size || n == stk_capacity){
        return;
    }

    stk_capacity = n;                           // Assigns n to capacity
    char* temp_array = new char[n];             // declares temp array for storeage
    for (size_t i = 0; i < stk_size; i++){      // uses the temp array for storeage
        temp_array[i] = stack_array[i];
    }

    delete[] stack_array;                       // deletes prior array
    stack_array = temp_array;

}

/********************************************************************************
 * returns top of the stack
 * no param
 * function returns the top of the stack 
 ********************************************************************************/
const char& mystack::top() const
{
    return stack_array[stk_size - 1];

}

/********************************************************************************
 * mo return
 * @param value
 * function pushes the value to the back of the string
 ********************************************************************************/
void mystack::push(char value)
{
     if (stk_size == stk_capacity){
        if (stk_capacity == 0)
            reserve(1);                 // reserves storeage
        else 
            reserve(stk_capacity * 2);  // doubles teh storeage
    }
    stack_array[stk_size] = value;
    stk_size++;

}

/********************************************************************************
 * no return
 * no param
 * function pops the stack size by 1
 ********************************************************************************/
void mystack::pop()
{
    stk_size--;

}