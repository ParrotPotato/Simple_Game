#ifndef CAMERA2D_H
#define CAMERA2D_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL

namespace Engine{

class Camera2D{
    public:
        Camera2D();
        ~Camera2D();

        void init(int newscreenWidth,int newscreenHeight);
        void update();

        void setPosition(glm::vec2 position){this->position = position;needsMatrixUpdate = true;}
        void setScale(float newScale){scaleValue = newScale; needsMatrixUpdate = true;}
        
        glm::vec2 converScreenToWorld(glm::vec2 screenCoords);

        glm::vec2 getPosition(){return position;}
        float getScale(){return scaleValue;}
        glm::mat4 getCameraMatrix(){return cameraMatrix;}
    private:
        bool needsMatrixUpdate;

        float scaleValue;

        glm::vec2 position;
        glm::mat4 cameraMatrix;
        glm::mat4 orthoMatrix;

        int screenHeight;
        int screenWidth;
};

}
#endif