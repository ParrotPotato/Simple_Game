#include "../header/Engine.hpp"

#include <SDL2/SDL.h>

namespace Engine
{
int init(){
        SDL_Init(SDL_INIT_EVERYTHING);
        SDL_GL_SetSwapInterval(0);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
}
}
