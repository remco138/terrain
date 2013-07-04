#include "QuadTree.h"

//float lodDistances[5] = { 50, 200, 400, 700, 1000 };
float lodDistances[] = { 1500, 1000, 500, 200, 100 };
int maxLodLevel = 5;

vec3f QuadTree::heightmapSize = vec3f(0, 0, 0);

QuadTree::QuadTree(VBO vertecis, vec3f location, vec3f size, int level, ShaderProgram shader) : boundingBox(location, size)
{
	this->level = level;
	maxLodDistance = lodDistances[level];
	//lodDivider: Amount of vertecis that will be skipped, power of 2,
	//meaning every level deeper we go the amount of vertecis we skip will be double. maxLodLevel - highest level = 0; 2^0 = 1
	int lodDivider = pow(2.0f, maxLodLevel - level);
	//These variables are needed to check whether we are at the edge of the chunk, and if so,ignore it,
	//otherwise the edge indexes in GPU memory will point to nonexistant vertecis for some reason
	int lastRowX = (boundingBox.getMinCorner().x + boundingBox.getSize().x == heightmapSize.x) ? lodDivider : 0;
	int lastRowZ = (boundingBox.getMinCorner().z + boundingBox.getSize().z == heightmapSize.z) ? lodDivider : 0;	
	int indexNum = (boundingBox.getSize().x - lodDivider) * (boundingBox.getSize().z - lodDivider) * 6 / lodDivider;
	std::vector<unsigned int> indexData(indexNum);	//Reserve the memory we will use, this will optimize the code a bit
	indexData.reserve(indexNum*2);

	//Static. HeightmapSize holds the size of the entire heightmap and is accesible by every child
	//(fixme) Keep this in mind when for some reason creating another QuadTree object
	if(level == 0)//root
	{
		this->heightmapSize = size;
	}

	for(unsigned int x = boundingBox.getMinCorner().x; x < boundingBox.getMinCorner().x + boundingBox.getSize().x - lastRowX; x += lodDivider)
	{
		for(unsigned int z = boundingBox.getMinCorner().z; z < boundingBox.getMinCorner().z + boundingBox.getSize().z - lastRowZ; z += lodDivider)
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
	//vao.setShader(shader);

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
	//Cube cameraBox(location, lodDistances[level]);
	//cameraBox.render();	
	if(!isLeaf && (boundingBox.getCenter() - location).length() < lodDistances[level]) //(boundingBox.contains(location) || boundingBox.contains(cameraBox) || cameraBox.contains(boundingBox)))//boundingBox.toSphere().intersects(range)*/)
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
	default:
		glColor3f(0.5, 0.5, 0.5);
	}
		boundingBox.render();

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		vao.render();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}