#include "../header/MainGame.hpp"

#include <iostream>

int main(int args,char **argv){
    MainGame * game = new MainGame();
    game->run();
    return 0;
}