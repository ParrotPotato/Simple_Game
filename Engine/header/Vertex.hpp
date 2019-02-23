#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <GL/glew.h>
#include <string>

namespace Engine{

struct Position{
    float x;
    float y;
    Position(){
        x = 0;
        y = 0;
    }
    void setPosition(float x,float y){
        this->x = x;
        this->y = y;
    }
};

struct Color{
    GLbyte r;
    GLbyte g;
    GLbyte b;
    GLbyte a;
    Color(){
        r = a = g = b = 0 ;
    }
    void setColor(int r,int g,int b,int a){
        this->r = (GLbyte)r;
        this->g = (GLbyte)g;
        this->b = (GLbyte)b;
        this->a = (GLbyte)a;
    }
};

struct UV{
    float u;
    float v;
    void setUV(float u,float v){
        this->u = u;
        this->v = v;
    }
};

struct Vertex{
    Position position;
    Color color;
    UV uv;

    std::string toString(){
        std::string dataString = "Position : (" + std::to_string(position.x) + "," + std::to_string(position.y) + 
                                 ") Color : " + std::to_string(color.r) + "," + std::to_string(color.g) + "," + std::to_string(color.b) + "," + std::to_string(color.a) + 
                                 ") UV  : (" + std::to_string(uv.u) + "," + std::to_string(uv.v) + ")" ;
        return dataString;
    }
};

}
#endif