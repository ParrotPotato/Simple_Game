#include "../header/Camera2D.hpp"

namespace Engine{

Camera2D::Camera2D():position(glm::vec2(0.0,0.0)),
cameraMatrix(1.0f),
scaleValue(1.0f),
needsMatrixUpdate(true),
screenHeight(800),
screenWidth(800),
orthoMatrix(1.0f){

}

Camera2D::~Camera2D(){
    
}

void Camera2D::init(int newscreenWidth,int newscreenHeight){
    screenHeight = newscreenHeight;
    screenWidth = newscreenWidth;
    orthoMatrix = glm::ortho(0.0f,(float)screenWidth,0.0f,(float)screenHeight);
    needsMatrixUpdate = true;
}

glm::vec2 Camera2D::converScreenToWorld(glm::vec2 screenCoords){
    screenCoords.y = screenHeight - screenCoords.y ; 
    screenCoords -= glm::vec2(screenWidth/2 , screenHeight/2);
    screenCoords /= scaleValue;
    screenCoords += position;

    return screenCoords;
}

void Camera2D::update(){
    if(needsMatrixUpdate){
        //camera translation 
        glm::vec3 translate(-position.x + screenWidth/(float)2 , -position.y + screenHeight/(float)2 , 0.0f);
        cameraMatrix = glm::translate(orthoMatrix,translate);

        //cameraScale
        glm::vec3 scale(scaleValue,scaleValue,0.0);
        cameraMatrix = glm::scale(glm::mat4(1.0f),scale) * cameraMatrix;
        needsMatrixUpdate = false;
    }
}

}