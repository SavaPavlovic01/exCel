#ifndef _CSV_PARSER_
#define _CSV_PARSER_

#include "table_structs.hpp"
#include <unordered_map>
#include "Cell.hpp"

typedef struct 
{
  int prec;
  int asoc;
  int id;
} op_info;
 
class Parser{
  
  std::vector<Token*> tokens;
  unsigned int cur_token_pos=0;
  std::unordered_map<std::string,Cell*> cell_map;

  public:

  const std::unordered_map<std::string,op_info> op_info_map={
    {"+",{1,0,0}},
    {"-",{1,0,1}},
    {"*",{2,0,2}},
    {"/",{2,0,3}},
    {"^",{3,1,4}}
  };

  Parser(std::vector<Token*> tokens){this->tokens=tokens;}

  Parser() {};

  Tree_structs* get_atom();

  Tree_structs* calc_expr(int prec);

  std::unordered_map<std::string,Cell*>& parse();

  Cell* parse_cell(std::string cell_pos,std::string content);

};

#endif