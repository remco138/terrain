#ifndef QUADTREE_H
#define QUADTREE_H

#include <vector>
#include "VBO.h"
#include "shapes/vec.h"
#include "shapes/cube.h"
#include "ShaderProgram.h"

//extern float lodDistances[5];
//extern int maxLodLevel;

class Quadtree
{
public:
	Quadtree();
	//depricated?
	Quadtree(VBO vertecis, vec3f location, vec3f size, int level, ShaderProgram shader, bool recur);
	Quadtree(VAO vao, vec3f location, vec3f size, int level);
	//Quadtree(vec3f<float> vertecis, vec3f location, int skipNum);
	Quadtree(std::vector<VAO> vao, vec3f location, vec3f size);
	~Quadtree();
	void render(vec3f location);
	std::vector<Quadtree> getChildren();
	void addChildren(std::vector<float> vertecis, vec3f location);
	void addChildren(std::vector<VAO> vao); 
	void removeChildren();
	Cube boundingBox;

private:
	int level;
	std::vector<Quadtree> treeList;
	//Quadtree *children[4];
	static vec3f heightmapSize;
	bool isLeaf;
	float maxLodDistance;
	vec3f size;

	VAO vao;
	VBO vbo;
};

#endif