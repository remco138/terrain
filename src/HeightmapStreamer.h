#ifndef HEIGHTMAPSTREAMER_H
#define HEIGHTMAPSTREAMER_H
#include <vector>
#include "shapes/vec.h"
#include "Quadtree.h"
#include "TerrainLod.h"

//temporary
std::vector<float>& planeGenerator(vec2f location, vec2f size, int skipNum);

class HeightmapStreamer
{
public:
	HeightmapStreamer();
	HeightmapStreamer(Quadtree* tree);
	void changeTree(Quadtree* tree); //Use some OOP magic here to allow Quadtree, Octree and Whatevertree
	void setLodRanges(std::vector<float> distances);
	//location: min corner to start generating, so we can continue constructing the heightmao after movement
	//size: amount of vertecis we wish to receive
	//skipNum: amount of vertecis we want to skip
	void setStreamSource(std::vector<float>& (*source)(vec2f location, vec2f size, int skipNum));

	void render(vec3f viewpoint);
	void update(vec3f viewpoint, bool force = false);
protected:
	std::vector<float>& (*streamSource)(vec2f, vec2f, int);
	Quadtree* tree;
	vec3f lastViewpoint;
	std::vector<float> lodDistances;
};

#endif