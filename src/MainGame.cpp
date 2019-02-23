#include "../header/MainGame.hpp"
#include "../Engine/header/Engine.hpp"
#include "../Engine/header/Timing.hpp"
#include "../Engine/header/Error.hpp"
#include "../Engine/header/ResourceManager.hpp"


#include "../header/Bullet.hpp"


#include <iostream>
#include <random>
#include <ctime>

MainGame::MainGame(){
    //giving something which is comparable to my resolution 
    _width = 1024;
    _height = 768;
    _fps = 0 ;
    _isGameOver = false;
}
MainGame::~MainGame(){
    for(int i = 0 ; i < _levels.size() ; i++){
        delete _levels[i];
    }
    _levels.clear();

    for(int i=0 ; i < _humans.size() ; i++){
        delete _humans[i];
    }

    for(int i=0 ; i < _zombies.size() ; i++){
        delete _zombies[i];
    }
}

void MainGame::run(){
   initSystems();

   gameLoop();

}
void MainGame::initSystems(){
    Engine::init();
    //my screen resolution 
    _width = 1920;
    _height = 1080;
    _window.create("Zombie Game ",_width,_height,Engine::FULLSCREEN);
    _window.clearColor(0.047, 0.298, 0.627,1.0);
    initShaders();

    _camera.init(_width,_height);
    _agentSpriteBatch.init();
    _gameState = GameState::PLAY;

    initLevel();
}

void MainGame::initLevel(){
    Level * plevel = new Level("res/level/level1");
    _levels.push_back(plevel);
    _currentLevel = 0 ;

    // adding player 

    _player = new Player();
    _player->init(10.0,_levels[_currentLevel]->getPlayerPosition(),&_inputManager,&_camera,&_bullets);

    const int BULLET_SPEED = 20.0f;
    _player->addGun(new Gun("Magnum",10,1,5.0f,30,BULLET_SPEED));
    _player->addGun(new Gun("Shotgun",30,12,20,4,BULLET_SPEED));
    _player->addGun(new Gun("MP5",2,1,10,20,BULLET_SPEED));

    _agent = _player;
    _humans.push_back(_player);
    _levels[_currentLevel]->loadMessage();
    
    
    
    srand((unsigned)time(nullptr));

    const float HUMAN_SPEED = 2.5;
    //adding random humans 
    glm::vec2 position(0.0);
    for(int i=0 ; i < _levels[_currentLevel]->getNumHumans() ; i++){
        int x = (rand() % (_levels[_currentLevel]->getWidth()-2)) + 2 ;
        int y = (rand() % (_levels[_currentLevel]->getHeight()-2)) + 2;
        if(_levels[_currentLevel]->getTile(x,y) == '.'){
            _humans.push_back(new Human());
            position = glm::vec2((float)x * TILE_WIDTH ,(float)y* TILE_WIDTH);
            _humans.back()->init(HUMAN_SPEED,position);
        }else{
            i--;
        }
    }
    // inisialise zombies 
    const float ZOMBIE_SPEED = 3.0;
    const std::vector<glm::vec2>& zombie_buffer = _levels[_currentLevel]->getZombiePositions();
    for(int i=0 ; i < zombie_buffer.size() ; i++){
        _zombies.push_back(new Zombie());
        _zombies.back()->init(ZOMBIE_SPEED,zombie_buffer[i]);
    }

    _camera.setPosition(_player->getPosition());
}

void MainGame::initShaders(){
    _textureProgram.compileShaders("res/shader/vertexShader.glsl","res/shader/fragmentShader.glsl");
    _textureProgram.addAttribute("vertexPosition");
    _textureProgram.addAttribute("vertexColor");
    _textureProgram.addAttribute("vertexUV");
    _textureProgram.linkShaders();
}

void MainGame::gameLoop(){
    Engine::FpsLimiter fpsLimiter;
    fpsLimiter.setMaxFps(60);

    while(_gameState == GameState::PLAY){
        system("clear");

        std::cout << "FPS    : " << _fps << std::endl;
        if(_humans.size() == 0){
                    _gameState == GameState::EXIT;
                    std::cout << "You lost Everything dear !!" << std::endl;
                    Engine::fatalError("Good Bye!");
                    continue;
        }
        fpsLimiter.begin();
        processInput();

        update();

        checkVictory();

        draw();

        

        _fps = fpsLimiter.end();
        //std::cout << "FPS : " << _fps << std::endl;
    }
}

void MainGame::processInput(){
    SDL_Event event;

    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT:
                _gameState = GameState::EXIT;
                break;
            case SDL_MOUSEMOTION:
                _inputManager.setMouseCoords(event.motion.x, event.motion.y);
                break;
            case SDL_KEYDOWN:
                _inputManager.pressKey(event.key.keysym.sym);
                break;
            case SDL_KEYUP:
                _inputManager.releaseKey(event.key.keysym.sym);
                break;
            case SDL_MOUSEBUTTONDOWN:
                _inputManager.pressKey(event.button.button);
                break;
            case SDL_MOUSEBUTTONUP:
                _inputManager.releaseKey(event.button.button);
                break;
        }
    }
}

void MainGame::update(){
    float CAMERA_SPEED = 10.0f;
    float SCALE_FACTOR = 0.1f;
    if(_inputManager.isKeyPressed(SDLK_ESCAPE)){
        _gameState = GameState::EXIT;
    }
    
    if(_inputManager.isKeyPressed(SDLK_q))
        _camera.setScale(_camera.getScale() + SCALE_FACTOR);
    if(_inputManager.isKeyPressed(SDLK_e))
        _camera.setScale(_camera.getScale() - SCALE_FACTOR);
    /**/
    
    updateAgents();
    _camera.setPosition(_agent->getPosition());
    _camera.update();
}

