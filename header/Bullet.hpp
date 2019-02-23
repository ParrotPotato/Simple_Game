#pragma once 

#include <glm/glm.hpp>
#include <vector>

#include "../Engine/header/SpriteBatch.hpp"

#define GLM_ENABLE_EXPERIMENTAL

class Human;
class Zombie;
class Agent;
const int  BULLET_RADIUS = 5;

class Bullet
{
public:
    Bullet(glm::vec2 position,glm::vec2 direction,float damage,float speed);
    ~Bullet();

    bool update(const std::vector<std::string>& levelbuffer);
    void draw(Engine::SpriteBatch &spritebatch);
    bool collidewithAgent(Agent *agent);
    float getDamage(){return _damage;}
private:
    bool collideWithWorld(const std::vector<std::string>& levelbuffer);

    float _damage;
    glm::vec2 _pos;
    glm::vec2 _direction;
    float _speed;


    Engine::Color _color;
};