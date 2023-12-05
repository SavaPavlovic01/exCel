#ifndef _CELL_HPP
#define _CELL_HPP

#include <string>
#include <vector>
#include "table_structs.hpp"

enum class Cell_type{
    STRING_CELL,NUM_CELL,EXPR_CELL
};

class Cell{
    public:
    std::string position;
    std::string str_val;
    int num_val;
    Tree_structs* expr_val;
    Cell_type type;

    Cell(std::string pos,std::string str);
    Cell(std::string pos,int val);
    Cell(std::string pos,Tree_structs* root);
};

#endif