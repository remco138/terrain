#include <GL/glew.h>

#include "Engine.h"

#pragma comment(lib, "glew32.lib")
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")


int main()
{
	//initialization stage
	Engine engine;
	engine.init();

	//main loop
	engine.start();

    return 0;
}