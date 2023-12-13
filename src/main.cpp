#include "../inc/buffer.hpp"
#include "../inc/csv_lexer.hpp"
#include <iostream>
#include "../inc/csv_parser.hpp"
#include "../inc/table_struct_visitor.hpp"

enum class Color{
  WHITE,GRAY,BLACK
};

bool check_cycle_dfs(std::unordered_map<std::string,std::unordered_set<std::string>*>& dep_map,std::unordered_map<std::string,Color>& visited,
  const std::string& node){
    std::unordered_set<std::string> *cur_set;
    
    if(dep_map.find(node)!=dep_map.end()){
      cur_set=dep_map[node];
    }else {
      visited[node]=Color::BLACK;
      return false;
    }

    visited[node]=Color::GRAY;
    for(auto& it:*cur_set){
      if(visited[it]==Color::GRAY) return true;
      if(visited[it]==Color::BLACK) continue;
      if(check_cycle_dfs(dep_map,visited,it)){
        return true;
      }
    }
    visited[node]=Color::BLACK;
    return false;
}

bool check_cycle(std::unordered_map<std::string,std::unordered_set<std::string>*>& dep_map){
  std::unordered_map<std::string,Color> visited;

  for(auto& it:dep_map){
    visited[it.first]=Color::WHITE;
  }

  for(auto& it:dep_map){
    if(visited[it.first]==Color::WHITE){
      if(check_cycle_dfs(dep_map,visited,it.first)){
        return true;
      }
    }
  }
  return false;
}

int main(){
  Lexer lex("test/test1.csv");
  lex.get_tokens();
  //std::cout<<lex<<std::endl;
  Parser parser(lex.send_tokens());
  //Tree_structs* res=parser.calc_expr(1);
  //std::cout<<res->get_val()<<std::endl;
  std::unordered_map<std::string,Cell*> map;
  std::unordered_map<std::string,std::unordered_set<std::string>*> dependecy_map;
  map=parser.parse();
  Visitor visitor(map);
  std::vector<Cell*> uncalculated_cells;
  int error_code=0;
  for(auto& it:map){
    
    switch (it.second->type){
      case Cell_type::STRING_CELL:
        std::cout<<it.first<<" ";
        std::cout<<"STRING_CELL "<<it.second->str_val<<std::endl;
        break;
      case Cell_type::NUM_CELL:
        
        std::cout<<it.first<<" ";
        std::cout<<"NUM_CELL "<<it.second->get_val(&visitor,error_code)<<std::endl;
        break;
      case Cell_type::EXPR_CELL:
        it.second->expr_val->calc_depends();
        
        for(auto elem:it.second->expr_val->get_dependecys()){
          auto itr=dependecy_map.find(elem);
          if(itr==dependecy_map.end()){
            auto new_set=new std::unordered_set<std::string>();
            dependecy_map[elem]=new_set;
            new_set->insert(it.second->position);
          }else {
            dependecy_map[elem]->insert(it.first);
          }
        }
        //it.second->get_val(&visitor,error_code);
        //if(error_code==-1) uncalculated_cells.push_back(it.second);
        //else std::cout<<it.first<<" "<<it.second->get_val(&visitor,error_code)<<std::endl;
        uncalculated_cells.push_back(it.second);
        error_code=0;
        break;
    }
  }
  if(check_cycle(dependecy_map)){
    std::cout<<"CIRCULAR DEPENDECY"<<std::endl;
    exit(-10);
  }
  bool has_changed=true;
  int to_calc=uncalculated_cells.size();
  while(has_changed && to_calc>0){
    has_changed=false;
    for(auto i=uncalculated_cells.begin();i!=uncalculated_cells.end();i++){
      int error=0;
      Cell* cur_cell=*i.base();
      if(cur_cell->is_calced()) continue;
      cur_cell->get_val(&visitor,error);
      if(error==-1) continue;
      else {
        std::cout<<cur_cell->position<<" "<<cur_cell->get_val(&visitor,error)<<std::endl;
        to_calc--;
        has_changed=true;
      }
      error=0;
    }
  }
  
  return 0;
}