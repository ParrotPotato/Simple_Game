#ifndef TIMING_H
#define TIMING_H

namespace Engine{



class FpsLimiter{
    public:
        FpsLimiter();
        ~FpsLimiter();

        void init(float maxFps);

        void setMaxFps(float maxFps);

        void begin();

        float end();
    private:
        void calculateFPS();

        float fps;
        float frameTime;
        float maxFps;
        unsigned int startTicks;
};

}

#endif