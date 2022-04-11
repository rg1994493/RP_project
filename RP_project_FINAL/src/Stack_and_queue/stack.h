#pragma once
#include <iostream>
using namespace std;

//******************************************************
#define SIZE 10
template <class T> 
class Stack { //Stack for DFS method
  public:
      Stack();
      void push(T k);
      T pop();
      T topElement();
      T get(int pos);
      int topPos();
      int frontPos();
      bool isFull();
      bool isEmpty();
  
    private:
      int top; // Taking data member top
      int front;
      T st[SIZE]; // Initialising stack with initial size
    
};
 
// To initialise top to -1(default constructor)
template <class T> Stack<T>::Stack() { top = -1; front = 0;}
template <class T> int Stack<T>::topPos() { return top;}
template <class T> int Stack<T>::frontPos() { return front;}
 
// To add element element k to stack
template <class T> void Stack<T>::push(T k){
 
    if (isFull()) {
      throw std::invalid_argument(" stack full ");
    }
 
    // Incrementing the top by unity as element is to be inserted
    top = top + 1;
    // Now, adding element to stack
    st[top] = k;
}
 
template <class T> bool Stack<T>::isEmpty(){
    if (top == -1)
        return 1;
    else
        return 0;
}
 
template <class T> bool Stack<T>::isFull(){
    if (top == (SIZE - 1))
      return 1;
    else
      return 0;
}
 
template <class T> T Stack<T>::pop(){
    // Initialising a variable to store popped element
    T pop_element = st[top];
    // Decreasing the top as element is getting out from the stack
    top--;
    return pop_element;
    
}
 
template <class T> T Stack<T>::topElement(){
    // Initialising a variable to store top element
    T top_element = st[top];
 
    return top_element;
}

template <class T> T Stack<T>::get( int pos ){
    // Initialising a variable to store get element
    T element;
    if(pos <= top && pos>= 0)
      element = st[pos];
 
    return element;
}
//******************************************************

