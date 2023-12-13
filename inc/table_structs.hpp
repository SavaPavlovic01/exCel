#ifndef _EXPRESSION_HPP_
#define _EXPRESSION_HPP_

#include "Token.hpp"
#include <vector>
#include <unordered_set>
#include "table_struct_visitor.hpp"

class Tree_struct_visitor;
class Tree_structs{
  protected:
  std::unordered_set<std::string> dependecys;
  public:
  
  virtual int accept(Tree_struct_visitor*,int& error_code)=0;
  std::unordered_set<std::string>& get_dependecys(){
    return dependecys;
  }

  virtual void calc_depends()=0;
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

  int accept(Tree_struct_visitor* visitor,int& error_code) override;

  void calc_depends() override{
    dependecys.clear();
    left->calc_depends();
    right->calc_depends();
    for(auto str:left->get_dependecys()){
      dependecys.insert(str);
    }
    for(auto str:right->get_dependecys()){
      dependecys.insert(str);
    }
  }
};

class Unary_op:public Tree_structs{
  public:
  Operation op;
  Tree_structs* arg;

  Unary_op(Tree_structs* arg,Operation op){
    this->op=op;
    this->arg=arg;
  }

  int accept(Tree_struct_visitor* visitor,int& error_code) override;

  void calc_depends() override{
    dependecys.clear();
    arg->calc_depends();
    for(auto str:arg->get_dependecys()){
      dependecys.insert(str);
    }
  }
};

class Func_op:public Tree_structs{
  public:
  std::string op;
  std::vector<Tree_structs*> args;

  Func_op(std::string op) {this->op=op;}

  void add_arg(Tree_structs* arg){args.push_back(arg);}


  int accept(Tree_struct_visitor* visitor,int& error_code) override;

  void calc_depends() override{
    dependecys.clear();
    for(auto arg:args){
      arg->calc_depends();
      for(auto str:arg->get_dependecys()){
        dependecys.insert(str);
      }
    }
  }
};

class Num_node:public Tree_structs{
  public:
  int num;

  Num_node(int num) {
    this->num=num;
  }

  int accept(Tree_struct_visitor* visitor,int& error_code) override;

  void calc_depends() override{
    return;
  }
};

class Var_node:public Tree_structs{
  public:
  std::string var;

  Var_node(std::string var){
    this->var=var;
  }

  int accept(Tree_struct_visitor* visitor,int& error_code) override;

  void calc_depends() override {
    dependecys.clear();
    dependecys.insert(var);
  }
};

#endif