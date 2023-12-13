#ifndef _TABLE_STRUCT_VISITOR_HPP_
#define _TABLE_STRUCT_VISITOR_HPP_

#include "table_structs.hpp"
#include "Cell.hpp"
#include <unordered_map>

class Binary_op;
class Unary_op;
class Func_op;
class Num_node;
class Var_node;
class Cell;
class Tree_struct_visitor {
  public:
  virtual int visit_binary_op(Binary_op*,int& error_code)=0;
  virtual int visit_unary(Unary_op*,int& error_code)=0;
  virtual int visit_func_op(Func_op*,int& error_code)=0;
  virtual int visit_num_node(Num_node*,int& error_code)=0;
  virtual int visit_var_node(Var_node*,int& error_code)=0;
};

class Visitor:public Tree_struct_visitor {
  std::unordered_map<std::string,Cell*> cell_map;
  public:

  Visitor(std::unordered_map<std::string,Cell*> map){
    cell_map=map;
  }

  int visit_binary_op(Binary_op*,int& error_code);
  int visit_unary(Unary_op*,int& error_code);
  int visit_func_op(Func_op*,int& error_code);
  int visit_num_node(Num_node*,int& error_code);
  int visit_var_node(Var_node*,int& error_code);
};

class Dependency_visitor:public Tree_struct_visitor{

};

#endif