#include <sstream>
#include <string>
#include <unistd.h>
#include <math.h>


#include <time.h>
#include <iostream>

#include "SDL2/SDL.h"


#include "level.h"
#include "player.h"
#include "ray_engine.h"




int main(int argc, char* argv[])
{
    Level my_level("level.lvl") ;
    Player my_player(1.5, 1.5) ;
    my_player.set_level(&my_level) ;




    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        SDL_Window* window = NULL;
        SDL_Renderer* renderer = NULL;
        if (SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer) == 0) {
            // SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN) ;
            SDL_bool done = SDL_FALSE;
            Ray_engine::init(renderer, &my_level) ;
            while (my_player.get_leave()) {
              clock_t begin = clock();
              // Ctrl
              my_player.input_from_keyboard() ;
              Ray_engine::render(renderer, &my_player) ;
              clock_t end = clock();
              std::cerr << CLOCKS_PER_SEC/(double)(end - begin) << std::endl ;
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
