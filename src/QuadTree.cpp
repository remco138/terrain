#include "QuadTree.h"

//float lodDistances[5] = { 50, 200, 400, 700, 1000 };
float lodDistances[] = { 2200, 1500, 800, 500, 200 };
int maxLodLevel = 5;

vec3f QuadTree::heightmapSize = vec3f(0, 0, 0);

QuadTree::QuadTree(VBO vertecis, vec3f location, vec3f size, int level, ShaderProgram shader) : boundingBox(location + size / 2, size / 2)
{
	this->level = level;
	int t = pow(2.0f, level);
	//printf("%f, %f, %f\n", boundingBox.getLocation().x, boundingBox.getLocation().y, boundingBox.getLocation().z);

	maxLodDistance = lodDistances[level];
	int lodDivider = pow(2.0f, maxLodLevel - level);
	int indexNum = (boundingBox.getSize().x - lodDivider) * (boundingBox.getSize().z - lodDivider) * 6 / lodDivider;
	std::vector<unsigned int> indexData;
	indexData.reserve(indexNum);

	int lastRowX = 0;//lodDivider;
	int lastRowZ = 0;//lodDivider;
	if(level == 0)//root
	{
		this->heightmapSize = size;
	}
	if(boundingBox.getLocation().x + boundingBox.getSize().x == heightmapSize.x)
	{
		lastRowX = lodDivider;
	}
	if(boundingBox.getLocation().z + boundingBox.getSize().z == heightmapSize.z)
	{
		lastRowZ = lodDivider;
	}

	for(unsigned int x = boundingBox.getLocation().x; x < boundingBox.getLocation().x + boundingBox.getSize().x - lastRowX; x += lodDivider)
	{
		for(unsigned int z = boundingBox.getLocation().z; z < boundingBox.getLocation().z + boundingBox.getSize().z - lastRowZ; z += lodDivider)
		{
			indexData.push_back((x * heightmapSize.z) + z);
			indexData.push_back((x * heightmapSize.z) + z + lodDivider);
			indexData.push_back((x + lodDivider) * heightmapSize.x + z);

			indexData.push_back((x * heightmapSize.z) + z + lodDivider );
			indexData.push_back((x + lodDivider) * heightmapSize.z + z);
			indexData.push_back((x + lodDivider) * heightmapSize.z + z + lodDivider);
		}
	}

	vao.create();	
	IBO indexes;
	indexes.create(&indexData[0], indexData.size());
	vao.addVbo(vertecis);
	vao.addIBO(indexes);
	vao.setShader(shader);

	if(level < maxLodLevel)
	{
		isLeaf = false;

		vec3f childrenSize = boundingBox.getSize() / vec3f(2, 1, 2);
		QuadTree node1(vertecis, location								, size / vec3f(2, 1, 2), level + 1, shader);
		QuadTree node2(vertecis, location + vec3f(childrenSize.x, 0, 0), size / vec3f(2, 1, 2), level + 1, shader);
		QuadTree node3(vertecis, location + vec3f(0, 0, childrenSize.z), size / vec3f(2, 1, 2), level + 1, shader);
		QuadTree node4(vertecis, location + vec3f(childrenSize.x, 0, childrenSize.z), size / vec3f(2, 1, 2), level + 1, shader);

		treeList.push_back(node1);
		treeList.push_back(node2);
		treeList.push_back(node3);
		treeList.push_back(node4);
	}
	else
	{
		isLeaf = true;
	}
}

QuadTree::~QuadTree()
{

}

//instead of distances:
//does contain point?
//:yes?
//	split (render child)
//:no?
//	render this

void QuadTree::render(vec3f location)
{
	Cube cameraBox(location, lodDistances[level]);
	//cameraBox.render();	
	if(!isLeaf && (boundingBox.contains(location) || boundingBox.contains(cameraBox) || cameraBox.contains(boundingBox)))//boundingBox.toSphere().intersects(range)*/)
	{
		for(int k = 0; k < 4; k++)
		{
			treeList[k].render(location);
		}
		return;
	}
	
	switch(level)
	{
	case 0:
		glColor3f(1, 0, 0);
		break;
	case 1:
		glColor3f(1, 1, 0);
		break;
	case 2:
		glColor3f(0, 0, 1);
		break;
	case 3:
		glColor3f(0, 1, 1);
		break;
	case 4:
		glColor3f(0, 1, 0);
		break;
	case 5:
		glColor3f(1, 1, 1);
	}
		//boundingBox.render();

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		vao.render();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}