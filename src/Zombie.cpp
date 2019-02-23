#include "../header/Zombie.hpp"

#include <random>
#include <glm/gtx/rotate_vector.hpp>

#include "../header/Human.hpp"

Zombie::Zombie(){
    _color.setColor(255,0,255,255);
}

Zombie::~Zombie(){
    
}

void Zombie::update(const std::vector<std::string> & levelData,
                            std::vector<Human *> & humans,
                            std::vector<Zombie *> &zombie){
    Human * closestHuman = getClosestHuman(humans);
    if(closestHuman != nullptr){
        glm::vec2 direction =  glm::normalize(closestHuman->getPosition() - _position);
        
        _position += direction * _speed ;
    }
    collideWithLevel(levelData);
}



void Zombie::init(int speed,glm::vec2 position){    
    _speed = speed;
    _position = position;
    _health = 150;
}

Human * Zombie::getClosestHuman(std::vector<Human *>& human){
    Human * closestHuman = nullptr;
    float smallestDistance = 9999999.0f;

    for(int i=0 ; i < human.size() ; i++){
        glm::vec2 direction = human[i]->getPosition() - _position;
        float distance = glm::length(direction);

        if(distance < smallestDistance){

            smallestDistance = distance;
            closestHuman = human[i];
        }
    }
    return closestHuman;
}
