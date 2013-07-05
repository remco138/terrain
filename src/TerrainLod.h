#ifndef TERRAIN_H
#define TERRAIN_H
#include <vector>
#include "shapes/vec.h"
#include "VBO.h"

class TerrainLod
{
public:
	TerrainLod() {};
	//returns multiple index files, size = subdivides
	std::vector<IBO> generateIndexes(std::vector<float> vertecis, int lodLevel, int subdivides);
};

#endif