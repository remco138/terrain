#include "Quadtree.h"

//float lodDistances[5] = { 50, 200, 400, 700, 1000 };
float lodDistances[] = { 1500, 1000, 500, 200, 100 };
int maxLodLevel = 5;

vec3f Quadtree::heightmapSize = vec3f(0, 0, 0);

Quadtree::Quadtree() : level(0), isLeaf(true)
{
}

Quadtree::Quadtree(VBO vertecis, vec3f location, vec3f size, int level, ShaderProgram shader, bool recur) : boundingBox(location, size)
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
	this->heightmapSize = size;

	//Static. HeightmapSize holds the size of the entire heightmap and is accesible by every child
	//(fixme) Keep this in mind when for some reason creating another Quadtree object
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
	if (shader.success) 
		vao.setShader(shader);

	if(level < maxLodLevel || recur == false)
	{
		isLeaf = false;

		vec3f childrenSize = boundingBox.getSize() / vec3f(2, 1, 2);
		Quadtree node1(vertecis, location								, size / vec3f(2, 1, 2), level + 1, shader, true);
		Quadtree node2(vertecis, location + vec3f(childrenSize.x, 0, 0), size / vec3f(2, 1, 2), level + 1, shader, true);
		Quadtree node3(vertecis, location + vec3f(0, 0, childrenSize.z), size / vec3f(2, 1, 2), level + 1, shader, true);
		Quadtree node4(vertecis, location + vec3f(childrenSize.x, 0, childrenSize.z), size / vec3f(2, 1, 2), level + 1, shader, true);

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

std::vector<Quadtree> Quadtree::getChildren()
{
	return treeList;
}

void Quadtree::removeChildren()
{
	treeList.clear();
}
/*
Quadtree::Quadtree(vec3f<float> vertecis, vec3f location, int skipNum)
{

}*/

/*
void Quadtree::addChildren(std::vector<float> vertecis, vec3f location)
{
	//Spec states that vectors store their data contiguously, so this is a save way to do this
	VBO terrainVbo(&vertecis[0], vertecis.size*sizeof(GLfloat));
	//Place a nice shader for the terrain here, placeholder for now
	ShaderProgram shader;

	vec3f childrenSize = boundingBox.getSize() / vec3f(2, 1, 2);
	Quadtree node1(&vertecis[0], location,												size / vec3f(2, 1, 2), level + 1, shader, false);
	Quadtree node2(&vertecis[0], location + vec3f(childrenSize.x, 0, 0),				size / vec3f(2, 1, 2), level + 1, shader, false);
	Quadtree node3(&vertecis[0], location + vec3f(0, 0, childrenSize.z),				size / vec3f(2, 1, 2), level + 1, shader, false);
	Quadtree node4(&vertecis[0], location + vec3f(childrenSize.x, 0, childrenSize.z),	size / vec3f(2, 1, 2), level + 1, shader, false);

	treeList.push_back(node1);
	treeList.push_back(node2);
	treeList.push_back(node3);
	treeList.push_back(node4);
}*/

Quadtree::Quadtree(VAO vao, vec3f location, vec3f size, int level) : vao(vao), boundingBox(location, size)
{
	isLeaf = true;
}

void Quadtree::addChildren(std::vector<VAO> vao)
{
	isLeaf = false;
	//Place a nice shader for the terrain here, placeholder for now
	ShaderProgram shader;
	vec3f childrenSize = boundingBox.getSize() / vec3f(2, 1, 2);
	vec3f location = boundingBox.getMinCorner();

	Quadtree node1(vao[0], location,											childrenSize, level + 1);
	Quadtree node2(vao[1], location + vec3f(childrenSize.x, 0, 0),				childrenSize, level + 1);		 
	Quadtree node3(vao[2], location + vec3f(0, 0, childrenSize.z),				childrenSize, level + 1);	 
	Quadtree node4(vao[3], location + vec3f(childrenSize.x, 0, childrenSize.z),childrenSize, level + 1);

	treeList.push_back(node1);
	treeList.push_back(node2);
	treeList.push_back(node3);
	treeList.push_back(node4);

}

Quadtree::~Quadtree()
{

}

//instead of distances:
//does contain point?
//:yes?
//	split (render child)
//:no?
//	render this

void Quadtree::render(vec3f location)
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