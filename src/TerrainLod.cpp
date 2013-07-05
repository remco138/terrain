#include "TerrainLod.h"

std::vector<IBO> TerrainLod::generateIndexes(std::vector<float> vertecis, int lodLevel, int subdivides)
{
	vec2f chunkAmount(std::pow(2, subdivides));
	vec2f size(std::sqrt(vertecis.size()/3));
	vec2f chunkSize(size.x/chunkAmount.x);
	//lodDivider: Amount of vertecis that will be skipped, power of 2,
	//meaning every level deeper we go the amount of vertecis we skip will be double. maxLodLevel - highest level = 0; 2^0 = 1
	int lodDivider = 8;//pow(2.0f, maxLodLevel - level);
	int lastRowX = 0;//(boundingbox.getmincorner().x + boundingBox.getSize().x == heightmapSize.x) ? lodDivider : 0;
	int lastRowY = 0;//(boundingBox.getMinCorner().z + boundingBox.getSize().z == heightmapSize.z) ? lodDivider : 0;	
	int indexNum = (size.x - lodDivider) * (size.y - lodDivider) * 6 / lodDivider;
	vec2u row(0, 0);
	std::vector<unsigned int> indexData;
	std::vector<IBO> ibo(chunkAmount.x*chunkAmount.y);// Fill 
	int counter = 0;


	for(row.x = 0; row.x < chunkAmount.y; row.x++)
	{
		for(row.y = 0; row.y < chunkAmount.y; row.y++)
		{
			indexData.clear();
			indexData.reserve(chunkSize.x*chunkAmount.y*6);
			//Caution, might nork work yet!
			for(unsigned int x = chunkSize.x*(row.x); x < chunkSize.x*(row.x+1) - lastRowX; x += lodDivider)
			{
				for(unsigned int y = chunkSize.y*(row.y); y < chunkSize.y*(row.y+1) - lastRowY; y += lodDivider)
				{
					indexData.push_back((x * size.y) + y);
					indexData.push_back((x * size.y) + y + lodDivider);
					indexData.push_back((x + lodDivider) * size.x + y);

					indexData.push_back((x * size.y) + y + lodDivider );
					indexData.push_back((x + lodDivider) * size.y + y);
					indexData.push_back((x + lodDivider) * size.y + y + lodDivider);
				}
			}
			//Upload our indexes to the GPU and put it in a good ol' handy IBO
			//ibo.push_back(IBO());
			ibo[counter].create(&indexData[0], indexData.size());
			counter++;
			//make room for next chunk
			indexData.clear();
		}
	}
	return ibo;

}