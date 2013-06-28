#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H


#include <string>

#include "shapes/vec.h"
#include "VBO.h"
#include "QuadTree.h"

#include <SFML/Config.hpp>

class HeightMap
{
public:
	vec2u size;
	int vertexCount;
	GLfloat* vertexData;
	VBO vbo;
	QuadTree* tree;

	HeightMap() {};
	bool init();
	VBO create(const char* file);
	IBO createIndexes(); 
	void render(vec3f location);
	vec3f getNearestVertex(const vec3f location) const;
};

#endif