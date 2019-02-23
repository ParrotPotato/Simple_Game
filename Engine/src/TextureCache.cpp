#include "../header/TextureCache.hpp"
#include "../header/ImageLoader.hpp"

#include <iostream>

namespace Engine{

TextureCache::TextureCache(){

}

TextureCache::~TextureCache(){

}

GLTexture TextureCache::getTexture(std::string texturePath){
    //The Actual iterator 
    //std::map<std::string,GLTexture>::iterator mit =  _textureMap.find(texturePath);

    //replacing it with an auto 

    //searches for the texture and look up it in the map 
    auto mit = _textureMap.find(texturePath);

    // If we didn't find the texture 
    // load and add the file to the texturecache 

    if(mit == _textureMap.end()){
        GLTexture newTexture = ImageLoader::loadPNG(texturePath);

        //std::pair <std::string,GLTexture> newPair(texturePath,newTexture);
        //but a simpler implementation

        _textureMap.insert(make_pair(texturePath,newTexture));
        return newTexture;
    }
    return mit->second;
}

}