void MainGame::updateAgents(){

    for(int i=0 ;i < _humans.size() ; i++){
        _humans[i]->update(_levels[_currentLevel]->getLevelBuffer(),_humans,_zombies);
    }

    for(int i=0 ; i < _zombies.size() ; i++){
        _zombies[i]->update(_levels[_currentLevel]->getLevelBuffer(),_humans,_zombies);
    }

    //collision with zombie
    for(int i=0 ; i < _zombies.size() ; i++){
        // with zombie 
        for(int j=i+1 ; j < _zombies.size() ; j++){
            _zombies[i]->collideWithAgent(_zombies[j]);
        }
        //with human 
        for(int j=1 ; j < _humans.size() ; ){
                if(_humans.size() == 0){
                    _gameState == GameState::EXIT;
                    std::cout << "You lost Everything dear !!" << std::endl;
                    Engine::fatalError("Good Bye!");
                }else if(_humans.size()  ==  1){
                    break;
                }else if(_zombies[i]->collideWithAgent(_humans[j])){
                    _zombies.push_back(new Zombie());
                    _zombies.back()->init(ZOMBIE_SPEED,_humans[j]->getPosition());
                    delete _humans[j];
                    _humans[j] = _humans.back();
                    _humans.pop_back();
                }else{
                    j++;
                }
        }
            if(_humans.size()!=0){
                if(_zombies[i]->collideWithAgent(_humans[0])){
                    _zombies.back()->init(ZOMBIE_SPEED,_humans[0]->getPosition());
                    if(!_isGameOver){
                        _agent = _zombies.back();
                        _isGameOver = true;
                    }
                    delete _humans[0];
                    _humans[0] = _humans.back();
                    _humans.pop_back();
                    _isGameOver = true;
                }
            }
    }
    
    for(int i=0 ; i < _humans.size() ; i++){
        for(int j=i+1 ; j < _humans.size() ; j++){
            _humans[i]->collideWithAgent(_humans[j]);
        }
    }


    /////UPDATING BULLEST /////
    for(int i=0 ; i < _bullets.size() ; )
    {
        if(_bullets[i].update(_levels[_currentLevel]->getLevelBuffer())){
            _bullets[i] = _bullets.back();
            _bullets.pop_back();
        }
        else{
            i++;
        }
    }

    for(int i=0 ; i < _bullets.size() ; i++){
        for(int j =0 ; j < _zombies.size() ; j++){
            if(_bullets[i].collidewithAgent(_zombies[j])){
                
                if(_zombies[j]->applyDamage(_bullets[i].getDamage())){
                    delete _zombies[j];
                    _zombies[j] = _zombies.back();
                    _zombies.pop_back();
                    j--;
                    _numZombiesKilled++;
                }
                
                _bullets[i] = _bullets.back();
                _bullets.pop_back();
                i--;
                break;
            }
        }
    }

    for(int i=0 ; i < _bullets.size() ; i++){
        for(int j =1 ; j < _humans.size() ; j++){
            if(_bullets[i].collidewithAgent(_humans[j])){
                
                if(_humans[j]->applyDamage(_bullets[i].getDamage())){
                    delete _humans[j];
                    _humans[j] = _humans.back();
                    _humans.pop_back();
                    j--;
                    _numHumansKilled++;
                }
                
                _bullets[i] = _bullets.back();
                _bullets.pop_back();
                i--;
                break;
            }
        }
    }
}

void MainGame::draw(){
    
    _window.clear();
    _textureProgram.useProgram();

    glActiveTexture(GL_TEXTURE0);
    GLint texture_uniform = _textureProgram.getUniformLocation("mySampler");
    glUniform1i(texture_uniform,0);

    glm::mat4 cameraMatrix = _camera.getCameraMatrix();
    GLint pLocation = _textureProgram.getUniformLocation("P");
    glUniformMatrix4fv(pLocation,1,GL_FALSE,&cameraMatrix[0][0]);
    GLuint textureID = Engine::ResourceManager::getTexture("res/texture/glass.png").id;
    _agentSpriteBatch.begin((int)Engine::GlyphSortType::TEXTURE | (int) Engine::GlyphSortType::BACK_TO_FRONT);


    for(int i=0 ; i < _humans.size() ; i++){
        _humans[i]->draw(_agentSpriteBatch);
    }

    for(int i=0; i < _zombies.size() ; i++){
        _zombies[i]->draw(_agentSpriteBatch);
    }
    
    for(int i=0 ; i < _bullets.size() ; i++)
    {
        _bullets[i].draw(_agentSpriteBatch);
    }
    
    Engine::Color color;
    color.setColor(255,255,255,255);
    _agentSpriteBatch.draw(glm::vec4(0.0,0.0,50.0,50.0),glm::vec4(0.0,0.0,1.0,1.0),textureID , 0.0,color);
    
    

    _agentSpriteBatch.end();

    _levels[_currentLevel]->draw();
    _agentSpriteBatch.renderBatch();

    _textureProgram.unuseProgram();
    _window.swapBuffer();
}

void MainGame::checkVictory(){
    if(_zombies.empty()){
        std::cout << "********* YOU WIN ***********" << std::endl;
        std::cout << " Humans killed : " << _numHumansKilled << std::endl;
        std::cout << " Zombies Killed : " << _numZombiesKilled << std::endl;
        std::cout << _humans.size() - 1  << " remaining  out of " << _levels[_currentLevel]->getNumHumans() << std::endl;

        Engine::fatalError("YOU WIN");
    }
}