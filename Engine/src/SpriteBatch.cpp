#include "../header/SpriteBatch.hpp"

#include <algorithm>
#include <iostream>

namespace Engine{

SpriteBatch::SpriteBatch():_vbo(0),_vao(0){
}

SpriteBatch::~SpriteBatch(){
    
}

void SpriteBatch::init(){
    createVertexArray();
}
// has a default parameter of TEXTURE sortnig 
void SpriteBatch::begin(int sortType){
    _sortType = sortType;
    renderBatches.clear();
    for(int i=0 ; i < glyphs.size() ; i++){
        delete glyphs[i];
    }
    glyphs.clear();
}
void SpriteBatch::end(){
    sortGlyphs();
    createRenderBatches();
}


void SpriteBatch::draw(const glm::vec4& destRect,const glm::vec4& uvRect, GLuint texture,float depth,const Color& color){
    Glyph * newGlyph = new Glyph();
    newGlyph->depth = depth;
    newGlyph->texture = texture;

    newGlyph->topLeft.color = color;
    newGlyph->topLeft.position.setPosition(destRect.x,destRect.y + destRect.w);
    newGlyph->topLeft.uv.setUV(uvRect.x,uvRect.y + uvRect.w);

    newGlyph->bottomLeft.color = color;
    newGlyph->bottomLeft.position.setPosition(destRect.x,destRect.y);
    newGlyph->bottomLeft.uv.setUV(uvRect.x,uvRect.y);
    
    newGlyph->bottomRight.color = color;
    newGlyph->bottomRight.position.setPosition(destRect.x + destRect.z ,destRect.y );
    newGlyph->bottomRight.uv.setUV(uvRect.x + uvRect.z ,uvRect.y);
    
    newGlyph->topRight.color = color;
    newGlyph->topRight.position.setPosition(destRect.x + destRect.z,destRect.y + destRect.w);
    newGlyph->topRight.uv.setUV(uvRect.x + uvRect.z ,uvRect.y + uvRect.w);
    
    glyphs.push_back(newGlyph);
}


void SpriteBatch::renderBatch(){

    glBindVertexArray(_vao);

    for(int i=0 ; i < renderBatches.size() ; i++){
        glBindTexture(  GL_TEXTURE_2D,renderBatches[i].texture);

        glDrawArrays(GL_TRIANGLES,renderBatches[i].offset,renderBatches[i].numVertices);
    }

    glBindVertexArray(0);

}

void SpriteBatch::createRenderBatches(){
    std::vector<Vertex> vertices;
    vertices.resize(glyphs.size() * 6);

    //checking that the glyphs are empty or not
    if(glyphs.empty())
        return ;

    int offset = 0 ;
    int cv = 0 ;
    // emplace_back calls the constructor by itself 
    renderBatches.emplace_back(offset,6,glyphs[0]->texture);
    vertices[cv++] = glyphs[0]->topRight;
    vertices[cv++] = glyphs[0]->topLeft;
    vertices[cv++] = glyphs[0]->bottomLeft;
    vertices[cv++] = glyphs[0]->bottomRight;
    vertices[cv++] = glyphs[0]->topRight;
    vertices[cv++] = glyphs[0]->bottomLeft;
    offset += 6;

    for(int cg = 1 ; cg < glyphs.size() ; cg++){
        if(glyphs[cg]->texture != glyphs[cg-1]->texture)
            renderBatches.emplace_back(offset,6,glyphs[cg]->texture);
        else{
            renderBatches.back().numVertices += 6;
        }
        vertices[cv++] = glyphs[cg]->topRight;
        vertices[cv++] = glyphs[cg]->topLeft;
        vertices[cv++] = glyphs[cg]->bottomLeft;
        vertices[cv++] = glyphs[cg]->bottomRight;
        vertices[cv++] = glyphs[cg]->topRight;
        vertices[cv++] = glyphs[cg]->bottomLeft;
        offset += 6;
    }

    glBindBuffer(GL_ARRAY_BUFFER,_vbo);

    // orphan the buffer 
    glBufferData(GL_ARRAY_BUFFER,vertices.size() * sizeof(Vertex) ,nullptr , GL_DYNAMIC_DRAW);
    // upload data 
    glBufferSubData(GL_ARRAY_BUFFER,0,vertices.size()*sizeof(Vertex),vertices.data());

    glBindBuffer(GL_ARRAY_BUFFER,0);
}

void SpriteBatch::createVertexArray(){
    if(_vao == 0){
        glGenVertexArrays(1,&_vao);
    }
    if(_vbo == 0){
        glGenBuffers(1,&_vbo);
    }
    glBindVertexArray(_vao);

    glBindBuffer(GL_ARRAY_BUFFER , _vbo);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);


    //position attribute pointer 
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex,position));
    //color attribute pointer 
    glVertexAttribPointer(1,4,GL_UNSIGNED_BYTE,GL_TRUE,sizeof(Vertex),(void*)offsetof(Vertex,color));
    //UV attribute poitner 
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void *)offsetof(Vertex,uv));

    glBindVertexArray(0);

}

void SpriteBatch::sortGlyphs(){
        if((int)(_sortType)&(int)GlyphSortType::FRONT_TO_BACK)
            std::stable_sort(glyphs.begin(),glyphs.end(),compareFrontToBack);
        if((int)(_sortType)&(int)GlyphSortType::BACK_TO_FRONT)
            std::stable_sort(glyphs.begin(),glyphs.end(),compareBackToFront);
        if((int)(_sortType)&(int)GlyphSortType::TEXTURE)
            std::stable_sort(glyphs.begin(),glyphs.end(),compareTexture);
}

bool SpriteBatch::compareFrontToBack(Glyph * a,Glyph *b){
    return (a->depth < b->depth)?true:false;
}

bool SpriteBatch::compareBackToFront(Glyph * a,Glyph *b){
    return (a->depth > b->depth)?true:false;
}

bool SpriteBatch::compareTexture(Glyph * a,Glyph *b){
    if(a->texture < b->texture){
        return true;
    }
    else if(a->texture > b->texture){
        return false;
    }else{
        return (a->depth > b->depth)?true:false;
    }
}


}