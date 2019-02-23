#include "../header/Level.hpp"

#include "../Engine/header/Error.hpp"
#include "../Engine/header/GLTexture.hpp"
#include "../Engine/header/ResourceManager.hpp"

#include <fstream>
#include <iostream>

#include <glm/glm.hpp>

Level::Level(const std::string filename){
    std::ifstream file;
    file.open(filename.c_str(),std::ios::in);
    
    std::string line;

    if(file.is_open()){
        file >> line >> _numHumans;
        file.ignore();
        while(file.good()){
            std::getline(file,line);
            _levelBuffer.push_back(line);
        }
    }else{
        Engine::fatalError("Unable to open :" + filename);
    }
    _levelWidth = _levelBuffer[5].size();
    _levelHeight = _levelBuffer.size();

    file.close();
    _spriteBatch.init();

    _spriteBatch.begin((int)Engine::GlyphSortType::TEXTURE | (int) Engine::GlyphSortType::BACK_TO_FRONT);

    glm::vec4 uvRect(0.0f,0.0f,1.0f,1.0f);
    Engine::Color white_color;
    white_color.setColor(255,255,255,255);

    for(int y = 0 ; y < _levelBuffer.size() ; y++){
        for(int x = 0 ; x < _levelBuffer[y].size() ; x++){
            char tile = _levelBuffer[y][x];

            glm::vec4 destRect(x * TILE_WIDTH ,y * TILE_WIDTH, TILE_WIDTH,TILE_WIDTH);
            switch(tile){

                case 'B':
                case 'R':
                    _spriteBatch.draw(destRect,
                                        uvRect,
                                        Engine::ResourceManager::getTexture("res/texture/red_brick.png").id,
                                        0.0,
                                        white_color);
                    break;
                case 'G':
                    _spriteBatch.draw(destRect,
                                        uvRect,
                                        Engine::ResourceManager::getTexture("res/texture/glass.png").id,
                                        0.0,
                                        white_color);
                    break;
                case 'L':
                    _spriteBatch.draw(destRect,
                                        uvRect,
                                        Engine::ResourceManager::getTexture("res/texture/light_brick.png").id,
                                        0.0,
                                        white_color);
                    break;
                case '@':
                    _startPlayerPos.x = x*TILE_WIDTH;
                    _startPlayerPos.y = y*TILE_WIDTH;
                    _levelBuffer[y][x] = '.';
                    break;
                case 'Z':
                    _zombieStartPosition.emplace_back(x*TILE_WIDTH,y*TILE_WIDTH);
                    _levelBuffer[y][x] = '.';
                    break;
                case '.':
                    break;
                default:
                    std::cout << "Unexpected symbole  " << tile << "at " << x << ',' << y << std::endl; 
            }
        }
    }

    _spriteBatch.end();
}

Level::~Level(){

}


 
void Level::load(std::string filename){

}

void Level::draw(){
    _spriteBatch.renderBatch();
}
