#include "cube.h"
#include "vec.h"
#include <algorithm>
#include <SFML/OpenGL.hpp>



vec3f Cube::getLocation()
{
  return vec3f(x, x, z);
}

vec3f Cube::getSize()
{
  return vec3f(size.x, size.y, size.z);
}

void Cube::render()
{
	glBegin(GL_LINES);
	glVertex3f(x, y, z); //bottomleft to right
	glVertex3f(x + size.x, y, z);

	glVertex3f(x, y, z); //bottomleft to up
	glVertex3f(x, y + size.y, z);

	glVertex3f(x, y, z); //botomleft to depth
	glVertex3f(x, y, z + size.z);

	glVertex3f(x, y, z + size.z);//back left to right
	glVertex3f(x + size.x, y, z + size.z);

	glVertex3f(x + size.x, y, z); //bottom right to depth
	glVertex3f(x + size.x, y, z + size.z);

	glVertex3f(x, y + size.y, z); //top left to to right
	glVertex3f(x + size.x, y + size.y, z);

	glVertex3f(x, y + size.y, z); //top left to depth
	glVertex3f(x, y + size.y, z + size.z);

	glVertex3f(x + size.x, y + size.y, z);//top right to depth
	glVertex3f(x + size.x, y + size.y, z + size.z);

	glVertex3f(x, y + size.y, z + size.z);//top back left to right
	glVertex3f(x + size.x, y + size.y, z + size.z);

	glVertex3f(x, y + size.y, z + size.z);
	glVertex3f(x + size.x, y + size.y, z + size.z);


	glVertex3f(x + size.x, y, z);//bottomright to up
	glVertex3f(x + size.x, y + size.y, z);

	glVertex3f(x, y, z + size.z); //bottombackleft to up
	glVertex3f(x, y + size.y, z + size.z);

	glVertex3f(x + size.x, y, z + size.z); //bottom back right to up
	glVertex3f(x + size.x, y + size.y, z + size.z);

	glEnd();
}


Cube::Cube(vec3f location, vec3f size) : vec3f(x, y, z), size(size)
{

}

Cube::Cube(vec3f location, float size) : vec3f(x, y, z), size(size, size, size)
{
  
}

Cube::~Cube()
{

}
bool Cube::contains(Cube box)
{
  vec3f x1 = box.getLocation(), x2 = box.getLocation() + vec3f(box.size.x, 0, 0), x3 = box.getLocation() + vec3f(0, box.size.y, 0), x4 = box.getLocation() + vec3f(box.size.x, box.size.y, 0);
  vec3f z1 = box.getLocation() + vec3f(0, 0, box.size.z), z2 = box.getLocation() + vec3f(box.size.x, 0, box.size.z), z3 = box.getLocation() + vec3f(0, box.size.y, box.size.z), z4 = box.getLocation() + vec3f(box.size.x, box.size.y, box.size.z);

	if(contains(x1) || contains(x2) || contains(x3) || contains(x4) ||
	   contains(z1) || contains(z2) || contains(z3) || contains(z4))
	{
		return true;
	}

	return false;
}

bool Cube::contains(vec3f point)
{
	if(point.x >= x && point.x <= x + size.x &&
	point.y >= y && point.y <= y + size.y &&
	point.z >= z && point.z <= z + size.z)
	{
		return true;
	}

	return false;
}


Sphere Cube::toSphere()
{
  return Sphere(getLocation(), std::max(std::max(x, y), z));
}
