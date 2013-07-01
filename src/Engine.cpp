#include "Engine.h"
#include "Heightmap.h"
#include <iostream>

#include <GL/glew.h>
#include <SFML/OpenGL.hpp>

int lastx = 0, lasty = 0;

void Engine::onResize()
{
	vec2u windowSize = window.getSize();

	glViewport (0, 0, windowSize.x, windowSize.y);  
	glMatrixMode (GL_PROJECTION);   
	glLoadIdentity ();
	gluPerspective (65, windowSize.x / windowSize.y, 1.0, 9999);  
	glMatrixMode (GL_MODELVIEW);
}

void Engine::init()//enable depth test
{
	window.create(sf::VideoMode(800, 600), "SFML works!");
	glewInit();
	onResize();
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	heightMap.create("heightMap.bmp");
	input.init(&window);
//	input.hookMouse(&(camera.update), hookType.difference);

	sf::ContextSettings settings = window.getSettings();
	std::cout << "OpenGL version:"<< settings.majorVersion << "." << settings.minorVersion << std::endl;
}

int tickRate = 33;

void Engine::start()
{	
	sf::Clock clock;
	while(true)
	{
		if(clock.getElapsedTime().asMilliseconds() >= 1000 / tickRate)
		{
			update();
			clock.restart();
		}
		render();
	}
}

void Engine::update()
{
	input.update();
	camera.update();

}

void Engine::render()
{
	glClearColor (0.0,0.0,0.0,1.0);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity(); 
	//glColor3f(1, 0, 0);
	
	camera.correctHeight(heightMap);
	camera.render();
	heightMap.render(camera.getLocation()); //requires our location for LOD

	window.display();
}

//_______WRAPPERS
/*
*/
