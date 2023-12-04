#ifndef _BUFFER_HPP
#define _BUFFER_HPP
#include <string>


class Buffer{
  unsigned int cur_pos;
  std::string buffer;

  public:
  
  Buffer();

  void insert(char);

  void clear();

  void get_content(std::string&);
};

#endif