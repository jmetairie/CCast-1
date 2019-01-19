#include "SDL2/SDL.h"
#include "player.cpp"
#include "const_trig.cpp"
#include <stdlib.h>

#include <iostream>

#include "bitmap.cpp"

#define PI 3.14159
#define to_radian(angle) (angle/180.0)*PI

#define __RAY_ENGINE_WALL_HEIGHT__ 2

#define DEBUG(val) std::cerr << val << std::endl ;

class Ray_engine {


  private:

    // Engine Parameters
    static unsigned int height ;
    static unsigned int half_height ;
    static unsigned int width  ;
    static unsigned int FOV ;
    static unsigned int HALF_FOV ;
    static unsigned int angle_step ;

    // Engine Inner Variables

    static SDL_Surface * image ;
    static SDL_Texture * texture ;

    static unsigned char* floor_surface ;





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
    static void init(SDL_Renderer* renderer)
    {
      height = 480 ;
      half_height = height >> 1 ;
      width = 640 ;
      FOV = 640 ; // 10*FOV/width should be a integer
      HALF_FOV = FOV >> 1 ;
      angle_step = FOV/width ;
      /* Textures Loading */
      image = SDL_LoadBMP("media/img/wall_1.bmp");
      texture = SDL_CreateTextureFromSurface(renderer, image);
      floor_surface = readBMP("media/img/floor_0.bmp") ;

    }

    static void render(SDL_Renderer* renderer, Player* my_player, Level* my_level){
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
      SDL_RenderClear(renderer) ;
      SDL_Event event;
      //display_grid(renderer, my_level) ;
      // Compute Screen Orientation
      int level_height = my_level->get_height() ;
      int level_width = my_level->get_width() ;
      float x_screen = const_trig::fast_sin(my_player->get_angle()) ;
      float y_screen = -const_trig::fast_cos(my_player->get_angle()) ;
      float player_angle = my_player->get_angle() ;
      // display player


      // (x,y) is the player position on the map array
      float x = my_player->get_x() ;
      float y = my_player->get_y() ;
      int angle = (player_angle-HALF_FOV) ;
      if (angle > 3600) { angle -= 3600 ; }
      if (angle < 0) { angle += 3600 ; }
      // For each ray ... !
      for(int w = 0 ; w < width ; w++) {
        //std::cerr << angle << std::endl ;
        //////////////////////////////
        // Variable Initialization //
        /////////////////////////////
        float x_ray_length, y_ray_length ; // position of the current ray
        float x_ray_vector = const_trig::fast_cos(angle) ;
        float y_ray_vector = const_trig::fast_sin(angle) ;
        float length_x_ray_vector = abs(1/x_ray_vector) ;
        float length_y_ray_vector = abs(1/y_ray_vector) ;
        int x_map = (int) x ;
        int y_map = (int) y ;
        ///////////////////////////////
        // Initialization before DDA //
        ///////////////////////////////
        int delta_x, delta_y ;
        // Starting with x_ray
        if (x_ray_vector < 0) {
          delta_x = -1 ;
          x_ray_length = (x-int(x))*length_x_ray_vector ;
        }
        else {
          delta_x = 1 ;
          x_ray_length = (1+int(x)-x)*length_x_ray_vector ;
        }
        // Then with y_ray
        if (y_ray_vector < 0) {
          delta_y = -1 ;
          y_ray_length = (y-int(y))*length_y_ray_vector ;
        }
        else {
          delta_y = 1 ;
          y_ray_length = (1+int(y)-y)*length_y_ray_vector ;
        }
        //////////////////
        // Running DDA //
        /////////////////
        bool hit = false ; // DEB TODO
        bool x_side = false ; // true if ray cross a x-axis in the end.
        int cpt = 0 ;
        while(!hit) { // should be hit variable ;) for debug purpose only.
          if (x_ray_length < y_ray_length) {
            x_map+= delta_x ;
            x_ray_length += length_x_ray_vector ;
            x_side = false ;
          }
          else {
            y_map+= delta_y ;
            y_ray_length += length_y_ray_vector ;
            x_side = true ;
          }
          if (x_map < 0 || x_map >= level_width) { hit = true ; }
          else if (y_map < 0 || y_map >= level_height)  { hit = true ;  }
          else if (my_level->get_array()[y_map][x_map]) { hit = true ;  }
        }
        /////////////////////////////
        // Distance Computing part //
        /////////////////////////////
        float x_edge, y_edge ;
        x_ray_length -= length_x_ray_vector ;
        y_ray_length -= length_y_ray_vector ;
        float ray_length ;
        float fisheye_correction = const_trig::fast_cos(abs(angle-player_angle)) ;
        if (x_side) { ray_length = y_ray_length ; } else { ray_length = x_ray_length ; }
        x_edge =  ((x+x_ray_vector*ray_length)) ;
        y_edge =  ((y+y_ray_vector*ray_length)) ;
        ray_length *= fisheye_correction ;

        int wall_height = (int) ((216.0*__RAY_ENGINE_WALL_HEIGHT__)/ray_length) ; //wall_height >>=1 ;
        int y_wall_start = half_height-(wall_height >>1) ;
        int y_wall_end = half_height+(wall_height>>1) ;

        ///////////////////////
        // Jump to next ray  //
        ///////////////////////
        angle += angle_step ;
        if (angle > 3600) { angle -= 3600 ; }
        //std::cerr << absolute_angle << std::endl ;

        /////////////////////
        // Rendering Part //
        /////////////////////

        // Wall Part //
        int texture_x ;
        if (x_side) { texture_x = int((x_edge-int(x_edge))*256) ; } else { texture_x = int((y_edge-int(y_edge))*256) ;}
        SDL_Rect Source = {texture_x, 0, 1, 256} ;
        SDL_Rect Dest = {w, y_wall_start, 1, wall_height} ;
        SDL_RenderCopy(renderer, texture, &Source, &Dest) ;

        // Floor //

        //
        for(unsigned int y_floor=y_wall_end;y_floor<height;y_floor++) {
          float floor_dist = (1.0*height/((y_floor << 1)-height))/fisheye_correction ; // mettre ces données dans une LUT ?
          float tmp_x = floor_dist*x_ray_vector+x ;
          float tmp_y = floor_dist*y_ray_vector+y ;
          int floor_x = (tmp_x-int(tmp_x))*256 ;
          int floor_y = (tmp_y-int(tmp_y))*256 ;

          int indx = (floor_y << 8)+floor_x ;
          indx = (indx << 1) + indx ; // indx*=3
          //std::cerr << "height " << floor_y << " - " << (floor_y) << " - " << indx << std::endl ;
          unsigned char r = floor_surface[indx] ;
          unsigned char g = floor_surface[indx+1] ;
          unsigned char b = floor_surface[indx+2] ;
          SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
          SDL_RenderDrawPoint(renderer, w, y_floor) ;
        }


      } // end while for ray casting.

      SDL_RenderPresent(renderer) ;
    }

} ;

unsigned int Ray_engine::height = 480 ;
unsigned int Ray_engine::half_height = 240 ;
unsigned int Ray_engine::width = 640 ;
unsigned int Ray_engine::FOV = 960 ;
unsigned int Ray_engine::HALF_FOV = 480 ;
unsigned int Ray_engine::angle_step = Ray_engine::FOV/Ray_engine::width ;
SDL_Surface* Ray_engine::image = NULL ;
SDL_Texture* Ray_engine::texture = NULL ;
unsigned char* Ray_engine::floor_surface = NULL ;
