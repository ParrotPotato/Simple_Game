#include "../header/Bullet.hpp"

#include "../Engine/header/ResourceManager.hpp"

#include "../header/Agent.hpp"
#include "../header/Human.hpp"
#include "../header/Zombie.hpp"
#include "../header/Level.hpp"

Bullet::Bullet(glm::vec2 position,glm::vec2 direction,float damage,float speed)
{
    _pos = position;
    _direction = direction;
    _damage = damage;
    _speed = speed;

    _color.setColor(0,0,0,255);
}


Bullet::~Bullet()
{

}

bool Bullet::update(const std::vector<std::string>& levelbuffer)
{
    _pos += _direction * _speed ;
    return collideWithWorld(levelbuffer);
}

void Bullet::draw(Engine::SpriteBatch &spritebatch)
{
    glm::vec4 destRect = glm::vec4(_pos.x + BULLET_RADIUS, _pos.y + BULLET_RADIUS , BULLET_RADIUS *2 ,BULLET_RADIUS *2);
    const glm::vec4 uvRect = glm::vec4(0.0f,0.0f,1.0f,1.0f);
    spritebatch.draw(destRect, uvRect, Engine::ResourceManager::getTexture("res/texture/circle.png").id, 0.0f, _color);
}

bool Bullet::collidewithAgent(Agent *agent)
{
    const float MIN_DIST =  AGENT_SIZE / 2 + BULLET_RADIUS ;

    glm::vec2 center = _pos;
    
    glm::vec2 agentCenter = agent->getPosition() + glm::vec2((float)BULLET_RADIUS);

    glm::vec2 distVec = center - agentCenter;

    float distance = glm::length(distVec);
    float collisionDepth = MIN_DIST - distance;
    if(collisionDepth > 0 ){
        return true;
    }
    return false ;
}

bool Bullet::collideWithWorld(const std::vector<std::string>& levelbuffer){
    glm::ivec2 gridPosition;
    gridPosition.x = floor(_pos.x / TILE_WIDTH);
    gridPosition.y = floor(_pos.y / TILE_WIDTH);

    if(gridPosition.x < 0 || gridPosition.x >= levelbuffer[1].size() || 
       gridPosition.y < 0 || gridPosition.y >= levelbuffer.size()){
        return true;
    }
    
    return (levelbuffer[gridPosition.y][gridPosition.x] != '.');
}   