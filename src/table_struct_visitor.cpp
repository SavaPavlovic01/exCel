#include "../inc/table_struct_visitor.hpp"
#include "../inc/table_structs.hpp"

int Visitor::visit_binary_op(Binary_op* op){
    int left_val=op->left->accept(this);
    int right_val=op->right->accept(this);
    int res=0;

    switch ((int)op->op){
        case 0:
            res=left_val+right_val;
            break;
        case 1:
            res=left_val-right_val;
            break;
        case 2:
            res=left_val*right_val;
            break;
        case 3:
            if(right_val==0){
                std::cout<<"Division by zero"<<std::endl;
                exit(-5);
            }
            res=left_val/right_val;
            break;
        case 4:
            //C FUNC
            //todo: implement
            std::cout<<"Not implemented"<<std::endl;
            res=0;
    }

    return res;
}

int Visitor::visit_num_node(Num_node* node){
    return node->num;
}

int Visitor::visit_func_op(Func_op* node){
    int cnt=0;
    int sum=0;
    for(auto cur_arg:node->args){
        
        cnt++;
        int add=cur_arg->accept(this);
        //std::cout<<"ARG "<<cnt<<" "<<add<<std::endl;
        sum+=add;
    }
    return sum/cnt;
}

int Visitor::visit_var_node(Var_node* node){
    auto itr=cell_map.find(node->var);
    if(itr==cell_map.end()) return -100;
    if(itr->second->type==Cell_type::NUM_CELL) return itr->second->num_val;
    return itr->second->expr_val->accept(this);
}

int Visitor::visit_unary(Unary_op* op){
    return 5;
}