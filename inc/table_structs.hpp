#ifndef _EXPRESSION_HPP_
#define _EXPRESSION_HPP_

#include "Token.hpp"
#include <vector>


class Tree_structs{
  public:
  
  virtual int get_val()=0;
};

enum class Operation{
  ADD,SUB,MUL,DIV,FUNC
};

class Binary_op:public Tree_structs{
  public:
  Operation op;
  Tree_structs* left;
  Tree_structs* right;

  Binary_op(Tree_structs* left,Tree_structs* right,Operation op){
    this->left=left;
    this->right=right;
    this->op=op;
  }

  int get_val() override;
};

class Unary_op:public Tree_structs{
  public:
  Operation op;
  Tree_structs* arg;

  Unary_op(Tree_structs* arg,Operation op){
    this->op=op;
    this->arg=arg;
  }

  int get_val() override;
};

class Func_op:public Tree_structs{
  public:
  std::string op;
  std::vector<Tree_structs*> args;

  Func_op(std::string op) {this->op=op;}

  void add_arg(Tree_structs* arg){args.push_back(arg);}

  int get_val() override;
};

class Num_node:public Tree_structs{
  public:
  int num;

  Num_node(int num) {
    this->num=num;
  }

  int get_val() override {return num;}
};

class Var_node:public Tree_structs{
  public:
  std::string var;

  Var_node(std::string var){
    this->var=var;
  }

  int get_val() override;
};

#endif