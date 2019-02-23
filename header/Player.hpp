#ifndef PLAYER_H
#define PLAYER_H

#include "Human.hpp"
#include "../Engine/header/InputManager.hpp"
#include "../Engine/header/Camera2D.hpp"

#include "../header/Gun.hpp"
#include "../header/Bullet.hpp"

#define GLM_ENABLE_EXPERIMENTAL

class Player : public Human{
    public:
        Player();
        virtual ~Player() throw();
        void init(float speed,glm::vec2 position,Engine::InputManager * inputManager,Engine::Camera2D * camera,std::vector<Bullet> * bullets);

        virtual void update(const std::vector<std::string> & levelData,
                            std::vector<Human *> & humans,
                            std::vector<Zombie *> &zombie
                            ) override;

        void addGun(Gun *gun);
    private:
        Engine::InputManager * _inputManager;
        int _numGun;
        std::vector<Gun*> _guns;
        Engine::Camera2D * _camera;
        std::vector<Bullet> * _bullets;
};

#endif 