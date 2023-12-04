#include <string>
#include "../inc/buffer.hpp"


Buffer::Buffer(){
  this->cur_pos=0;
}

void Buffer::insert(char elem){
  if(buffer.length()<=cur_pos) buffer.push_back(elem);
  else buffer[cur_pos]=elem;
  cur_pos++;
}

void Buffer::clear(){
  cur_pos=0;
}

void Buffer::get_content(std::string& dest){
  dest=std::string(buffer,0,cur_pos);
}

