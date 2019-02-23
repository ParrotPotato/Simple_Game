#ifndef SPRITE_H
#define SPRITE_H

#include <GL/glew.h>
#include <string>

#include "GLTexture.hpp"

namespace Engine{

class Sprite{
    public:
        Sprite();
        ~Sprite();

        void init(float x,float y,float width,float height,std::string texturePath);
        void draw();

    private:
        int _x;
        int _y;
        int _width;
        int _height;

        GLuint _vboID;
        GLTexture texture;
};

}

#endif