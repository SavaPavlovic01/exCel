#ifndef _CELL_HPP
#define _CELL_HPP

#include <string>
#include <vector>
#include "table_structs.hpp"

class Tree_structs;
class Tree_struct_visitor;

enum class Cell_type{
    STRING_CELL,NUM_CELL,EXPR_CELL
};

class Cell{
    int calculated_val=0;
    bool calced=false;
    public:
    std::string position;
    std::string str_val;
    int num_val;
    Tree_structs* expr_val;
    Cell_type type;
    std::string content=std::string("");

    Cell(std::string pos,std::string str);
    Cell(std::string pos,int val);
    Cell(std::string pos,Tree_structs* root);

    int get_val(Tree_struct_visitor* visitor,int& error_code);

    bool is_calced(){return calced;}
};

#endif