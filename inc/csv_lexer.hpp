#ifndef _CSV_LEXER_HPP_
#define _CSV_LEXER_HPP_

#include <string>
#include "Token.hpp"
#include <stdio.h>
#include <vector>

//WHAT ARE THE TOKENS????
// =, STRING, NESTO TIPA A1, NUM,=call(ime_fje,...args), +, -, *, /, (, )

class Lexer{

  std::string path;
  std::vector<Token*> tokens;
  unsigned int pos=0;
  int line=0;
  std::string stream;

  int open_file(const char*);

  char consume_next_char(){
    if(pos>stream.size()) return 0;
    else return stream[pos++];
  }

  char get_next_char(){
    if(pos>stream.size()) return 0;
    else return stream[pos];
  }

  public:

  Lexer(const char* path){open_file(path);}  

  Lexer(const std::string content){stream=content;}

  friend std::ostream& operator<<(std::ostream& stream,const Lexer& lexer){
    for(auto i:lexer.tokens){
      stream<<*i;
    }
    return stream;
  }

  void get_tokens();

  std::vector<Token*> send_tokens(){return tokens;}
};

#endif