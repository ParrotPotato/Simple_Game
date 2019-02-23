#ifndef GLSLPROGRAM_HPP
#define GLSLPROGRAM_HPP

#include <string>
#include <GL/glew.h>
#include <vector>

#define GLM_ENABLE_EXPERIMENTAL

namespace Engine{

class GLSLProgram{
    public:
        void compileShaders(const std::string vertexShaderfilePath,const std::string fragmentShaderfilePath);
        void linkShaders();
        GLSLProgram();
        void addAttribute(std::string attribute);
        void useProgram();
        void unuseProgram();
        GLint getUniformLocation(std::string uniformName);
        GLuint getProgramID(){
            return program;
        }
    private:
        GLuint vertexShader;
        GLuint fragmentShader;
        GLuint program;
        std::vector<std::string> attributes;
};

}

#endif