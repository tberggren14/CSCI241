//*******************************************************************
// 
//  CSCI 241 Assignment 10
//
// Trevor Berggren  z1906236
// 4/8/2021
//
//*******************************************************************

#ifndef MYLIST_H
#define MYLIST_H
        
#include <iostream>
#include <stdexcept>
        
// Forward declaration of the mylist template class
template <class T>
class mylist;
        
// Forward declaration of the operator<< template function
template <class T>
std::ostream& operator<<(std::ostream&, const mylist<T>&);

template <class T>
struct node
{
      T value;
    node<T>* prev;
    node<T>* next;
    
    node(const T& value = T(), node<T>* prev = nullptr, node<T>* next = nullptr)
    {
        this->value = value;
        this->prev = prev;
        this->next = next;
    }
};

template <class T>
class mylist
{
    // friend declaration for the template function - note the special syntax
    friend std::ostream& operator<< <>(std::ostream&, const mylist<T>&);
        
    private:
    node<T>* l_back = nullptr;
    node<T>* l_front = nullptr;
    size_t list_size = 0;

    void clone(const mylist<T>&);

    public:
    mylist() = default;
    mylist(const mylist<T>&);
    ~mylist();
    mylist<T>& operator=(const mylist<T>&);

    void clear();
    size_t size() const;
    bool empty() const;
      
    const T& front() const;
    T& front();
    const T& back() const;
    T& back();
      
    void push_front(const T&);
    void push_back(const T&);
    void pop_front();
    void pop_back();

    
    bool operator==(const mylist<T>&)const;
    bool operator<(const mylist<T>& rhs) const;

};

//destructor
template <class T>
mylist<T>::~mylist()
{
    clear();                            // clears the queue
}

//copy constructor
template <class T>
mylist<T>::mylist(const mylist<T>& x)
{
    l_front = l_back = nullptr;        // makes front and back null
    list_size = 0;                      
    clone(x);                           // clones objext
} 

/**
 * Copy assignment operator.
 *
 * @param x The mystack object on the right-hand side of the 
 *          assignment statement.
 *
 * @return The updated mystack object on the left side of the 
 *         assignment statement.
 ********************************************************************/
template <class T>
mylist<T>& mylist<T>::operator=(const mylist<T>& x)
{
    if (this != &x)
    {   
        clear();        // clears and clones
        clone(x);
    }
         
    return *this;       // returns this pointer
}

/**
 * Resets the stack to the empty state.
 ********************************************************************/
template <class T>
void mylist<T>::clear()
{
    while (!empty())            // while queue is not empty pops
        pop_front();
}

/**
 * Returns the stack size.
 *
 * @return The number of elements stored in the stack.
 ********************************************************************/ 
template <class T>
size_t mylist<T>::size() const
{
    return list_size;
}

/**
 * Tests whether the stack is empty.
 *
 * @return Returns true if the stack size is 0, false
 *         otherwise.
 ********************************************************************/ 
template <class T>
bool mylist<T>::empty() const
{
    if (list_size == 0){
        return true;            // if list size is 0 true else false
    }
    return false;
}

/**
 * Accesses the front element of the queue.
 *
 * @return The front element of the queue.
 ********************************************************************/
template <class T>
const T& mylist<T>::front() const
{
    if (empty())
        throw std::underflow_error("queue underflow on front()");

    return l_front->value; 
}

/**
 * Accesses the front element of the queue.
 *
 * @return The front element of the queue.
 ********************************************************************/
template <class T>
T& mylist<T>::front()
{
    if (empty())
        throw std::underflow_error("queue underflow on front()");

    return l_front->value;
}

/**
 * Accesses the back element of the queue.
 *
 * @return The back element of the queue.
 ********************************************************************/
template <class T>
const T& mylist<T>::back() const
{
    if (empty())
        throw std::underflow_error("queue underflow on back()");

    return l_back->value;
}

/**
 * Accesses the back element of the queue.
 *
 * @return The back element of the queue.
 ********************************************************************/
template <class T>
T& mylist<T>::back()
{
    if (empty())
        throw std::underflow_error("queue underflow on back()");

    return l_back->value;
}

/**
 * Clones the object
 *
 ********************************************************************/
