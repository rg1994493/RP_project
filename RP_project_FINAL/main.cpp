#include <fstream>
#include <iostream>
#include <string>
#include <bits/stdc++.h> // for reverse vector
#include <vector>

using namespace std;
using IntVector=vector<int>; //Needs the std namespace
using IntMatrix=vector<vector<int>>; //Needs the std namespace

//TODO AÑADIR METODOS EN LAS CLASESS

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
    // Initialising a variable to store top element
    T element;
    if(pos <= top && pos>= 0)
      element = st[pos];
 
    return element;
}

//******************************************************

class Node {       
  public:
  IntVector state;
  Node* parent;  

  public:
  
  Node(){
  this->state={};
  this->parent = NULL;
  }

  Node(IntVector _state){
  this->state = _state;
  this->parent = NULL;
  //cout << "node constructor" << state[0] << "," << state[1] <<endl;
  }

  Node(IntVector _state, Node** _parent){
  this->parent = *_parent;
  this->state = _state;
  return;
  //cout << "node constructor" << state[0] << "," << state[1] <<endl;
  //cout<< "parent constructor " << parent->state[0] << "," << parent->state[1] << endl;
  }

  Node (const Node& n){
    this->parent = n.parent;
    this->state = n.state;
  }

  void setNode(IntVector _state, Node** _parent){
    this->parent = *_parent;
    this->state = _state;
  }


  /*
  //op =, deep copy
  Node operator =(const Node* other) {
  this->state = other->state;
  this->parent = other->parent;  
  return *this;
  }
  */
  

};


//******************************************************
struct Maze {

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
      mazeDraw[xtemp][ytemp] = "█";
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
    cout<<"row"<<row<<"col"<<col<<endl; // BORRARRRRRR   
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
    num_explored = 0;
    cout<<"TEST 2;"<<endl;
    Node* aux = new Node({0,0});
    Node* s = new Node(startPos,&aux);
    Node* node = new Node({0,0},&s);
    Node* child = new Node({0,0},&s);
    
    cout<<"TEST 3;"<<endl; 
    Stack<Node> frontier; // Stack just for DFS mode
    frontier.push(*s);
    cout<<"TEST 4;"<<endl; 
    IntMatrix explored; //explored nodes states to avoid repeat
    IntMatrix cells; //To recover the solution after finding the path
    
    cout<<"TEST 1;"<<endl;
    
    while(true){
      
      if (frontier.isEmpty()){
        throw std::invalid_argument(" No solution ");
      }
      cout<<endl;
      cout<<"******************************************************************"<<endl;
      cout<<"Nodes explored: "<<num_explored<<endl; // BORRARR

      cout<<"node before popo "<<node->state[0]<<"."<<node->state[1]<<endl;
      cout<<"node parent before pop "<<node->parent->state[0]<<"."<<node->parent->state[1]<<endl;

      cout<<"TEST6"<<endl;
      cout<< "Current node data NODE CHILD after push" << frontier.topElement().state[0]<< "," << frontier.topElement().state[1] << endl;
      cout<< "Current node data NODE PARENT after push" << frontier.topElement().parent->state[0]<< "," << frontier.topElement().parent->state[1] << endl;
      node = new Node(frontier.pop());
      
      cout<<"TEST7"<<endl;       
      //cout<<frontier.isEmpty()<<endl; //BORRARRR

      cout<<"node after pop"<<node->state[0]<<"."<<node->state[1]<<endl;
      cout<<"node parent after pop "<<node->parent->state[0]<<"."<<node->parent->state[1]<<endl;
      
      num_explored += 1;

      if (node->state == goalPos){
        
        cout<<"FOUND THE GOAL!"<<endl; //BORRARRRRR
        
        cells = {};
        int t = 0;

        while(node->parent != NULL){
          cout<< "NODE: "<< node->state[0]<<","<< node->state[1] << endl;
          cout<< "NODE PARENT: "<< node->parent->state[0]<<","<< node->parent->state[1] << endl;
          node = node->parent;
          cells.push_back(node->state);
          t++;
        }

        reverse(cells.begin(), cells.end());
        solution = cells;
        cout<<"FOUND THE GOAL! 2"<<endl; //BORRARRRRR
        return;
        
      }

      explored.push_back(node->state); //add node to explored
      
      //if it is not yet the solution check neighbors
      IntMatrix v = neighbors(node->state);

      for(auto i = v.begin() ; i!= v.end(); i++){
        
        bool exp = false;
        for(auto j = explored.begin() ; j!= explored.end(); j++) {
          if(*i == *j){ exp = true; cout<<" Esta en explored!!!!!!!!!!!"<<endl;break;} //BORRARRRRR
        } 
        if(exp == false){
          bool front = false;
          for(int j = 0; j< frontier.topPos() ; j++){
            if (frontier.get(j).state == *i) {front = true; cout<<" Esta en frontier!!!!!!!!!!!"<<endl;break;} //BORRARRRRR 
          }
          if(front == false) {
            cout<<" NO esta en frontier !!!!!!!!!!!"<<endl; //BORRARRRRR
            cout<< "NODE " << node->state[0]<< "," << node->state[1] << endl;
            cout<< "NODE PARENT " << node->parent->state[0]<< "," << node->parent->state[1] << endl;
            child->setNode(*i,&node);
             
            cout<< "Current node data: CHILD  " << child->state[0] << "," << child->state[1] << endl;
            cout<< "Parent data: CHILD " << child->parent->state[0] << "," << child->parent->state[1] << endl;
            //cout<< "Current node data: NODE  " << node.state[0] << "," << node.state[1] << endl;
            //if(num_explored>1) cout<< "Parent data: NODE " << node.parent->state[0] << "," << node.parent->state[1] << endl;
            frontier.push(*child);
            cout<< "Current node data NODE CHILD after push" << frontier.topElement().state[0]<< "," << frontier.topElement().state[1] << endl;
            cout<< "Current node data NODE PARENT after push" << frontier.topElement().parent->state[0]<< "," << frontier.topElement().parent->state[1] << endl;
            cout<< "NODE after push " << node->state[0]<< "," << node->state[1] << endl;
            cout<< "NODE PARENT after push " << node->parent->state[0]<< "," << node->parent->state[1] << endl;                        
          } 

        }          
        
      }
            
    }
  }
  
};
//******************************************************
int main(int argc, char *argv[]) {

string file = argv [1];
Maze maze1;
maze1.init(file);
maze1.print();
maze1.solve();


return 0;
}







 
