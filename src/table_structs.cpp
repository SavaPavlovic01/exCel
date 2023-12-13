#include "../inc/table_structs.hpp"
#include <unordered_map>
#include "../inc/Cell.hpp"

int Binary_op::accept(Tree_struct_visitor* visitor,int& error_code) {return visitor->visit_binary_op(this,error_code);}

int Unary_op::accept(Tree_struct_visitor* visitor,int& error_code) {return visitor->visit_unary(this,error_code);}

int Func_op::accept(Tree_struct_visitor* visitor,int& error_code) {return visitor->visit_func_op(this,error_code);}

int Num_node::accept(Tree_struct_visitor* visitor,int& error_code) {return visitor->visit_num_node(this,error_code);}

int Var_node::accept(Tree_struct_visitor* visitor,int& error_code) {return visitor->visit_var_node(this,error_code);}