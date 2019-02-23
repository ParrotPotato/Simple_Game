#include "../header/InputManager.hpp"

namespace Engine{

InputManager::InputManager():mouseCoords(glm::vec2(0.0f,0.0f)){

}

InputManager::~InputManager(){

}

void InputManager::pressKey(unsigned int keyID){
    keyMap[keyID] = true;
}

void InputManager::releaseKey(unsigned int keyID){
    keyMap[keyID] = false;
}

void InputManager::setMouseCoords(float x,float y){
    mouseCoords.x = x;
    mouseCoords.y = y;
}

bool InputManager::isKeyPressed(unsigned int keyID){
    auto it = keyMap.find(keyID);
    if( it != keyMap.end())
        return it->second;
    return false;
}

}