template <class T>
void mylist<T>::clone(const mylist<T>& x)
{
    node<T>* ptr;
   
    for (ptr = x.l_front; ptr != nullptr; ptr = ptr->next)
        push_back(ptr->value);                              // loop while ptr doesnt equal null and 
                                                            // pushes ptr->value back
}

/**
 * Inserts a value at the top of the stack.
 *
 * @param value The value to insert.
 ********************************************************************/ 
template <class T>
void mylist<T>::push_front(const T& value)
{
    node<T>* new_node = new node<T>(value);     // new node
    new_node->next = l_front;                   // assigns

    if(empty())
    l_back = new_node;                          // checks to see if empty and assigns the new node
    else 
    l_front->prev = new_node;                   // pushes l_front prev to new node

    l_front = new_node;

    list_size++;                                // increment
}

/**
 * Accesses the back element of the queue.
 *
 * @return The back element of the queue.
 ********************************************************************/
template <class T>
void mylist<T>::push_back(const T& value)
{
    node<T>* new_node = new node<T>(value);     // new node and assigns
    new_node->prev = l_back;

    if(empty())                                 // checks to see if empty and assigns the new node
    l_front = new_node;
    else 
    l_back->next = new_node;                    // pushes l_back next to new node

    l_back = new_node;

    list_size++;                                // increment
}

/**
 * Removes the front element of the queue.
 *
 ********************************************************************/
template <class T>
void mylist<T>::pop_front()
{
    if (empty())
        throw std::underflow_error("queue underflow in pop_front()");

    node<T>* del_node = l_front; // Save address of node to delete in a pointer
    l_front = del_node->next;    // Point l_back at the new last node in the list

    if(l_front == nullptr)
        l_back = nullptr;
    else
    l_front->prev = nullptr;     // Set the new last node's next pointer to nullptr
    delete del_node;

    list_size--;
}

/**
 * Removes the back element of the queue.
 *
 ********************************************************************/
template <class T>
void mylist<T>::pop_back()
{
    if (empty())
        throw std::underflow_error("queue underflow in pop_back()");

    node<T>* del_node = l_back; // Save address of node to delete in a pointer
    l_back = del_node->prev;    // Point l_back at the new last node in the list

    if(l_back == nullptr)
        l_front = nullptr;
    else
    l_back->next = nullptr;     // Set the new last node's next pointer to nullptr
    delete del_node;

    list_size--;

}

/**
 * Tests to see if left and right sides are equal to eachother
 *
 ********************************************************************/
template <class T>
bool mylist<T>::operator==(const mylist<T>& rhs) const
{
    if(size() != rhs.list_size)         // checks if sizes are equal
    return false;

    node<T>* list1 = l_front;           // declares and assigns
    node<T>* list2 = rhs.l_front;

    while(list1 && list2)               // while list 1 and 2 have values
    {
        if(list1->value != list2->value)    // if not equal
        return false;

        list1 = list1->next;                // next node
        list2 = list2->next;
    }
    return true;

}

/**
 * Tests to see if left is less than the right side
 *
 ********************************************************************/
template <class T>
bool mylist<T>::operator<(const mylist<T>& rhs) const
{
    node<T>* list1 = l_front;               // declares and assigns
    node<T>* list2 = rhs.l_front;

    while(list1 != nullptr && list2 != nullptr)     // while not equal to nullptr
    {
        if(list1->value < list2->value)             // list 1 less 
        {
        return true;
        }

        else if(list1->value > list2->value)        // list 1 more
        {
        return false;
        }
                                               // goes through all values
        {
            list1 = list1->next;
            list2 = list2->next;
        }
    }
        if(list1 == nullptr && list2 != nullptr)        // if euqal is true
        return true;
        else
        return false;

}

/********************************************************************************
 * returns the left hand side operator
 * @param os
 * @param rhs
 * this function take << and makes it able to print
 *
 ********************************************************************************/
template <class T>
std::ostream& operator<<(std::ostream& os, const mylist<T>& obj)
{
    node<T>* frontptr = obj.l_front;        // new node

    for(size_t i = 0; i< obj.list_size;i++) // loop goes over the objects list size
    {
        os << frontptr->value << " ";       // puts values into os
        frontptr = frontptr->next;           // goes to next 
    }
    return os;                              // returns printable

}
#endif