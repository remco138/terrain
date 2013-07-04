#include "cube.h"
#include "vec.h"
#include <algorithm>
#include <SFML/OpenGL.hpp>

 vec3f Cube::getCenter()
{
	return vec3f(x, y, z) + size*0.5f;
}

 vec3f Cube::getMinCorner()
{
	return vec3f(x, y, z);
}

 vec3f Cube::getMaxCorner()
{
	return vec3f(x, y, z) + size;
}

vec3f Cube::getSize()
{
  return vec3f(size.x, size.y, size.z);
}

void Cube::setCenter(vec3f location)
{
	x = location.x - size.x*0.5f;
	y = location.y - size.y*0.5f;
	z = location.z - size.z*0.5f;
}

void Cube::setCenter(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

void Cube::setRotation(vec3f rotation)
{
	this->rotation.z = rotation.x;
	this->rotation.y = rotation.y;
	this->rotation.z = rotation.z;
}

void Cube::setRotation(float x, float y, float z)
{
	rotation.x = x;
	rotation.y = y;
	rotation.z = z;
}

void Cube::setSize(vec3f size)
{
	this->size.x = size.x;
	this->size.y = size.y;
	this->size.z = size.z;
}

void Cube::setSize(float x, float y, float z)
{
	size.x = x;
	size.y = y;
	size.z = z;
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

Cube::Cube() : vec3f()
{
}

Cube::Cube(vec3f location, vec3f size) : vec3f(location), size(size), rotation(0, 0, 0)
{
}

Cube::Cube(vec3f location, float size) : vec3f(location), size(size, size, size), rotation(0, 0, 0)
{
}

Cube::~Cube()
{

}

Cube Cube::createMinCorner(vec3f location, vec3f size)
{
	return Cube(location - size*0.5f, size);
}
Cube Cube::createMinCorner(vec3f location, float size)
{
	return Cube(location - size*0.5f, size);
}

bool Cube::contains(Cube box)
{
  vec3f x1 = box.getMinCorner(), x2 = box.getMinCorner() + vec3f(box.size.x, 0, 0), x3 = box.getMinCorner() + vec3f(0, box.size.y, 0), x4 = box.getMinCorner() + vec3f(box.size.x, box.size.y, 0);
  vec3f z1 = box.getMinCorner() + vec3f(0, 0, box.size.z), z2 = box.getMinCorner() + vec3f(box.size.x, 0, box.size.z), z3 = box.getMinCorner() + vec3f(0, box.size.y, box.size.z), z4 = box.getMinCorner() + vec3f(box.size.x, box.size.y, box.size.z);

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
  return Sphere(getCenter(), std::max(std::max(x, y), z));
}
