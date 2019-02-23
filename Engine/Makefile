all: Sprite Error GLSLProgram picoPNG ImageLoader IOManager ResourceManager TextureCache Window Engine Camera2D SpriteBatch InputManager Timing

Sprite: src/Sprite.cpp
	g++ src/Sprite.cpp -c -std=c++11 -std=gnu++11 -o  bin/Sprite.o

GLSLProgram:  src/GLSLProgram.cpp
	g++ src/GLSLProgram.cpp -c -std=c++11 -std=gnu++11 -o  bin/GLSLProgram.o

Error:  src/Error.cpp
	g++ src/Error.cpp -c -std=c++11 -std=gnu++11 -o  bin/Error.o

picoPNG:  src/picoPNG.cpp
	g++ src/picoPNG.cpp -c -std=c++11 -std=gnu++11 -o  bin/picoPNG.o

ImageLoader:  src/ImageLoader.cpp
	g++ src/ImageLoader.cpp -c -std=c++11 -std=gnu++11 -o  bin/ImageLoader.o

IOManager:  src/IOManager.cpp
	g++ src/IOManager.cpp -c -std=c++11 -std=gnu++11 -o  bin/IOManager.o

TextureCache:  src/TextureCache.cpp
	g++ src/TextureCache.cpp -c -std=c++11 -std=gnu++11 -o  bin/TextureCache.o

ResourceManager:  src/ResourceManager.cpp
	g++ src/ResourceManager.cpp -c -std=c++11 -std=gnu++11 -o  bin/ResourceManager.o

Window: src/Window.cpp
	g++ src/Window.cpp -c -std=c++11 -std=gnu++11 -o  bin/Window.o 

Engine: src/Engine.cpp
	g++ src/Engine.cpp -c -std=c++11 -std=gnu++11 -o  bin/Engine.o 

Camera2D: src/Camera2D.cpp
	g++ src/Camera2D.cpp -c -std=c++11 -std=gnu++11 -o  bin/Camera2D.o 

SpriteBatch: src/SpriteBatch.cpp
	g++ src/SpriteBatch.cpp -c -std=c++11 -std=gnu++11 -o bin/SpriteBatch.o

InputManager: src/InputManager.cpp 
	g++ src/InputManager.cpp -c -std=c++11 -std=gnu++11 -o bin/InputManager.o

Timing: src/Timing.cpp
	g++ src/Timing.cpp -c -std=c++11 -std=gnu++11 -o bin/Timing.o

clear:
	rm bin/*