#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <bits/stdc++.h> // for reverse vector
#include <vector>

#include "node.h"
#include "stack.h"
#include "queue.h"

using namespace std;
using IntVector = vector<int>; //Needs the std namespace
using IntMatrix = vector<vector<int>>; //Needs the std namespace

class Maze {

  public:
    int width = 0; 
    int height = 0;
    int num_explored = 0;
    IntVector startPos;
    IntVector goalPos;
    IntMatrix obsArr;
    IntMatrix solution;
    IntMatrix explored;
            
  public:
  
  void init(string file){ //Open the maze file and check goal and start
      string line;  //Lines of the input file
      ifstream myfile (file);
      cout << file << endl;
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

    for(int i = 0; i < height; ++i){
      for(int j = 0; j < width; ++j){
        cout << mazeDraw[i][j];
      }
      cout<<endl;
    }
    cout<<endl;

    if (!explored.empty()){
    for(auto i = explored.begin() ; i< explored.end() ; i++){
      IntVector n = *i;
      mazeDraw[n[0]][n[1]] = "-";
    }

    cout<<endl;
    cout<<"TOTAL NODES EXPLORED: "<<endl;
    cout<<"Node explored: "<< num_explored << endl;
    cout<<endl;
    for(int i = 0; i < height; ++i){
      for(int j = 0; j < width; ++j){
        cout << mazeDraw[i][j];
      }
      cout<<endl;
    }
    cout<<endl;
    }
    
  }

  IntMatrix neighbors(IntVector state){
  
    int row = state[0];
    int col = state[1]; 
    
    IntMatrix adj;
    IntVector up = {row-1,col};
    IntVector down = {row+1,col};
    IntVector left = {row,col-1};
    IntVector right = {row,col+1};
    
    if(row-1>=0) adj.push_back(up); 
    if(row+1<height) adj.push_back(down); 
    if(col-1>=0) adj.push_back(left);
    if(col+1<width) adj.push_back(right); 

    IntMatrix result;
    bool wall = false;
    for(auto i = adj.begin(); i!= adj.end(); i++){ //Check which neighbor is not a wall
      wall = false;
      for(auto j = obsArr.begin(); j!= obsArr.end(); j++){
        if (*i == *j ) {wall = true; break;};
      }
      if (wall == false) result.push_back(*i);
    }
    return result;
  }

  void solveDFS(){
    num_explored = 0;
        
    Node* s = new Node(startPos);
    Node* node = new Node({0,0},&s);

    Stack<Node> frontier; // Stack just for DFS mode
        
    frontier.push(*s);
    
    //IntMatrix explored; //explored nodes states to avoid repeat
    IntMatrix cells; //To recover the solution after finding the path
    
    while(true){
      
      if (frontier.isEmpty()){
        throw std::invalid_argument(" No solution ");
      }
                  
      node = new Node(frontier.pop());
      
      num_explored += 1;

      if (node->state == goalPos){
        
        cells = {};
        
        while(node->parent != NULL){
          node = node->parent;
          cells.push_back(node->state);
        }

        reverse(cells.begin(), cells.end());
        solution = cells;
        return;        
      }

      explored.push_back(node->state); //add node to explored
      
      //if it is not yet the solution check neighbors
      IntMatrix v = neighbors(node->state);
      
      for(auto i = v.begin() ; i!= v.end(); i++){
        
        bool exp = false;
        for(auto j = explored.begin() ; j!= explored.end(); j++) { //Check if neighbors are in explored
          if(*i == *j){ exp = true; break;} 
        } 
        if(exp == false){
          bool front = false;
          for(int j = frontier.frontPos(); j<= frontier.topPos() ; j++){ //check if neighbors are in frontier already
            if (frontier.get(j).state == *i) {front = true; break;} 
          }
          if(front == false) { //If there are not in any, add them to frontier
            Node* child = new Node(*i,&node);
            frontier.push(*child);
          } 
        }                 
      }            
    }
  }
  
  void solveBFS(){
    num_explored = 0;
        
    Node* s = new Node(startPos);
    Node* node = new Node({0,0},&s);

    Queue<Node> frontier; // Queue just for BFS mode
    
    frontier.push(*s);
    
    //IntMatrix explored; //explored nodes states to avoid repeat
    IntMatrix cells; //To recover the solution after finding the path
    
    while(true){
      
      if (frontier.isEmpty()){
        throw std::invalid_argument(" No solution ");
      }
                  
      node = new Node(frontier.pop());
      
      num_explored += 1;

      if (node->state == goalPos){
        
        cells = {};
        
        while(node->parent != NULL){
          node = node->parent;
          cells.push_back(node->state);
        }

        reverse(cells.begin(), cells.end());
        solution = cells;
        return;        
      }

      explored.push_back(node->state); //add node to explored
      
      //if it is not yet the solution check neighbors
      IntMatrix v = neighbors(node->state);
      
      for(auto i = v.begin() ; i!= v.end(); i++){
        
        bool exp = false;
        for(auto j = explored.begin() ; j!= explored.end(); j++) { //Check if neighbors are in explored
          if(*i == *j){ exp = true; break;} 
        } 
        if(exp == false){
          bool front = false;
          for(int j = frontier.frontPos(); j<= frontier.topPos() ; j++){ //check if neighbors are in frontier already
            if (frontier.get(j).state == *i) {front = true; break;} 
          }
          if(front == false) { //If there are not in any, add them to frontier
            Node* child = new Node(*i,&node);
            frontier.push(*child);
          } 
        }                 
      }            
     }
   }
  
};
