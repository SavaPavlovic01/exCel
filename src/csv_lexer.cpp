#include "../inc/csv_lexer.hpp"
#include "../inc/buffer.hpp"
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <streambuf>
#include <sstream>

int buffer_size=256;

int Lexer::open_file(const char* path){
  std::ifstream t(path);
  std::stringstream buffer;
  buffer << t.rdbuf();
  this->stream=std::string(buffer.str());
  return 0;
}

void Lexer::get_tokens(){
  char cur_char=consume_next_char();
  std::string buffer;
  while(cur_char!=0){
    switch (cur_char)
    {
      case '=':
        tokens.push_back(new Token(Token_types::EQUALS));
        break;
      case '(':
        tokens.push_back(new Token(Token_types::LEFT_PAR));
        break;
      case ')':
        tokens.push_back(new Token(Token_types::RIGHT_PAR));
        break;
      case '+':
        tokens.push_back(new Token(Token_types::BINARY_OP,0,0,std::string("+")));
        break;
      case '-':
        tokens.push_back(new Token(Token_types::BINARY_OP,0,0,std::string("-")));
        break;
      case '*':
        tokens.push_back(new Token(Token_types::BINARY_OP,0,0,std::string("*")));
        break;
      case '/':
        tokens.push_back(new Token(Token_types::BINARY_OP,0,0,std::string("/")));
        break;
      case ',':
        tokens.push_back(new Token(Token_types::COMMA));
        break;
      case '\n':
        tokens.push_back(new Token(Token_types::NEW_LINE));
        break;
      default:
        if(isdigit(cur_char)){
          buffer+=cur_char;
          while(isdigit(get_next_char())) buffer+=consume_next_char();
          tokens.push_back(new Token(Token_types::NUM,0,0,buffer));
          buffer.clear();
        }else if(isalpha(cur_char)){
          buffer+=cur_char;
          while(isalpha(get_next_char())) buffer+=consume_next_char();
          tokens.push_back(new Token(Token_types::STRING,0,0,buffer));
          buffer.clear();
        }else std::cout<<"Unrecognized symbol "<<cur_char<<std::endl;
        break;
    }
    cur_char=consume_next_char();
  }
  tokens.push_back(new Token(Token_types::END));
}
