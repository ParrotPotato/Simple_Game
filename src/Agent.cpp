#include "../header/Agent.hpp"

#include "../Engine/header/ResourceManager.hpp"

#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <stddef.h>

glm::vec2 global_position;

Agent::Agent(){

}

Agent::~Agent(){

}


bool compare(glm::vec2 t1,glm::vec2 t2);
void Agent::draw(Engine::SpriteBatch& spriteBatch)
{    
    static int textureId = Engine::ResourceManager::getTexture("res/texture/circle.png").id;

    glm::vec4 destRect = glm::vec4(_position.x,_position.y,AGENT_SIZE,AGENT_SIZE);
    glm::vec4 uvRect = glm::vec4(0.0f,0.0f,1.0f,1.0f);

    spriteBatch.draw(destRect,uvRect,textureId,-1.0,_color);
}

bool Agent::collideWithLevel(const std::vector<std::string> & levelData ){
    global_position = _position;
    std::vector <glm::vec2>collideTilePosition;
    checkTilePosition(collideTilePosition,_position.x + AGENT_SIZE,_position.y,levelData);
    checkTilePosition(collideTilePosition,_position.x,_position.y+ AGENT_SIZE,levelData);
    checkTilePosition(collideTilePosition,_position.x+ AGENT_SIZE,_position.y+ AGENT_SIZE,levelData);
    checkTilePosition(collideTilePosition,_position.x,_position.y,levelData);
    std::stable_sort(collideTilePosition.begin(),collideTilePosition.end(),compare);
    
    if(collideTilePosition.size() == 0){
        return false;
    }

    for(int i=0 ; i  < collideTilePosition.size() ; i++){
        collideWithTile(collideTilePosition[i]);
    }

    return true;
}

void Agent::checkTilePosition(std::vector<glm::vec2>& collideTilePosition,float x,float y,const std::vector<std::string> & levelData ){
    glm::vec2 levelMapping = glm::vec2(floor(x/(float)TILE_WIDTH) , floor(y/(float)TILE_WIDTH));
    if(levelData[levelMapping.y][levelMapping.x] != '.'){
        collideTilePosition.push_back(levelMapping * (float)TILE_WIDTH  + glm::vec2((float)TILE_WIDTH/2.0));
    }
}


//AABB Collision 
void Agent::collideWithTile(glm::vec2 tilePos)
{
    const float MIN_DIST = (float)TILE_WIDTH/2.0f + (float)AGENT_SIZE/2.0f ; 

    glm::vec2 center = _position + glm::vec2((float)AGENT_SIZE/2.0f);

    float xdist = (center - tilePos).x;
    float ydist = (center - tilePos).y;

    if(MIN_DIST - std::abs(xdist) < MIN_DIST  - std::abs(ydist)){
        float x_correction = MIN_DIST - std::abs(xdist);
        if(center.x > tilePos.x ){
            _position.x += x_correction;
        }
        else{
            _position.x -= x_correction;
        }
    }else if(MIN_DIST - std::abs(xdist) > MIN_DIST  - std::abs(ydist)){
        float y_correction = MIN_DIST  - std::abs(ydist);
        if(center.y > tilePos.y){
            _position.y += y_correction;
        }
        else{
            _position.y -= y_correction;
        }
    }
}

bool Agent::collideWithAgent(Agent *agent){
    const float MIN_DIST =  AGENT_SIZE;

    glm::vec2 center = _position + glm::vec2((float)AGENT_SIZE/2.0f);
    
    glm::vec2 agentCenter = agent->getPosition() + glm::vec2((float)AGENT_SIZE/2.0f);

    glm::vec2 distVec = center - agentCenter;

    float distance = glm::length(distVec);
    float collisionDepth = MIN_DIST - distance;
    if(collisionDepth > 0 ){
        glm::vec2 collisionDepthVec = glm::normalize(distVec) * collisionDepth;
        _position += collisionDepthVec / 2.0f;
        agent->_position -= collisionDepthVec / 2.0f;
        return true;
    }
    return false ;
}

bool compare(glm::vec2 t1,glm::vec2 t2){
    glm::vec2 center = global_position +  glm::vec2((float)AGENT_SIZE / 2.0f);
    if(glm::distance(center,t1) > glm::distance(center,t2)){
        return true;
    }
    return false;
}
