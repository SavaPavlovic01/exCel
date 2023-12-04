#ifndef _TABLE_STRUCT_VISITOR_HPP_
#define _TABLE_STRUCT_VISITOR_HPP_

#include "table_structs.hpp"

class Tree_struct_visitor {
  public:
  virtual int visit_binary_op(Binary_op*);
  virtual int visit_unary(Unary_op*);
  virtual int visit_func_op(Func_op*);
  virtual int visit_num_node(Num_node*);
  virtual int visit_var_node(Var_node*);
  // TREBA SVE DA SE DODA
};

#endif