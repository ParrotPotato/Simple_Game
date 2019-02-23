#include "../header/Human.hpp"

#include <random>
#include <ctime>
#include <glm/gtx/rotate_vector.hpp>

Human::Human(){
    _color.setColor(193, 6, 17,255);
    _direction = glm::vec2(0.0);
    _health = 20;
}

Human::~Human() throw(){
    
}

void Human::update(const std::vector<std::string> & levelData,
                            std::vector<Human *> & humans,
                            std::vector<Zombie *> &zombie){
    static std::mt19937 randomEngine(time(nullptr));
    static std::uniform_real_distribution<float> roatate_rand(-0.01f,0.01f);
    static std::uniform_real_distribution<float> emg(-4.1f,4.1f);
    _position += _direction * _speed;
    if(collideWithLevel(levelData))
    {
        _direction = glm::rotate(_direction,emg(randomEngine));
    }
    _direction = glm::rotate(_direction,roatate_rand(randomEngine));
}

void Human::init(float speed,glm::vec2 position){
    static std::mt19937 randomEngine(time(nullptr));
    static std::uniform_real_distribution<float> randDir(-1.0f,1.0f);
    _speed  = speed;
    _position = position;

    _direction = glm::vec2(randDir(randomEngine),randDir(randomEngine));

    if(_direction == glm::vec2(0.0f,0.0f))_direction = glm::vec2(1.0,1.0);

    _direction = glm::normalize(_direction);
}