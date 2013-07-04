#include <GL/glew.h>

#include "Engine.h"

int main()
{
	//initialization stage
	Engine engine;
	engine.init();

	//main loop
	engine.start();

    return 0;
}