#include <sstream>
#include <string>
#include <unistd.h>
#include "SDL2/SDL.h"

#include "level.cpp"
#include "player.cpp"



void display_grid(SDL_Renderer* renderer, Level* my_level)
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
  //SDL_RenderPresent(renderer) ;
} // end function


int main(int argc, char* argv[])
{
    Level my_level("level.lvl") ;
    Player my_player(48, 48) ;

    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        SDL_Window* window = NULL;
        SDL_Renderer* renderer = NULL;

        if (SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer) == 0) {
            SDL_bool done = SDL_FALSE;

            while (my_player.get_leave()) {
              // Ctrl
              my_player.input_from_keyboard() ;
              // Display
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                SDL_RenderClear(renderer) ;
                SDL_Event event;
                display_grid(renderer, &my_level) ;
                // display player
                SDL_SetRenderDrawColor(renderer, 125, 65, 65, SDL_ALPHA_OPAQUE);
                SDL_Rect Rect = {(int) my_player.get_x(), (int) my_player.get_y(), 10, 10} ;
                SDL_RenderFillRect(renderer, &Rect) ;
                SDL_RenderPresent(renderer) ;
                /*while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) {
                        done = SDL_TRUE;
                    }
                } // end while loop poll_event */
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
