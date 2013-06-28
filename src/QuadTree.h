#ifndef QUADTREE_H
#define QUADTREE_H

#include <vector>
#include "VBO.h"
#include "shapes/vec.h"
#include "shapes/cube.h"
#include "ShaderProgram.h"

//extern float lodDistances[5];
//extern int maxLodLevel;

class QuadTree 
{
private:
	int level;
	std::vector<QuadTree> treeList;
	QuadTree *children[4];
	Cube boundingBox;
	static vec3f heightmapSize;
	bool isLeaf;
	float maxLodDistance;


	VAO vao;
public:
	QuadTree(VBO vertecis, vec3f location, vec3f size, int level, ShaderProgram shader);
	~QuadTree();
	void render(vec3f location);
};

#endif