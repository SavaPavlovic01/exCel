#include "../inc/csv_parser.hpp"
#include <stdlib.h> 
#include "../inc/csv_lexer.hpp"

Tree_structs* Parser::get_atom(){
  Token* cur_token=tokens[cur_token_pos++];
  if(cur_token->type==Token_types::NUM) {
    //std::cout<<"Found atom NUM: "<<cur_token->val<<std::endl;
    return new Num_node(atoi(cur_token->val.c_str()));
  }
  if(cur_token->type==Token_types::STRING){
    if(tokens[cur_token_pos]->type==Token_types::NUM){
      //std::cout<<"Found atom VAR: "<<cur_token->val+tokens[cur_token_pos]->val<<std::endl;
      return new Var_node(cur_token->val+tokens[cur_token_pos++]->val);
    } else if(tokens[cur_token_pos]->type==Token_types::LEFT_PAR){
      //std::cout<<"Found atom FUNC: "<<cur_token->val<<std::endl;
      
      Func_op* ret_val=new Func_op(cur_token->val);
      if(!ret_val) return ret_val;
      while(tokens[cur_token_pos]->type!=Token_types::RIGHT_PAR){
        cur_token_pos++;
        Tree_structs* temp=calc_expr(1);
        if(!temp) return temp;
        ret_val->add_arg(temp);
        if(tokens[cur_token_pos]->type!=Token_types::COMMA && tokens[cur_token_pos]->type!=Token_types::RIGHT_PAR) return nullptr; 
      }
      cur_token_pos++;
      return ret_val;
    }
  }
  if(cur_token->type==Token_types::LEFT_PAR){
    Tree_structs* val=calc_expr(1);
    if(!val) return val;
    if(tokens[cur_token_pos++]->type!=Token_types::RIGHT_PAR){
      std::cout<<"( not closed"<<std::endl;
      return nullptr;
    }
    return val;
  }
  std::cout<<"Unexpected symbol "<< cur_token->val<< std::endl;
  return nullptr;
}

Tree_structs* Parser::calc_expr(int prec){
  Tree_structs* left=get_atom();
  if(!left) return left;
  while(true){
    Token* cur_token=tokens[cur_token_pos];
    if(cur_token->type!=Token_types::BINARY_OP) break;
    op_info cur_op=op_info_map.find(cur_token->val)->second;
    if(cur_op.prec<prec) break;
    int next_prec=(cur_op.asoc)?cur_op.prec:cur_op.prec+1;
    cur_token_pos++;
    Tree_structs* right=calc_expr(next_prec);
    if(!right) return right;
    left=new Binary_op(left,right,(Operation)cur_op.id);
  }  

  return left;
}

std::unordered_map<std::string,Cell*>& Parser::parse(){
  char row='a';
  int col=1;
  while(tokens[cur_token_pos]->type!=Token_types::END){
    Token* cur_token=tokens[cur_token_pos];
    std::string new_pos=std::string{row}+std::to_string(col);
    if(cur_token->type==Token_types::EQUALS){
      cur_token_pos++;
      cell_map[new_pos]=new Cell(new_pos,calc_expr(1));
    } else if((cur_token->type==Token_types::NUM) && 
        (tokens[cur_token_pos+1]->type==Token_types::COMMA || tokens[cur_token_pos+1]->type==Token_types::NEW_LINE ||
        tokens[cur_token_pos+1]->type==Token_types::END)){
      cur_token_pos++;
      cell_map[new_pos]=new Cell(new_pos,atoi(cur_token->val.c_str()));
    } else {
      std::string conncat;
      while(cur_token->type==Token_types::STRING || cur_token->type==Token_types::NUM){
        conncat=conncat+cur_token->val;
        cur_token=tokens[++cur_token_pos];
      }
      cell_map[new_pos]=new Cell(new_pos,conncat);
        
    }
    if(tokens[cur_token_pos]->type==Token_types::COMMA) col++;
    else if (tokens[cur_token_pos]->type==Token_types::NEW_LINE){
      row++;
      col=1;
    }
    if(tokens[cur_token_pos]->type==Token_types::END) break;
    cur_token_pos++;
    
  }
  return cell_map;
}

Cell* Parser::parse_cell(std::string cell_pos,std::string content){
  Lexer lexer(content);
  lexer.get_tokens();
  tokens=lexer.send_tokens();
  while(tokens[cur_token_pos]->type!=Token_types::END){
    Token* cur_token=tokens[cur_token_pos];
    if(cur_token->type==Token_types::EQUALS){
      cur_token_pos++;
      return new Cell(cell_pos,calc_expr(1));
    } else if((cur_token->type==Token_types::NUM) && 
        (tokens[cur_token_pos+1]->type==Token_types::COMMA || tokens[cur_token_pos+1]->type==Token_types::NEW_LINE ||
        tokens[cur_token_pos+1]->type==Token_types::END)){
      cur_token_pos++;
      return new Cell(cell_pos,atoi(cur_token->val.c_str()));
    } else {
      std::string conncat;
      while(cur_token->type==Token_types::STRING || cur_token->type==Token_types::NUM){
        conncat=conncat+cur_token->val;
        cur_token=tokens[++cur_token_pos];
      }
      return new Cell(cell_pos,conncat);
        
    }
    
    if(tokens[cur_token_pos]->type==Token_types::END) break;
    cur_token_pos++;
    
  }
}