#include "../header/Gun.hpp"

#include <glm/gtx/rotate_vector.hpp>

#include <ctime>
#include <random>


//default constructor 
Gun::Gun(){
    _name = "_not_initialised_";
    _firerate = 0.0;
    _bulletsPerShot = 0.0;
    _spread = 0.0;
    _bulletDamage = 0.0;
    _bulletSpeed = 0.0;
}

// parameterized constructor 
Gun::Gun(std::string name,int firerate,int bulletsPerShot,float spread,float bulletDamage,float bulletSpeed)
{
    _name = name;
    _firerate = firerate;
    _bulletsPerShot = bulletsPerShot;
    _spread = spread;
    _bulletDamage = bulletDamage;
    _bulletSpeed = bulletSpeed;
}


// Redundent function but working for the time being 
void Gun::init(std::string name,int firerate,int bulletsPerShot,float spread,float bulletDamage,float bulletSpeed)
{
    _name = name;
    _firerate = firerate;
    _bulletsPerShot = bulletsPerShot;
    _spread = spread;
    _bulletDamage = bulletDamage;
    _bulletSpeed = bulletSpeed;
}

Gun::~Gun()
{

}

void Gun::update(bool isMouseDown,const glm::vec2& position,const glm::vec2& direction,std::vector<Bullet>& bullets)
{
    _frameCounter++;
    if(_frameCounter >= _firerate && isMouseDown)
    {
        fire(position,direction,bullets);
        _frameCounter = 0 ;
    }
}

void Gun::fire(const glm::vec2& position,const glm::vec2& direction,std::vector<Bullet>& bullets)
{
    static std::mt19937 randomEngine(time(nullptr));
    static std::uniform_real_distribution<float> roatate_rand(-_spread/100,_spread/100);

    for(int i=0 ; i < _bulletsPerShot ; i++)
    {
        bullets.emplace_back(position, glm::rotate(direction,roatate_rand(randomEngine)) ,_bulletDamage,_bulletSpeed);
    }
}