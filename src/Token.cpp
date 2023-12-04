#include "../inc/Token.hpp"

Token::Token(Token_types type,int row,int col,const char* val){
  this->type=type;
  this->row=row;
  this->col=col;
  this->val=std::string(val);
}

Token::Token(Token_types type,int row,int col,std::string val){
  this->type=type;
  this->row=row;
  this->col=col;
  this->val=std::string(val);
}

Token::Token(Token_types type){
  this->type=type;
}