#include "../inc/csv_parser.hpp"
#include <stdlib.h> 

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
      while(tokens[cur_token_pos]->type!=Token_types::RIGHT_PAR){
        cur_token_pos++;
        ret_val->add_arg(calc_expr(1)); 
      }
      cur_token_pos++;
      return ret_val;
    }
  }
  if(cur_token->type==Token_types::LEFT_PAR){
    Tree_structs* val=calc_expr(1);
    if(tokens[cur_token_pos++]->type!=Token_types::RIGHT_PAR){
      std::cout<<"( not closed"<<std::endl;
      exit(-1);
    }
    return val;
  }
  std::cout<<"Unexpected symbol "<< cur_token->val<< std::endl;
  exit(-2);
  return nullptr;
}

Tree_structs* Parser::calc_expr(int prec){
  Tree_structs* left=get_atom();

  while(true){
    Token* cur_token=tokens[cur_token_pos];
    if(cur_token->type!=Token_types::BINARY_OP) break;
    op_info cur_op=op_info_map.find(cur_token->val)->second;
    if(cur_op.prec<prec) break;
    int next_prec=(cur_op.asoc)?cur_op.prec:cur_op.prec+1;
    cur_token_pos++;
    Tree_structs* right=calc_expr(next_prec);
    left=new Binary_op(left,right,(Operation)cur_op.id);
  }  

  return left;
}

