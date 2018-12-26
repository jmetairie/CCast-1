#include <iostream>
#include "level.cpp"


int main() {
  level my_level("level.lvl") ;
  for(int i=0;i<my_level.get_height();i++)
  {
    for(int j=0;j<my_level.get_width();j++)
    {
      std::cout << my_level.get_array()[i][j] ;
    } // end for j.
    std::cout << std::endl ;
  } // end for i.
  return 0 ;
}
