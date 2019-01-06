#include <sstream>
#include <string>
#include <unistd.h>
#include <math.h>

#include "SDL2/SDL.h"


#include "level.cpp"
#include "player.cpp"
#include "ray_engine.cpp"




int main(int argc, char* argv[])
{
    Level my_level("level.lvl") ;
    Player my_player(1.5, 1.5) ;
    my_player.set_level(&my_level) ;
    Ray_engine::init() ; 

    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        SDL_Window* window = NULL;
        SDL_Renderer* renderer = NULL;

        if (SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer) == 0) {
            SDL_bool done = SDL_FALSE;

            while (my_player.get_leave()) {
              // Ctrl
              my_player.input_from_keyboard() ;
              Ray_engine::render(renderer, &my_player, &my_level) ;
            } // end main loop
        }

        if (renderer) {
            SDL_DestroyRenderer(renderer);
        }
        if (window) {
            SDL_DestroyWindow(window);
        }
    }

    SDL_Quit();
    return 0;
}
