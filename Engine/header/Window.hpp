#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <string>

namespace Engine{

enum windowFlag{
    INVISIBLE   = 0x1,
    FULLSCREEN  = 0x2,
    BORDERLESS  = 0x4
};

class Window{
    public:
        Window();
        ~Window();

        int create(std::string title,unsigned int width,unsigned int height,unsigned int currentFlag);

        void clear();
        
        void clearColor(float r,float g, float b,float a);

        void clearDepth(float d);

        void swapBuffer();

        int getwidth(){
            return width;
        }
        int getHeight(){
            return height;
        }
    private:
        SDL_Window* sdlwindow;

        unsigned int width;
        unsigned int height;        
};

}

#endif 