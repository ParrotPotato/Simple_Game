#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H

#include <GL/glew.h>
#include "Vertex.hpp"
#include <glm/glm.hpp>
#include <vector>

namespace Engine{

enum class GlyphSortType{
    NONE = 0 ,
    FRONT_TO_BACK = 1 ,
    BACK_TO_FRONT = 2 ,
    TEXTURE = 4 
};


struct Glyph{
    GLuint texture;
    float depth;

    Vertex topLeft;
    Vertex topRight;
    Vertex bottomRight;
    Vertex bottomLeft;
};

class RenderBatch{
    public:
        RenderBatch(GLuint offsetValue,GLuint numVerticesValue, GLuint textureValue){
            offset = offsetValue;
            numVertices = numVerticesValue;
            texture = textureValue;
        }
        GLuint offset;
        GLuint numVertices;
        GLuint texture;
};


class SpriteBatch{
    public:
        SpriteBatch();
        ~SpriteBatch();

        void init();

        void begin(int sortType = (int)GlyphSortType::TEXTURE);
        void end();


        void draw(const glm::vec4& destRect,const glm::vec4& uvRect, GLuint texture,float depth ,const Color& color);
        void createRenderBatches();
        void renderBatch();

    private:
        
        void createVertexArray();
        void sortGlyphs();

        static bool compareFrontToBack(Glyph * a,Glyph *b);
        static bool compareBackToFront(Glyph * a,Glyph *b);
        static bool compareTexture(Glyph * a,Glyph *b);

        GLuint _vbo;
        GLuint _vao;

        std::vector<Glyph*> glyphs;
        std::vector<RenderBatch> renderBatches;

        int _sortType;
};


}
#endif 