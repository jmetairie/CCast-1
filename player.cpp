#include <math.h>

#include "SDL2/SDL.h"
#include "level.cpp"
#include "const_trig.cpp"

#ifndef __PLAYER_H__
#define __PLAYER_H__

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

    Player() {
      this->leave = true ;
      this->x = 0 ;
      this->y = 0 ;
      this->angle = 0 ;
      this->speed_angle = __DEFAULT_ANGLE_SPEED__ ;
      this->speed_step = __DEFAULT_STEP_SPEED__ ;
    }

    Player(float x, float y) {
      this->leave = true ;
      this->x = x ;
      this->y = y ;
      this->angle = 0 ;
      this->speed_angle = __DEFAULT_ANGLE_SPEED__ ;
      this->speed_step = __DEFAULT_STEP_SPEED__ ;
    }

    ~Player() { }


    void set_x(float x) {
      this->x = x ;
    }

    void set_y(float y) {
      this->y = y ;
    }

    float get_x() {
      return this->x ;
    }

    float get_y() {
      return this->y ;
    }

     int get_angle() {
      return this->angle ;
    }

    bool get_leave() {
      return this->leave ;
    }

    void set_level(Level* my_level) {
      this->array = my_level->get_array() ;
    }


    // input_from_keyboard
    // input: void
    // return: void.
    void input_from_keyboard() {
      SDL_Event event;
      int delta_s, delta_a ;
      float new_x, new_y ;
      delta_s = delta_a = 0 ;
      while(SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN) {
          switch(event.key.keysym.sym) {
            case SDLK_LEFT: delta_a = -1 ; break ;
            case SDLK_RIGHT: delta_a = 1 ; break ;
            case SDLK_UP: delta_s = 1 ; break ;
            case SDLK_DOWN: delta_s = -1 ; break ;
            default: break ;
          } // end switch
        } // else key is released.
        else if (event.type == SDL_KEYUP) {
          switch(event.key.keysym.sym) {
            case SDLK_LEFT: delta_a = 0 ; break ;
            case SDLK_RIGHT: delta_a = 0 ; break ;
            case SDLK_UP: delta_s = 0 ; break ;
            case SDLK_DOWN: delta_s = 0 ; break ;
            default: break ;
          } // end switch
        }
        else if (event.type == SDL_QUIT) {
          this->leave = false ;
        } // end if
      } // end while loop.
      // Update coordinates.
      // /!\ For now, collision engine is in the Player class but should be moved soon.

      this->angle += delta_a*this->speed_angle ;
      if (this->angle < 0) { this->angle += 3600 ; }
      if (this->angle >= 3600) { this->angle -= 3600 ; }

      //std::cerr << this->angle << std::endl ;


      new_x = this->x+this->speed_step*const_trig::fast_cos(this->angle)*delta_s ;
      if (!this->array[(int) this->y][(int) new_x]) { this->x = new_x ;}
      new_y = this->y+this->speed_step*const_trig::fast_sin(this->angle)*delta_s ;
      if (!this->array[(int) new_y][(int) this->x]) { this->y = new_y ;}


    } // end function


} ;

#endif
