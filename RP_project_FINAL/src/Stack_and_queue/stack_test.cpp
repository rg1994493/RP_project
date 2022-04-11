#include<iostream>
#include "stack.h"

using namespace std;

//Main code to call mazes and functions
int main() {

cout << " TEST FOR STACK STRUCT "<< endl;
Stack<int> l;
int a ;
l.push(2);
l.push(3);
l.push(4);
cout << "topPos" <<  l.topPos() <<endl;

a = l.pop();

cout << "a" << a <<endl;
cout << "topPos" <<  l.topPos() <<endl;


return 0;

}
