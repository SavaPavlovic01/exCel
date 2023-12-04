#include "../inc/buffer.hpp"
#include "../inc/csv_lexer.hpp"
#include <iostream>
#include "../inc/csv_parser.hpp"

int main(){
  Lexer lex("test/test1.csv");
  lex.get_tokens();
  std::cout<<lex<<std::endl;
  Parser parser(lex.send_tokens());
  Tree_structs* res=parser.calc_expr(1);
  std::cout<<res->get_val()<<std::endl;
  return 0;
}