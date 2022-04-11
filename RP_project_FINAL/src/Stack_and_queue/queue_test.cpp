#include<iostream>
#include "queue.h"

using namespace std;

//Main code to call mazes and functions
int main() {

    cout << " TEST FOR QUEUE STRUCT "<< endl; 
    Queue<int> q;
    int a;
 
    q.push(1);
    q.push(2);
    q.push(3);
 
    cout << "The front element is " << q.frontPos() << endl;
    cout << "The rear element is " << q.topPos() << endl;
     
    cout << "The queue size is " << q.size() << endl;
 
    q.pop();
    q.pop();
    q.pop();
 
    if (q.isEmpty()) {
        cout << "The queue is empty\n";
    }
    else {
        cout << "The queue is not empty\n";
    }

return 0;

}
