#include "../header/Timing.hpp"

#include <SDL2/SDL.h>

namespace Engine{

FpsLimiter::FpsLimiter(){

}

FpsLimiter::~FpsLimiter(){

}

void FpsLimiter::init(float maxFps){
    setMaxFps(maxFps);

}

void FpsLimiter::setMaxFps(float maxFps){
    this->maxFps = maxFps;
}

void FpsLimiter::begin(){
    startTicks = SDL_GetTicks();
}

float FpsLimiter::end(){
    calculateFPS();

    float frameTicks = SDL_GetTicks() - startTicks; 
        if(1000.0/maxFps > frameTicks){
            SDL_Delay(1000.0/maxFps - frameTicks);
        }

    return fps;
}

void FpsLimiter::calculateFPS(){
    static bool initialised = false;
    static const unsigned int NUM_FRAMES = 10;
    static float frameTimes[NUM_FRAMES];

    static unsigned int currentFrame = 0 ;

    static float prevTicks = SDL_GetTicks();

    float currentTicks;
    currentTicks = SDL_GetTicks();

    frameTime = currentTicks - prevTicks ; 
    prevTicks = currentTicks;

    frameTimes[currentFrame % NUM_FRAMES] = frameTime;

    int count = 0  ;
    currentFrame++;
    if(currentFrame  == NUM_FRAMES){
        initialised = true;
    }
    currentFrame%=NUM_FRAMES;

    if(initialised == false){
        count = currentFrame;
    }else{
        count = NUM_FRAMES;
    }
    float frameTimeAverage = 0.0f;
    for(int i=0 ; i < count ; i++){
        frameTimeAverage += frameTimes[i];
    }

    frameTimeAverage /= count;

    if (frameTimeAverage > 0){
        fps = 1000/frameTimeAverage  ;
    }else {
        fps = 60 ;
    }

}

}