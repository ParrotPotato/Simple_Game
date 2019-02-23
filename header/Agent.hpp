#ifndef AGENT_H
#define AGENT_H

#include <glm/glm.hpp>
#include "../Engine/header/SpriteBatch.hpp"
#include <vector>

#include "Level.hpp"
#define GLM_ENABLE_EXPERIMENTAL


const float AGENT_SIZE = 60.0;

class Zombie;
class Human;


class Agent{
    public:
        Agent();
        virtual ~Agent();
        virtual void update(const std::vector<std::string> & levelData,
                            std::vector<Human *> & humans,
                            std::vector<Zombie *> &zombie) = 0 ;
        void draw(Engine::SpriteBatch& spriteBatch);
        bool collideWithAgent( Agent *agent);
        glm::vec2 getPosition()const {return _position;}
        bool applyDamage(float damage){
            _health -= damage;
            if(_health < 0)
                return true;
            return false;
        }
    protected:
        bool collideWithLevel(const std::vector<std::string> & levelData );
        void checkTilePosition(std::vector<glm::vec2>& collideTilePosition,float x,float y,const std::vector<std::string> & levelData );
        void collideWithTile(glm::vec2 tilePos);
        
        float _health;

        glm::vec2 _position;
        float _speed;

        Engine::Color _color;
};


#endif 