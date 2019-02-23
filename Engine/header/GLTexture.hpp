#ifndef GLTEXTURE_H
#define GLTEXTURE_H

#include <GL/glew.h>

namespace Engine{

struct GLTexture{
    GLuint id;
    unsigned int width;
    unsigned int height;
};

}
#endif 