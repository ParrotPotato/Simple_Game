#include "../header/Window.hpp"
#include "../header/Error.hpp"

#include <GL/glew.h>
#include <iostream>

namespace Engine{
    
Window::Window(){
    sdlwindow = nullptr;
    height = 800;
    width = 800;
}

Window::~Window(){

}

int Window::create(std::string title,unsigned int width,unsigned int height,unsigned int currentFlag){
    this->width = width;
    this->height = height;

    Uint32 flags = SDL_WINDOW_OPENGL;

    if(currentFlag & INVISIBLE){
        flags |= SDL_WINDOW_HIDDEN;
    }
    if(currentFlag & FULLSCREEN){
        flags |= SDL_WINDOW_FULLSCREEN;
    }
    if(currentFlag & BORDERLESS){
        flags |= SDL_WINDOW_BORDERLESS;
    }
    
    sdlwindow = SDL_CreateWindow(title.c_str(),SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,flags);
    if(sdlwindow == nullptr){
        fatalError("MainGame unable to create window ");
    }
    SDL_GLContext context = SDL_GL_CreateContext(sdlwindow);
    if(context == nullptr){
        fatalError("Unable to create context");
    }

    GLenum errorCode = glewInit();
    if(errorCode != GLEW_OK)
        fatalError("Unable to initialise glew ");

    glClearColor(0.486, 0.509, 0.870, 1.0);

    const GLubyte *buffer = glGetString(GL_VERSION);
    std::cout << "OpenGL Version  : " <<   buffer << std::endl;

    //glClearColor(0.0,0.0,0.0,0.0);
    glClearDepth(1.0);   

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    return 0;
}

void Window::clear(){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}
        
void Window::clearColor(float r,float g, float b,float a){
    glClearColor(r,g,b,a);
}

void Window::clearDepth(float d){
    glClearDepth(d);
}

void Window::swapBuffer(){
    SDL_GL_SwapWindow(sdlwindow);
}

}