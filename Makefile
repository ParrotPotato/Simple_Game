# variables for game compilation and linking
BIN = bin/
OBJECT_FILE  = $(BIN)main.o
OBJECT_FILE += $(BIN)MainGame.o
OBJECT_FILE += $(BIN)Level.o
OBJECT_FILE += $(BIN)Agent.o
OBJECT_FILE += $(BIN)Zombie.o
OBJECT_FILE += $(BIN)Human.o
OBJECT_FILE += $(BIN)Player.o
OBJECT_FILE += $(BIN)Gun.o
OBJECT_FILE += $(BIN)Bullet.o

FILE_LIST = main
FILE_LIST += MainGame
FILE_LIST += Level
FILE_LIST += Agent
FILE_LIST += Zombie
FILE_LIST += Human
FILE_LIST += Player
FILE_LIST += Gun 
FILE_LIST += Bullet

# variables for Engine compilation and linking 
ENGINE_BIN = Engine/bin/
ENGINE_OBJECT_FILE += $(ENGINE_BIN)Sprite.o
ENGINE_OBJECT_FILE += $(ENGINE_BIN)GLSLProgram.o
ENGINE_OBJECT_FILE += $(ENGINE_BIN)Error.o
ENGINE_OBJECT_FILE += $(ENGINE_BIN)picoPNG.o
ENGINE_OBJECT_FILE += $(ENGINE_BIN)ImageLoader.o
ENGINE_OBJECT_FILE += $(ENGINE_BIN)IOManager.o
ENGINE_OBJECT_FILE += $(ENGINE_BIN)TextureCache.o
ENGINE_OBJECT_FILE += $(ENGINE_BIN)ResourceManager.o
ENGINE_OBJECT_FILE += $(ENGINE_BIN)Window.o
ENGINE_OBJECT_FILE += $(ENGINE_BIN)Engine.o
ENGINE_OBJECT_FILE += $(ENGINE_BIN)Camera2D.o
ENGINE_OBJECT_FILE += $(ENGINE_BIN)SpriteBatch.o
ENGINE_OBJECT_FILE += $(ENGINE_BIN)InputManager.o
ENGINE_OBJECT_FILE += $(ENGINE_BIN)Timing.o


DEBUG_FILE_LIST = src/main.cpp
DEBUG_FILE_LIST += src/MainGame.cpp
DEBUG_FILE_LIST += src/Level.cpp
DEBUG_FILE_LIST += src/Agent.cpp
DEBUG_FILE_LIST += src/Zombie.cpp
DEBUG_FILE_LIST += src/Human.cpp
DEBUG_FILE_LIST += src/Player.cpp
DEBUG_FILE_LIST += src/Gun.cpp

DEBUG_ENGINE_FILE_LIST = 

DEBUG_ENGINE_FILE_SOURCE = Engine/src/
DEBUG_ENGINE_FILE_LIST += $(DEBUG_ENGINE_FILE_SOURCE)Sprite.cpp
DEBUG_ENGINE_FILE_LIST += $(DEBUG_ENGINE_FILE_SOURCE)GLSLProgram.cpp
DEBUG_ENGINE_FILE_LIST += $(DEBUG_ENGINE_FILE_SOURCE)Error.cpp
DEBUG_ENGINE_FILE_LIST += $(DEBUG_ENGINE_FILE_SOURCE)picoPNG.cpp
DEBUG_ENGINE_FILE_LIST += $(DEBUG_ENGINE_FILE_SOURCE)ImageLoader.cpp
DEBUG_ENGINE_FILE_LIST += $(DEBUG_ENGINE_FILE_SOURCE)IOManager.cpp
DEBUG_ENGINE_FILE_LIST += $(DEBUG_ENGINE_FILE_SOURCE)TextureCache.cpp
DEBUG_ENGINE_FILE_LIST += $(DEBUG_ENGINE_FILE_SOURCE)ResourceManager.cpp
DEBUG_ENGINE_FILE_LIST += $(DEBUG_ENGINE_FILE_SOURCE)Window.cpp
DEBUG_ENGINE_FILE_LIST += $(DEBUG_ENGINE_FILE_SOURCE)Engine.cpp
DEBUG_ENGINE_FILE_LIST += $(DEBUG_ENGINE_FILE_SOURCE)Camera2D.cpp
DEBUG_ENGINE_FILE_LIST += $(DEBUG_ENGINE_FILE_SOURCE)SpriteBatch.cpp
DEBUG_ENGINE_FILE_LIST += $(DEBUG_ENGINE_FILE_SOURCE)InputManager.cpp
DEBUG_ENGINE_FILE_LIST += $(DEBUG_ENGINE_FILE_SOURCE)Timing.cpp


LIBS = -lSDL2 -lGL -lGLEW

GAME = output



all: engine game run

game: $(FILE_LIST)
	g++ $(OBJECT_FILE) $(ENGINE_OBJECT_FILE) $(LIBS) -o $(GAME)

game_debug: $(DEBUG_FILE_LIST)
	g++ $(DEBUG_FILE_LIST) $(DEBUG_ENGINE_FILE_LIST) $(LIBS) -std=c++11 -std=gnu++11 -g $(GAME)

engine:
	cd Engine/ && make

engine_clr:
	cd Engine/ && make clear

main: src/main.cpp
	g++ src/main.cpp -c -std=c++11 -std=gnu++11 -o bin/main.o

MainGame: src/MainGame.cpp
	g++ src/MainGame.cpp -c -std=c++11 -std=gnu++11 -o bin/MainGame.o

Level: src/Level.cpp
	g++ src/Level.cpp -c -std=c++11 -std=gnu++11 -o bin/Level.o

Agent: src/Agent.cpp
	g++ src/Agent.cpp -c -std=c++11 -std=gnu++11 -o bin/Agent.o

Human: src/Human.cpp
	g++ src/Human.cpp -c -std=c++11 -std=gnu++11 -o bin/Human.o

Zombie: src/Zombie.cpp
	g++ src/Zombie.cpp -c -std=c++11 -std=gnu++11 -o bin/Zombie.o

Player: src/Player.cpp
	g++ src/Player.cpp -c -std=c++11 -std=gnu++11 -o bin/Player.o

Gun: src/Gun.cpp
	g++ src/Gun.cpp -c -std=c++11 -std=gnu++11 -o bin/Gun.o

Bullet: src/Bullet.cpp
	g++ src/Bullet.cpp -c -std=c++11 -std=gnu++11 -o bin/Bullet.o

clear:
	rm bin/*

run:
	clear
	./output