#include "../inc/table_structs.hpp"

int Binary_op::get_val(){
    int left_val=left->get_val();
    int right_val=right->get_val();
    int res=0;

    switch ((int)op){
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

int Func_op::get_val(){
    int cnt=0;
    int sum=0;
    for(auto cur_arg:this->args){
        
        cnt++;
        int add=cur_arg->get_val();
        //std::cout<<"ARG "<<cnt<<" "<<add<<std::endl;
        sum+=add;
    }
    return sum/cnt;
}

int Unary_op::get_val(){
    std::cout<<"Not implemented"<<std::endl;
    return 1;
}

int Var_node::get_val(){
    std::cout<<"Not implemented"<<std::endl;
    return 2;
}