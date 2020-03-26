#include "SDL2/SDL.h"
#include "player.h"
#include "const_trig.h"
#include <stdlib.h>
#include <iostream>

#include "bitmap.h"

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

    // Map

    static unsigned int** map ;
    static int map_height ;
    static int map_width ;

    // Display

    static SDL_Surface * image ;
    static SDL_Texture * texture ;

    static unsigned char* floor_surface ;


  public:
	static void init(SDL_Renderer* renderer, Level* level_arg);
    static void render(SDL_Renderer* renderer, Player* my_player);

} ;





