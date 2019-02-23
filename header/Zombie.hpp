#ifndef ZMOBIE_H
#define ZMOBIE_H

#include "Agent.hpp"


#define GLM_ENABLE_EXPERIMENTAL
class Zombie : public Agent{
    public:
        Zombie();
        virtual ~Zombie();

        virtual void update(const std::vector<std::string> & levelData,
                            std::vector<Human *> & humans,
                            std::vector<Zombie *> &zombie);
        void init(int speed,glm::vec2 position);
    private:
        Human * getClosestHuman(std::vector<Human *>& human);
        glm::vec2 _direction;
};


#endif 