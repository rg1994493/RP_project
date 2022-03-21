#include<iostream>
#include "dfs.h"
#include <fstream>
#include <iostream>
#include <string>
#include <bits/stdc++.h> // for reverse vector
#include <vector>

using namespace std;
using IntVector=vector<int>; //Needs the std namespace
using IntMatrix=vector<vector<int>>; //Needs the std namespace

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
      bool isFull();
      bool isEmpty();
  
    private:
      // Taking data member top
      int top;

      // Initialising stack with initial size
      T st[SIZE];
    
};
 
// To initialise top to -1(default constructor)
template <class T> Stack<T>::Stack() { top = -1;}
template <class T> int Stack<T>::topPos() { return top;}
 
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
      // As top can not exceeds th size
      return 0;
}
 
template <class T> T Stack<T>::pop(){
    // Initialising a variable to store popped element
    T popped_element = st[top];
 
    // Decreasing the top as element is getting out from the stack
    top--;
    return popped_element;
}
 
template <class T> T Stack<T>::topElement(){
    // Initialising a variable to store top element
    T top_element = st[top];
 
    return top_element;
}

template <class T> T Stack<T>::get( int pos ){
    // Initialising a variable to store top element
    T element;
    if(pos <= top && pos>= 0)
      element = st[pos];
 
    return element;
}

//******************************************************

class Node {
    public:
    Node(){
     this->state = {};
     this->parent = nullptr; // Pointer initialized with null
     cout<<"NULL CONSTRUCTOR"<<endl;
     
    }

    Node(IntVector state){
     this->state = state;
     this->parent = nullptr; // Pointer initialized with null
     cout << "node constructor" << state[0] << "," << state[1] <<endl;
     
    }

    Node(IntVector state, Node& _parent){
      this->state = state;
      this->parent = &_parent;
    }

    IntVector getParentState(){
      return parent->state;
    }

    IntVector getState(){
      return state;
    }

    Node getParentNode(){
      return *parent;
    }

    //op =, deep copy
    Node& operator =(const Node& other) {
      this->state = other.state;
      this->parent = other.parent;
    return *this;
    }
       
    public:
    IntVector state;
    Node* parent;
  
};

//******************************************************
class Maze {

  public:
    int width = 0; 
    int height = 0;
    int num_explored = 0;
    IntVector startPos;
    IntVector goalPos;
    IntMatrix obsArr;
    IntMatrix solution;
            
  public:
  
  void init(string file){
  //Open the maze file and check goal and start
    string line;  //Lines of the input file
    ifstream myfile (file);
    
    if (myfile.is_open())  {

      int start = 0; //To check if there is a start character
      int goal = 0;  //To check if there is a goal character
            
      char ch;
      int n = 0; //column # of the char 
      
      while (myfile >> noskipws >> ch) { //Read the file by chars
        
        n++; //Counts all the characters in the line

        if(ch == ('A')){
          start ++;
          startPos.push_back(height); //minus one, arrays start in zero
          startPos.push_back(n-1);
        }
        else if(ch == ('B')){
          goal ++;
          goalPos.push_back(height);
          goalPos.push_back(n-1);
        }
        else if(ch == ('\n')){
          if(height == 0 ) width = n - 1; //subtract the /n char
          height ++;
          n = 0;
        } else if (ch == ('#')) {
          obsArr.push_back({height,n-1});
        }
      }
    
      if(start != 1)
        throw std::invalid_argument(" No start or multiple start points ");

      if(goal != 1)
        throw std::invalid_argument(" No goal or multiple goals ");

      cout << "Everything fine!" << endl;

      //Determine width and height of maze
      cout<< "Height of maze is:  "<< height << endl;

      cout<< "Width of maze is: "<< width << endl;

      //Position of Start
      cout<< "Position of Start  "<<  startPos[0] << " " << startPos[1]   << endl;

      //Position of Goal
      cout<< "Position of Goal  "<< goalPos[0] << " " << goalPos[1]   << endl;

      myfile.close();

    } else {
      cout << "Unable to open file"; 
    }
  
  }

  void print(){
    string** mazeDraw;
    mazeDraw = new string* [height];
    for(int i = 0; i < height; ++i) mazeDraw[i] = new string[width];

    for(int i = 0; i < height; ++i){
      for(int j = 0; j < width; ++j){
        mazeDraw[i][j] = " ";
      }
    }
    
    for(auto i = solution.begin() ; i< solution.end() ; i++){
      IntVector n = *i;
      mazeDraw[n[0]][n[1]] = "*";
    }

    mazeDraw[startPos[0]][startPos[1]] = "A";
    mazeDraw[goalPos[0]][goalPos[1]] = "B";
    
    for(int i=0;i<obsArr.size();i++){
      int xtemp = 0;
      int ytemp = 0;
      xtemp = obsArr[i][0];
      ytemp = obsArr[i][1];
      mazeDraw[xtemp][ytemp] = "â–ˆ";
    }

    cout<<endl;
    cout<<"MAZE: "<<endl;
    cout<<endl;
    for(int i = 0; i < height; ++i){
      for(int j = 0; j < width; ++j){
        cout << mazeDraw[i][j];
      }
      cout<<endl;
    }
    cout<<endl;
    
  }

  IntMatrix neighbors(IntVector state){
    int row = state[0];
    int col = state[1]; 
    cout<<"row"<<row<<"col"<<col<<endl; // ERASEEE  
    IntMatrix adj;
    IntVector up = {row-1,col};
    IntVector down = {row+1,col};
    IntVector left = {row,col-1};
    IntVector right = {row,col+1};
    if(row-1>=0) {adj.push_back(up); cout<<"UP"<<endl;} 
    if(row+1<height) {adj.push_back(down); cout<<"DOWN"<<endl;}
    if(col-1>=0) {adj.push_back(left); cout<<"LEFT"<<endl;}
    if(col+1<width) {adj.push_back(right); cout<<"RIGHT"<<endl;}

    IntMatrix result;
    bool wall = false;
    for(auto i = adj.begin(); i!= adj.end(); i++){ //Check which neighbor is not a wall
      wall = false;
      for(auto j = obsArr.begin(); j!= obsArr.end(); j++){
        if (*i == *j ) {wall = true; cout<<"ITS A WALL"<<endl;break;};
      }
      if (wall == false) {result.push_back(*i);cout<<"SPACE ADDED"<<endl;}
    }
    return result;
  }

  void solve(){
            
  }
  
};
//******************************************************
int main(int argc, char *argv[]) {

string file = argv [1];
Maze maze1;
maze1.init(file);
maze1.print();

return 0;
}




 
