#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>

#include "../Engine/header/SpriteBatch.hpp"

#include <iostream>

#define GLM_ENABLE_EXPERIMENTAL

const float TILE_WIDTH = 64.0;


class Level{
    public:
        Level(const std::string filename);
        ~Level();

        void load(std::string filename);
        void draw();

        glm::vec2 getPlayerPosition() const {return _startPlayerPos;}
        const std::vector<glm::vec2>& getZombiePositions() const {return _zombieStartPosition;}
        const std::vector<std::string>& getLevelBuffer(){return _levelBuffer;}
        const int getNumHumans(){return _numHumans;}

        int getWidth(){return _levelWidth;}
        int getHeight(){return _levelHeight;}
        void loadMessage(){
            std::cout << "Level -> Humans : " << _numHumans << " Height : " << _levelHeight << " width : " << _levelWidth << std::endl;
        }
        char getTile(int x,int y){return _levelBuffer[y][x];}
    private:
        std::vector<std::string> _levelBuffer;
        
        int _levelWidth;
        int _levelHeight;

        int _numHumans;

        Engine::SpriteBatch _spriteBatch;

        glm::vec2 _startPlayerPos;
        std::vector<glm::vec2> _zombieStartPosition;
};

#endif 