#include "HeightMap.h"
#include <math.h>
#include <SFML/Graphics/Image.hpp>
#include "ShaderProgram.h"

bool HeightMap::init()
{
	return true;
}

VBO HeightMap::create(const char* file){
	sf::Image heightMap;
	int test = heightMap.loadFromFile("heightMap.bmp");
	if(test == false)
	{
		printf("%s", "error");
	}
	int b = heightMap.getSize().x;
	size.x = heightMap.getSize().x;
	size.y = heightMap.getSize().y;

	vertexCount = size.x * size.y;
	vertexData = new GLfloat[vertexCount * 3];

	for(unsigned int x = 0; x < size.x; x++)
	{
		for(unsigned int z = 0; z < size.y; z++)
		{
			sf::Color c = heightMap.getPixel(x, z); 

			vertexData[x*size.x*3+z*3]   = static_cast<float>(x);
			vertexData[x*size.x*3+z*3+1] = static_cast<float>((c.r + c.g + c.b)/3);
			vertexData[x*size.x*3+z*3+2] = static_cast<float>(z);
		}
	}

	init(); //empty for now

	vbo.create(vertexData, vertexCount);

	ShaderProgram shader("shader");

	vec3f loc(0, 0, 0);
	vec3f size(size.x, 200, size.y);
	tree = new QuadTree(vbo,loc, size, 0, shader); 
	return vbo;
}

void HeightMap::render(vec3f location)
{
	tree->render(location);
}

vec3f HeightMap::getNearestVertex(const vec3f location) const
{
	if((location.x < 0 || location.x >= size.x) ||
		location.y < 0							||
		location.z < 0 || location.z >= size.y)
	{
		return location;
	}
	int x = std::floor(location.x);
	int z = std::floor(location.z);
	return vec3f(location.x, vertexData[x*size.x*3+z*3 + 1] + 15, location.z);

//return location;
}