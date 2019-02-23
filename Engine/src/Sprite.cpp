#include "../header/Sprite.hpp"
#include "../header/Vertex.hpp"
#include "../header/ResourceManager.hpp"
#include <iostream>

namespace Engine{

Sprite::Sprite(){
    _vboID = 0;
    _x = _y = _height = _width = 0;
}
Sprite::~Sprite(){
    if(_vboID == 0)
        glDeleteBuffers(1,&_vboID);
}

void Sprite::init(float x,float y,float width,float height,std::string texturePath){
    
    _x = x;
    _y = y;
    _width = width;
    _height = _height;

    
    if(_vboID == 0)
        glGenBuffers(1,&_vboID);
            
    texture = ResourceManager::getTexture(texturePath);
    Vertex vertexData[6];
    
    //triangle 1
    vertexData[0].position.setPosition(x + width,y + height);
    vertexData[0].color.setColor(0,225,0,225);
    vertexData[0].uv.setUV(1.0f,1.0f);

    vertexData[1].position.setPosition(x ,y + height);
    vertexData[1].color.setColor(225,0,0,225);
    vertexData[1].uv.setUV(0.0f,1.0f);

    vertexData[2].position.setPosition(x ,y);
    vertexData[2].color.setColor(0,0,225,225);
    vertexData[2].uv.setUV(0.0f,0.0f);

    //triangle 2 
    vertexData[3].position.setPosition(x + width,y );
    vertexData[3].color.setColor(0,225,0,225);
    vertexData[3].uv.setUV(1.0f,0.0f);

    vertexData[4].position.setPosition(x + width,y + height);
    vertexData[4].color.setColor(0,225,0,225);
    vertexData[4].uv.setUV(1.0f,1.0f);

    vertexData[5].position.setPosition(x ,y );
    vertexData[5].color.setColor(0,0,225,225);
    vertexData[5].uv.setUV(0.0f,0.0f);

    //Binding the created buffer 
    glBindBuffer(GL_ARRAY_BUFFER,_vboID);
    //Putting data into the created buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER,0);
}
//glEnableattribArray is called by the GLSL program when the program is under use and 
//glDisableattribarray is called by the GLSL program when the program is not under use 
void Sprite::draw(){
    glBindTexture(GL_TEXTURE_2D,texture.id);
    glBindBuffer(GL_ARRAY_BUFFER,_vboID);
    //position attribute pointer 
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex,position));
    //color attribute pointer 
    glVertexAttribPointer(1,4,GL_UNSIGNED_BYTE,GL_TRUE,sizeof(Vertex),(void*)offsetof(Vertex,color));
    //UV attribute poitner 
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void *)offsetof(Vertex,uv));

    //drawing the triangles 
    glDrawArrays(GL_TRIANGLES,0,6);
    glBindBuffer(GL_ARRAY_BUFFER,0);    
    glBindTexture(GL_TEXTURE_2D,0);
}

}