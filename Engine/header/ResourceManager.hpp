#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "TextureCache.hpp"
#include <string>

namespace Engine{

class ResourceManager{
    static TextureCache _textureCache;
    
    public:
        static GLTexture getTexture(std::string texturePath);

};

}

#endif 