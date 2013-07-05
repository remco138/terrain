#include "HeightmapStreamer.h"

std::vector<float> planeGenerator(vec2f location, vec2f size, int skipNum)
{
	std::vector<float> vertecis;//size.x*size.y*3);
	vertecis.reserve(size.x*size.y*3);
	for(unsigned int x = 0; x < size.x; x++)
	{
		for(unsigned int z = 0; z < size.y; z++)
		{
			vertecis.push_back(x);
			vertecis.push_back(0);
			vertecis.push_back(z);
			/*
			//Old array based code...
			vertecis[x*size.x*3+z*3]		= static_cast<float>(x);
			vertecis[x*size.x*3+z*3+1]	= static_cast<float>(0);
			vertecis[x*size.x*3+z*3+2]	= static_cast<float>(z);
			*/
		}
	}
	return vertecis;
}

float distances[5] = { 1500, 1000, 500, 200, 100 };
HeightmapStreamer::HeightmapStreamer() : lodDistances(std::begin(distances), std::end(distances))
{
}

HeightmapStreamer::HeightmapStreamer(Quadtree* tree)
{
	this->tree = tree;
}

void HeightmapStreamer::changeTree(Quadtree* tree)
{
	this->tree = tree;
	tree->boundingBox.setSize(1024, 200, 1024);
	//update():
}

void HeightmapStreamer::setLodRanges(std::vector<float> distances)
{
	lodDistances = distances;
}

void HeightmapStreamer::setStreamSource(std::vector<float> (*source)(vec2f location, vec2f size, int skipNum))
{
	streamSource = source;
}

void HeightmapStreamer::render(vec3f viewpoint)
{
	if(tree)
	{
		tree->render(viewpoint);
	}
}

void HeightmapStreamer::update(vec3f viewpoint, bool force)
{
	//Don't update when we haven't moved or if a tree hasn't been set
	if(lastViewpoint != viewpoint && tree || force == true)
	{
		//Just store the tree, we only want 1 copy...
		std::vector<Quadtree*> children;
		children.push_back(tree);

		for(int level = 0; level < lodDistances.size(); level++)
		{
			for(int i = 0; i < children.size(); i++)
			{
				if((children[i]->boundingBox.getCenter() - viewpoint).length() < lodDistances[level])
				{
					Cube& bbox= children[i]->boundingBox;
					std::vector<float> vertecis = streamSource(bbox.getMinCorner().removeY(), bbox.getSize().removeY(), pow(2, lodDistances.size() - level));
					VBO vbo(&vertecis[0], vertecis.size()/3);//*sizeof(GLfloat));
					TerrainLod lodApplier;
					//1 subdivide, will in total split into 4 chunks
					std::vector<IBO> ibo = lodApplier.generateIndexes(vertecis, level, 1);
					std::vector<VAO> vao;

					//upload to GPU, multiple index buffers will do their pointing to a single vertex buffer
					for(int k = 0; k < ibo.size(); k++) { vao.push_back(VAO()); vao[k].create(); vao[k].addVbo(vbo); vao[k].addIBO(ibo[k]); vao[k].create(); }
					children[i]->addChildren(vao);
				}
				//Remove chunks because we're too far away
				else if(children[i]->getChildren().size() != 0)
				{
					children[i]->removeChildren();
				}
			}
		}
	}
}
