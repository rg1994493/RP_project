#pragma once
#include <iostream>
using namespace std; 

//***********************************************************

#define SIZE2 100
template <class T> 
class Queue { //QUEUE for BFS method
  public:
    Queue();
    T pop();
    void push(T x);
    int size();
    T get( int pos );
    int topPos();
    int frontPos();
    bool isEmpty();
    bool isFull();
  
  private:
    int capacity = SIZE2;
    int front;
    int rear;
    int count;

    // Initialising queue with initial size
    T q[SIZE2];
};
 
template <class T> Queue<T>::Queue() {
  this->front = 0;
  this->rear = -1;
  this->count = 0;
}

template <class T> T Queue<T>::pop() {
    // check for queue underflow
    if (isEmpty()){
        cout << "Empty\n";
        exit(EXIT_FAILURE);
    }
    T element = q[front];
    front = (front + 1);
    count--;
    
    return element;
}

// Utility function to add an item to the queue
template <class T> void Queue<T>::push(T item) {
    // check for queue overflow
    if (isFull()) {
        cout << "Full\n";
        exit(EXIT_FAILURE);
    }
    
    rear = (rear + 1);
    q[rear] = item;
    count++;
    
  }

// Utility function to return the front element of the queue
template <class T> T Queue<T>::get( int pos ){
    // Initialising a variable to store top element
    T element;
    element = q[pos];
 
    return element;
}

// Utility function to return rear and front of the queue
template <class T> int Queue<T>::topPos() {
    return rear;
}

template <class T> int Queue<T>::frontPos() {
    return front;
}
 
// Utility function to return the size of the queue
template <class X> int Queue<X>::size() {
    return count;
}

// Utility function to check if the queue is empty or not
template <class T> bool Queue<T>::isEmpty() {
    return (size() == 0);
}
 
// Utility function to check if the queue is full or not
template <class T> bool Queue<T>::isFull() {
    return (size() == capacity);
}

