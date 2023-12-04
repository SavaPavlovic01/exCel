#ifndef _TOKEN_HPP_
#define _TOKEN_HPP_
#include <string>
#include <iostream>

enum class Token_types{
  EQUALS,LEFT_PAR,RIGHT_PAR,COMMA,PLUS,MINUS,SLASH,STAR,NEW_LINE,
  STRING,NUM,POSITION,BINARY_OP,END
};

class Token{
  public:
  Token_types type;
  int row;
  int col;
  std::string val;

  Token(Token_types,int,int,const char*);
  Token(Token_types,int,int,std::string);
  Token(Token_types);
  
  friend std::ostream& operator<<(std::ostream& stream,const Token& token){
    stream<<"Type:"<<(int)token.type;
    if(token.val.size()>0) stream<<" val:"<<token.val;
    stream<<std::endl;
    return stream;
  }
};

#endif