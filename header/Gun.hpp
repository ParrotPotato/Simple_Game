#pragma once 

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

#include "Bullet.hpp"

#define GLM_ENABLE_EXPERIMENTAL

class Gun{
    public:
        Gun(std::string name,int firerate,int bulletsPerShot,float spread,float bulletDamage,float bulletSpeed);
        Gun();
        ~Gun();

        void init(std::string name,int firerate,int bulletsPerShot,float spread,float bulletDamage,float bulletSpeed);
        void update(bool isMouseDown,const glm::vec2& position,const glm::vec2& direction,std::vector<Bullet>& bullets);
    private:
        void fire(const glm::vec2& position,const glm::vec2& direction,std::vector<Bullet>& bullets);

        std::string _name;

        int _firerate;
        int _bulletsPerShot;

        float _spread;

        float _bulletSpeed;
        float _bulletDamage;

        int _frameCounter = 0 ;
};