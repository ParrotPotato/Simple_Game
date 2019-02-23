#include "../header/GLSLProgram.hpp"
#include <fstream>
#include <iostream>
#include <vector>

namespace Engine{

std::string loadFile(const char* filePath);
GLuint compileShader(GLuint shaderID,const char* shader_source,const char* errorMessage);
GLuint linkProgram(GLuint programID, GLuint vertexShader, GLuint fragmentShader);


GLSLProgram::GLSLProgram(){
	program = 0;
	vertexShader = 0 ;
	fragmentShader = 0 ;
}


void GLSLProgram::compileShaders(const std::string vertexShaderfilePath,const std::string fragmentShaderfilePath){
    program = glCreateProgram();
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	compileShader(vertexShader,loadFile(vertexShaderfilePath.c_str()).c_str(),"Vertexshader failed to load : Compilation Error Occured " );
	compileShader(fragmentShader,loadFile(fragmentShaderfilePath.c_str()).c_str(),"FragmentShader failed to load : Compilation Error Occured " );
}

void GLSLProgram::linkShaders(){
	linkProgram(program,vertexShader,fragmentShader);

	glDetachShader(program,vertexShader);
	glDetachShader(program,fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}


void GLSLProgram::addAttribute(std::string attribute){
    glBindAttribLocation(program,(GLuint)attributes.size(),attribute.c_str());
	attributes.push_back(attribute);
}

void GLSLProgram::useProgram(){
	glUseProgram(program);
	/*
	for(int i=0;i<attributes.size() ; i++){
		glEnableVertexAttribArray(i);
	}*/
}

void GLSLProgram::unuseProgram(){
	/*for(int i=0;i<attributes.size() ; i++){
		glDisableVertexAttribArray(i);
	}*/
	glUseProgram(0);
}

GLint GLSLProgram::getUniformLocation(std::string uniformName){
    GLint location = glGetUniformLocation(program,uniformName.c_str());
    if(location == GL_INVALID_INDEX){
		return -1;
    }
    return location;
}


std::string loadFile(const char* filePath){
	std::string file_data ; 
	std::string line;
	std::ifstream file(filePath,std::ios::in);
	if(!file.is_open()){
		std::cout << "File : " << filePath << " unable to open " << std::endl;
		return "";
	}
	while(getline(file,line)){
		file_data += line + "\n";
	}
	file.close();
	return file_data;
}
GLuint compileShader(GLuint shaderID,const char* shader_source,const char* errorMessage){
	GLint result;
	int infoLenght;
	glShaderSource(shaderID,1,&shader_source,NULL);
	glCompileShader(shaderID);
	glGetShaderiv(shaderID,GL_COMPILE_STATUS,&result);
	glGetShaderiv(shaderID,GL_INFO_LOG_LENGTH,&infoLenght);
	if(infoLenght > 0){
		std::vector<char> VertexShaderErrorMessage(infoLenght+1);
		glGetShaderInfoLog(shaderID, infoLenght, NULL, &VertexShaderErrorMessage[0]);
		std::cout << "Error  : " << errorMessage << std::endl;
		printf("		%s\n", &VertexShaderErrorMessage[0]);
		return (GLuint)0;
	}
	return (GLuint)1;
}
GLuint linkProgram(GLuint programID, GLuint vertexShader, GLuint fragmentShader){
	GLint result;
	int infoLenght;

	glAttachShader(programID,vertexShader);
	glAttachShader(programID,fragmentShader);
	glLinkProgram(programID);
	glGetProgramiv(programID,GL_LINK_STATUS,&result);
	glGetProgramiv(programID,GL_INFO_LOG_LENGTH,&infoLenght);
	if(infoLenght > 0){
		std::vector<char> ProgramErrorMessage(infoLenght+1);
		glGetProgramInfoLog(programID, infoLenght, NULL, &ProgramErrorMessage[0]);
		std::cout << "Error : Linking Program " <<std::endl;
		printf("		%s\n", &ProgramErrorMessage[0]);
		return (GLuint)0;
	}
	return (GLuint)1;
}

}