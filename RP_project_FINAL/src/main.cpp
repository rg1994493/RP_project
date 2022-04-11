#include<iostream>
#include "maze.h"

using namespace std;

//Main code to call mazes and functions
int main(int argc, char *argv[]) {  

  string file = argv[1];  //Lines of the input file
  Maze maze1;
  maze1.init(file);
  cout<<endl;
  
  cout<<"MAZE SHAPE: "<<endl;
  cout<<endl;
  maze1.print();

  string type;
  cout << "Type BFS for the breadth first solution or DFS for Depth First search "<< endl;
  cin>>type;
  
  while(type!="BFS" && type!="DFS") {
   cout<<" Enter the option correctly, BFS or DFS " <<endl;
   cin>>type;
  }
  
  cout<<endl;
  cout << " Searching solution... "<< endl;
  cout<<"MAZE SOLUTION: "<<endl;
  cout<<endl;
  
  if(type == "DFS") {
    maze1.solveDFS();
    } else {
    maze1.solveBFS();
  }
      
  cout << " States explored "<< maze1.num_explored << endl;
  cout << " Solution "<< endl;
  maze1.print();


return 0;

}
