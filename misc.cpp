#ifndef __MISC_H__

#include <string>
#define __MISC_H__
#define __MISC_LEFT__ true
#define __MISC_RIGHT__ false

namespace misc{

  //

  std::string split(std::string my_string, std::string my_substring, bool left) {
    unsigned int pos = my_string.find(my_substring) ;
    std::string local ;
    local = left ? my_string.substr(0, pos) : my_string.substr(pos+1) ;
    return local ;
  }



}

#endif
