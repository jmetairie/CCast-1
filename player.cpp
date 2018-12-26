#include "SDL2/SDL.h"

class Player {

  private:

    bool leave ;
    unsigned int x ;
    unsigned int y ;

  public:

    Player() {
      this->leave = true ;
      this->x = 0 ;
      this->y = 0 ;
    }

    Player(unsigned int x, unsigned int y) {
      this->leave = true ;
      this->x = x ;
      this->y = y ;
    }

    ~Player() { }


    void set_x(unsigned int x) {
      this->x = x ;
    }

    void set_y(unsigned int y) {
      this->y = y ;
    }

    unsigned int get_x() {
      return this->x ;
    }

    unsigned int get_y() {
      return this->y ;
    }

    bool get_leave() {
      return this->leave ;
    }


    // input_from_keyboard
    // input: void
    // return: void.
    void input_from_keyboard() {
      SDL_Event event;
      int delta_x, delta_y ;
      delta_x = delta_y = 0 ;
      while(SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN) {
          switch(event.key.keysym.sym) {
            case SDLK_LEFT: delta_x = -1 ; break ;
            case SDLK_RIGHT: delta_x = 1 ; break ;
            case SDLK_UP: delta_y = -1 ; break ;
            case SDLK_DOWN: delta_y = 1 ; break ;
            default: break ;
          } // end switch
        } // else key is released.
        else if (event.type == SDL_KEYUP) {
          switch(event.key.keysym.sym) {
            case SDLK_LEFT: delta_x = 0 ; break ;
            case SDLK_RIGHT: delta_x = 0 ; break ;
            case SDLK_UP: delta_y = 0 ; break ;
            case SDLK_DOWN: delta_y = 0 ; break ;
            default: break ;
          } // end switch
        }
        else if (event.type == SDL_QUIT) {
          this->leave = false ;
        } // end if
      } // end while loop.
      // Update coordinates.
      this->x += delta_x ;
      this->y += delta_y ;
    }


} ;
