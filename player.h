

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <math.h>

#include "SDL2/SDL.h"
#include "level.h"
#include "const_trig.h"

#define __DEFAULT_ANGLE_SPEED__ 100 // 1 does actually mean 0.1 degree
#define __DEFAULT_STEP_SPEED__ 0.05

class Player {

  private:

    bool leave ;
    float x ;
    float y ;
    float speed_step ;
    int angle, speed_angle ;
    unsigned int** array ;

  public:

    Player() ;
    Player(float x, float y);
    ~Player();

    void set_x(float x);
    void set_y(float y);
    float get_x();
    float get_y() ;
     int get_angle() ;
    bool get_leave();
    void set_level(Level* my_level);
    void input_from_keyboard();


} ;

#endif
