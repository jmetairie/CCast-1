#include "SDL2/SDL.h"
#include "player.cpp"
#include "const_trig.cpp"
#include <stdlib.h>

#include <iostream>

#define PI 3.14159
#define to_radian(angle) (angle/180.0)*PI

class Ray_engine {


  private:

    // Engine Parameters
    static unsigned int height ;
    static unsigned int width  ;
    static unsigned int FOV ;
    static unsigned int HALF_FOV ;
    static unsigned int angle_step ;

    // Engine Inner Variables





    static void display_grid(SDL_Renderer* renderer, Level* my_level)
    {
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
      for(int y=0; y<my_level->get_height(); y++)
      {
        for(int x=0; x<my_level->get_width(); x++ )
        {
          if (my_level->get_array()[y][x]) {
            SDL_Rect Rect = {(x << 5), (y << 5), 32, 32} ;
            SDL_RenderFillRect(renderer, &Rect) ;
          }
        } // end x loop
      } // end y loop
    } // end function


  public:
    static void init()
    {
      height = 640 ;
      width = 480 ;
      FOV = 960 ; // 10*FOV/width should be a integer
      HALF_FOV = FOV >> 1 ;
      angle_step = FOV/width ;
    }

    static void render(SDL_Renderer* renderer, Player* my_player, Level* my_level){
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
      SDL_RenderClear(renderer) ;
      SDL_Event event;
      display_grid(renderer, my_level) ;
      // Compute Screen Orientation
      float x_screen = const_trig::fast_sin(my_player->get_angle()) ;
      float y_screen = -const_trig::fast_cos(my_player->get_angle()) ;
      // display player
      SDL_SetRenderDrawColor(renderer, 125, 65, 65, SDL_ALPHA_OPAQUE);

      int angle = (my_player->get_angle()-HALF_FOV) ;
      if (angle > 3600) { angle -= 3600 ; }
      if (angle < 0) { angle += 3600 ; }


      // (x,y) is the player position on the map array
      float x = my_player->get_x() ;
      float y = my_player->get_y() ;

      unsigned int x_map = (int) x ;
      unsigned int y_map = (int) y ;

      // For each ray ... !
      for(int w = 0 ; w < width ; w++) {
        //std::cerr << angle << std::endl ;
        //////////////////////////////
        // Variable Initialization //
        /////////////////////////////
        float x_ray_pos, y_ray_pos ; // position of the current ray
        float x_ray_vector = const_trig::fast_cos(angle) ;
        float y_ray_vector = const_trig::fast_sin(angle) ;
        float length_x_ray = abs(1/x_ray_vector) ;
        float length_y_ray = abs(1/y_ray_vector) ;
        ///////////////////////////////
        // Initialization before DDA //
        ///////////////////////////////
        /*
        int delta_x, delta_y ;
        // Starting with x_ray
        if (x_ray_vector < 0) {
          delta_x = -1 ;
          x_ray_pos = (x-int(x))*length_x_ray ;
        }
        else {
          delta_x = 1 ;
          x_ray_pos = (1+int(x)-x)*length_x_ray ;
        }
        // Then with y_ray
        if (y_ray_vector < 0) {
          delta_y = -1 ;
          y_ray_pos = (y-int(y))*length_y_ray ;
        }
        else {
          delta_y = 1 ;
          y_ray_pos = (1+int(y)-y)*length_y_ray ;
        }*/
        //////////////////
        // Running DDA //
        /////////////////
        bool hit = false ;
        bool x_side = false ; // true if ray cross a x-axis in the end.
        int cpt = 0 ;
        /*while(cpt < 0) { // should be hit variable ;) for debug purpose only.
          if (x_ray_pos < y_ray_pos) {
            x_map+= delta_x ;
            x_ray_pos += length_x_ray ;
            x_side = true ;
          }
          else {
            y_map+= delta_y ;
            y_ray_pos += length_y_ray ;
            x_side = false ;
          }
          //std::cerr << y_map << std::endl ;
          //if (my_level->get_array()[y_map][x_map]) { hit = true ; }
          cpt++ ;
        }*/
        //////////////////
        // Display part //
        //////////////////
        int x_edge, y_edge ;
        std::cerr << angle << " " << w << std::endl ;
        x_edge = (int) (x+x_ray_vector)*32 ;
        y_edge = (int) (y+y_ray_vector)*32 ;
        /*if (x_side) {
          x_edge = (int) (x+x_ray_vector)*32 ;
          y_edge = (int) (y+y_ray_vector)*32 ;
        }
        else {
          x_edge = (int) (x+x_ray_vector)*32 ;
          y_edge = (int) (y+y_ray_vector)*32 ;
        }*/
        SDL_RenderDrawLine(renderer, x*32, y*32, x_edge, y_edge) ;
        angle += angle_step ;
        if (angle > 3600) { angle -= 3600 ; }
      } // end while for ray casting.
      SDL_RenderPresent(renderer) ;
    }

} ;

unsigned int Ray_engine::height = 640 ;
unsigned int Ray_engine::width = 480 ;
unsigned int Ray_engine::FOV = 960 ;
unsigned int Ray_engine::HALF_FOV = 480 ;
unsigned int Ray_engine::angle_step = Ray_engine::FOV/Ray_engine::width ;
