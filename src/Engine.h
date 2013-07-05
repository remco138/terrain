#ifndef ENGINE_H
#define ENGINE_H

#include "GL/glew.h"
#include <SFML/Window.hpp>

#include "Input.h"
#include "Heightmap.h"
#include "HeightmapStreamer.h"
#include "camera.h"

class Engine
{
public:
	sf::Window window;

	Input input;
	HeightMap heightMap;
	HeightmapStreamer infiniteTerrain;
	Camera camera;
	Quadtree* tree;
	/*
	* maybe put this/these functions in a window class 
	*/
	Engine() {}
	~Engine();
	
	void onResize();

	void handleMouse(int movedX, int movedY);
	void init();
	void start();
	void update();
	void render();
};

#endif