#include "../header/Player.hpp"
#include "../header/Bullet.hpp"

#include <SDL2/SDL.h>
#include <glm/glm.hpp>

Player::Player(){
    _color.setColor(34, 16, 203,255);
    _numGun = -1 ;
}

Player::~Player() throw(){
    
}


void Player::addGun(Gun *gun)
{
    _numGun++;
    _guns.push_back(gun);
}

void Player::init(float speed,glm::vec2 position,Engine::InputManager * inputManager,Engine::Camera2D * camera,std::vector<Bullet> * bullets)
{
    _speed = speed;
    _position = position;
    _inputManager = inputManager;
    _direction.x = 0 ; 
    _direction.y = 0 ;

    _camera = camera;
    _bullets = bullets;
    

    _health = 150;
}
void Player::update(const std::vector<std::string> & levelData,
                            std::vector<Human *> & humans,
                            std::vector<Zombie *> &zombie
                            )
{
    glm::vec2 temp(0.0f,0.0f);
    if(_inputManager->isKeyPressed(SDLK_d))
        temp.x += 1.0;
    if(_inputManager->isKeyPressed(SDLK_a))
        temp.x -= 1.0;
    if(_inputManager->isKeyPressed(SDLK_w))
        temp.y += 1.0;
    if(_inputManager->isKeyPressed(SDLK_s))
        temp.y -= 1.0;
    if(_inputManager->isKeyPressed(SDLK_1) &&  _numGun != -1 )
        _numGun = 0;
    if(_inputManager->isKeyPressed(SDLK_2) &&  _numGun != -1)
        _numGun = 1;
    if(_inputManager->isKeyPressed(SDLK_3) &&  _numGun != -1)
        _numGun = 2;

    if(temp == glm::vec2(0.0)){
        _direction = temp;
    }
    else{
        _direction = glm::normalize(temp);
    }
    _position += _direction * _speed;

    glm::vec2 mousecoordinates = _camera->converScreenToWorld(_inputManager->getMouseCoords());
    glm::vec2 centerPosition =  _position + glm::vec2(AGENT_SIZE/2.0);

    glm::vec2 direction = glm::normalize(mousecoordinates - centerPosition);
    if(glm::length(centerPosition - mousecoordinates) == 0)
    {
        direction = glm::vec2(0.0);
    }

    _guns[_numGun]->update(_inputManager->isKeyPressed(SDL_BUTTON_LEFT), centerPosition, direction, *_bullets);

    collideWithLevel(levelData);

    _direction.x = 0 ; 
    _direction.y = 0 ;
}

