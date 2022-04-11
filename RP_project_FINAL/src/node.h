//Class that includes object Nodes with a parent and a position in the maze

#pragma once
#include <iostream>
#include <vector>

using namespace std;
using IntVector = vector<int>; //Needs the std namespace
using IntMatrix = vector<vector<int>>; //Needs the std namespace

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
  }

  Node(IntVector _state, Node** _parent){
  this->parent = *_parent;
  this->state = _state;
  return;
  }

  Node (const Node& n){
    this->parent = n.parent;
    this->state = n.state;
  }

  void setNode(IntVector _state, Node** _parent){
    this->parent = *_parent;
    this->state = _state;
  } 

};
