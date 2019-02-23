#include "../header/ImageLoader.hpp"
#include "../header/picoPNG.hpp"
#include "../header/IOManager.hpp"
#include "../header/Error.hpp"

#include <GL/glew.h>

namespace Engine{

GLTexture ImageLoader::loadPNG(std::string filePath){
    GLTexture texture;


    std::vector<unsigned char> out;
    unsigned long width;
    unsigned long height;

    std::vector<unsigned char> in;

    if(IOManager::readFiletoBuffer(filePath,in) == false)
        fatalError("Texture file : " + filePath + " Unable to load in buffer ");


    int errorCode = decodePNG(out,width,height,&in[0],in.size());

    if(errorCode!=0)
        fatalError("picoPNG failed to load PNG image" + errorCode);

    glGenTextures(1,&(texture.id));

    texture.height = height;
    texture.width = width;

    glBindTexture(GL_TEXTURE_2D,texture.id);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,&out[0]);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);

    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,0);

    return texture;
    
}

}