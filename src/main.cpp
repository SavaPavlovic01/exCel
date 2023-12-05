#include "../inc/buffer.hpp"
#include "../inc/csv_lexer.hpp"
#include <iostream>
#include "../inc/csv_parser.hpp"

int main(){
  Lexer lex("test/test1.csv");
  lex.get_tokens();
  //std::cout<<lex<<std::endl;
  Parser parser(lex.send_tokens());
  //Tree_structs* res=parser.calc_expr(1);
  //std::cout<<res->get_val()<<std::endl;
  std::unordered_map<std::string,Cell*> map;
  parser.parse(map);
  for(auto& it:map){
    std::cout<<it.first<<" ";
    switch (it.second->type){
      case Cell_type::STRING_CELL:
        std::cout<<"STRING_CELL "<<it.second->str_val<<std::endl;
        break;
      case Cell_type::NUM_CELL:
        std::cout<<"NUM_CELL "<<it.second->num_val<<std::endl;
        break;
      case Cell_type::EXPR_CELL:
        std::cout<<"EXPR_CELL "<<std::endl;
        break;
    }
  }
  return 0;
}