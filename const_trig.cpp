
#include "const_trig.h"

// Should be between 0 and 360*10.
float const_trig::fast_cos(unsigned int angle) {
	if (angle < 900) {
	  return const_trig::COS[angle] ;
	}
	else if (angle < 1800) {
	  return -const_trig::COS[1800-angle] ;
	}
	else if (angle < 2700) {
	  return -const_trig::COS[angle-1800] ;
	}
	else {
	  return const_trig::COS[3600-angle] ;
	}
} // end function.

float const_trig::fast_sin(unsigned int angle) {
  int temp_angle = angle-900 ;
  if (temp_angle < 0 ) { temp_angle += 3600 ; }
  return fast_cos(temp_angle) ;
}




/*#include <time.h>
#include <math.h>
#include <iostream>

#define MAX 1000000
#define to_radian(angle) angle/180.0*3.14159 ;

int main() {
  clock_t tStart = clock();
  float acc = 0 ;
  for(int i=0;i<MAX;i++) {
    float angle = to_radian(i%360) ;
    acc+= cos(angle) ;
  }
  std::cout << acc << std::endl ;
  std::cout << (double)(clock() - tStart)/CLOCKS_PER_SEC << std::endl ;


  tStart = clock();
  acc = 0 ;
  for(int i=0;i<MAX;i++) {
    float angle = (i*10)%3600 ;
    acc+= const_trig::fast_cos(angle) ;
  }
  std::cout << acc << std::endl ;
  std::cout << (double)(clock() - tStart)/CLOCKS_PER_SEC << std::endl ;


  return 0 ;
}*/
