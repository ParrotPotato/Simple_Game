#ifndef TEXTURECACHE_H
#define TEXTURECACHE_H

#include "GLTexture.hpp"
#include <map>

#define GLM_ENABLE_EXPERIMENTAL

namespace Engine{

class TextureCache{
    public:
        TextureCache();
        ~TextureCache();

        GLTexture getTexture(std::string texturePath);

    private:
        std::map <std::string,GLTexture> _textureMap;
};

}
#endif 