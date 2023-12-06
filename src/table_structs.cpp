#include "../inc/table_structs.hpp"
#include <unordered_map>
#include "../inc/Cell.hpp"

int Binary_op::accept(Tree_struct_visitor* visitor) {return visitor->visit_binary_op(this);}

int Unary_op::accept(Tree_struct_visitor* visitor) {return visitor->visit_unary(this);}

int Func_op::accept(Tree_struct_visitor* visitor) {return visitor->visit_func_op(this);}

int Num_node::accept(Tree_struct_visitor* visitor) {return visitor->visit_num_node(this);}

int Var_node::accept(Tree_struct_visitor* visitor) {return visitor->visit_var_node(this);}