#include "SDL2/SDL.h"
#include "player.cpp"
#include "const_trig.cpp"

#define PI 3.14159
#define to_radian(angle) (angle/180.0)*PI

class Ray_engine {


  private:

    static int height ;
    static int width  ;
    static float FOV ;
    static float angle_step ;


    static void init()
    {
      height = 640 ;
      width = 480 ;
      FOV = to_radian(96) ; // 10*FOV/width should be a integer
      angle_step = width/FOV ;

    }

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
    static void render(SDL_Renderer* renderer, Player* my_player, Level* my_level){
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
      SDL_RenderClear(renderer) ;
      SDL_Event event;
      display_grid(renderer, my_level) ;
      // display player
      SDL_SetRenderDrawColor(renderer, 125, 65, 65, SDL_ALPHA_OPAQUE);
      int x, y ;
      x = (int) (my_player->get_x() * 32.0) ;
      y = (int) (my_player->get_y() * 32.0) ;
      int x_edge = (int) (const_trig::fast_cos(my_player->get_angle()) * 16)+x ;
      int y_edge = (int) (const_trig::fast_sin(my_player->get_angle()) * 16)+y ;
      SDL_RenderDrawLine(renderer, x, y, x_edge, y_edge) ;
      SDL_RenderPresent(renderer) ;
    }

} ;
