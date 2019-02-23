#include "../header/Error.hpp"
#include <iostream>
#include <SDL2/SDL.h>

namespace Engine{

void fatalError(std::string errorString){
    std::cerr << "Fatal Error : \n\t";
    std::cerr << errorString   << std::endl;

    SDL_Quit();
    exit(0);
}

}
