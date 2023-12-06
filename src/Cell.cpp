#include "../inc/Cell.hpp"

Cell::Cell(std::string pos,std::string str){
    type=Cell_type::STRING_CELL;
    this->position=pos;
    this->str_val=str;
}

Cell::Cell(std::string pos,int val){
    type=Cell_type::NUM_CELL;
    this->position=pos;
    this->num_val=val;
}

Cell::Cell(std::string pos,Tree_structs* root){
    type=Cell_type::EXPR_CELL;
    this->position=pos;
    this->expr_val=root;
}

int Cell::get_val(Tree_struct_visitor* visitor){
        if(type==Cell_type::NUM_CELL) return num_val;
        if(type==Cell_type::EXPR_CELL){
            if(!calced) {
                calculated_val=expr_val->accept(visitor);
                calced=true;
            }
            return calculated_val;
        }
        return -100;
    }