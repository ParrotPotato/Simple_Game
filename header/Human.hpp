#ifndef HUMAN_H
#define HUMAN_H

#include "Agent.hpp"

#define GLM_ENABLE_EXPERIMENTAL

class Human : public Agent{
    public:
        Human();
        virtual ~Human () throw();
        void init(float speed,glm::vec2 position);
        virtual void update(const std::vector<std::string> & levelData,
                            std::vector<Human *> & humans,
                            std::vector<Zombie *> &zombie);
    protected:
        glm::vec2 _direction;
};

#endif