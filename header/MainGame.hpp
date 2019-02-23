#ifndef MAINGAME_H
#define MAINGAME_H

#include "../Engine/header/Window.hpp"
#include "../Engine/header/Camera2D.hpp"
#include "../Engine/header/GLSLProgram.hpp"
#include "../Engine/header/InputManager.hpp"
#include "../Engine/header/SpriteBatch.hpp"

#include "../header/Level.hpp"
#include "../header/Player.hpp"
#include "../header/Zombie.hpp"

#define GLM_ENABLE_EXPERIMENTAL


const float ZOMBIE_SPEED = 3.0;
const float HUMAN_SPEED = 2.5;

enum class GameState{
    PLAY,
    EXIT
};

class MainGame{
    public:
        MainGame();
        ~MainGame();

        void run();

    private:
        void initSystems();
        void initLevel();
        void initShaders();
        void gameLoop();
        void processInput();
        void update();
        void updateAgents();
        void draw();
        void checkVictory();

        unsigned int _height;
        unsigned int _width;


        Engine::Window _window;
        Engine::GLSLProgram _textureProgram;
        Engine::InputManager _inputManager;
        Engine::Camera2D _camera;

        GameState _gameState;

        int _currentLevel;

        Engine::SpriteBatch _agentSpriteBatch;

        std::vector<Level *> _levels;

        std::vector<Human *> _humans;
        std::vector<Zombie *> _zombies;
        std::vector<Bullet> _bullets;
        Player * _player;

        int _numHumansKilled =  0 ; 
        int _numZombiesKilled = 0 ; 

        
        float _fps;

        bool _isGameOver;
        Agent * _agent;
};

#endif