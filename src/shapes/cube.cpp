#include "cube.h"
#include "vec.h"
#include <algorithm>
#include <SFML/OpenGL.hpp>

void Cube::render()
{
	glBegin(GL_LINES);
	glVertex3f(location.x, location.y, location.z); //bottomleft to right
	glVertex3f(location.x + size.x, location.y, location.z);

	glVertex3f(location.x, location.y, location.z); //bottomleft to up
	glVertex3f(location.x, location.y + size.y, location.z);

	glVertex3f(location.x, location.y, location.z); //botomleft to depth
	glVertex3f(location.x, location.y, location.z + size.z);

	glVertex3f(location.x, location.y, location.z + size.z);//back left to right
	glVertex3f(location.x + size.x, location.y, location.z + size.z);

	glVertex3f(location.x + size.x, location.y, location.z); //bottom right to depth
	glVertex3f(location.x + size.x, location.y, location.z + size.z);

	glVertex3f(location.x, location.y + size.y, location.z); //top left to to right
	glVertex3f(location.x + size.x, location.y + size.y, location.z);

	glVertex3f(location.x, location.y + size.y, location.z); //top left to depth
	glVertex3f(location.x, location.y + size.y, location.z + size.z);

	glVertex3f(location.x + size.x, location.y + size.y, location.z);//top right to depth
	glVertex3f(location.x + size.x, location.y + size.y, location.z + size.z);

	glVertex3f(location.x, location.y + size.y, location.z + size.z);//top back left to right
	glVertex3f(location.x + size.x, location.y + size.y, location.z + size.z);

	glVertex3f(location.x, location.y + size.y, location.z + size.z);
	glVertex3f(location.x + size.x, location.y + size.y, location.z + size.z);


	glVertex3f(location.x + size.x, location.y, location.z);//bottomright to up
	glVertex3f(location.x + size.x, location.y + size.y, location.z);

	glVertex3f(location.x, location.y, location.z + size.z); //bottombackleft to up
	glVertex3f(location.x, location.y + size.y, location.z + size.z);

	glVertex3f(location.x + size.x, location.y, location.z + size.z); //bottom back right to up
	glVertex3f(location.x + size.x, location.y + size.y, location.z + size.z);

	glEnd();
}

vec3f Cube::getSize()
{
	return size;
}

vec3f Cube::getLocation()
{
	return location;
}

vec3f Cube::getCenter()
{
	return center;
}

Cube::Cube() : x(location.x), y(location.y), z(location.z)
{
}

Cube::Cube(vec3f centr, vec3f extnds) : location(centr - extnds), size(extnds * 2), extends(extnds), center(centr), x(center.x), y(center.y), z(center.z)
{

}

Cube::Cube(vec3f centr, float len) : x(this->center.x), y(this->center.y), z(this->center.z)// : location(location), size(vec3f(length, length, length)), extends....
{
	this->center = centr;
	this->size = vec3f(len, len, len);
	float l = len / 2;
	this->extends = vec3f(l, l, l);
	this->location = center - extends;

}

Cube::~Cube()
{

}
bool Cube::contains(Cube box)
{
	vec3f x1 = box.location, x2 = box.location + vec3f(box.size.x, 0, 0), x3 = box.location + vec3f(0, box.size.y, 0), x4 = box.location + vec3f(box.size.x, box.size.y, 0);
	vec3f z1 = box.location + vec3f(0, 0, box.size.z), z2 = box.location + vec3f(box.size.x, 0, box.size.z), z3 = box.location + vec3f(0, box.size.y, box.size.z), z4 = box.location + vec3f(box.size.x, box.size.y, box.size.z);

	if(contains(x1) || contains(x2) || contains(x3) || contains(x4) ||
	   contains(z1) || contains(z2) || contains(z3) || contains(z4))
	{
		return true;
	}

	return false;
}

bool Cube::contains(vec3f point)
{
	if(point.x >= location.x && point.x <= location.x + size.x &&
	point.y >= location.y && point.y <= location.y + size.y &&
	point.z >= location.z && point.z <= location.z + size.z)
	{
		return true;
	}

	return false;
}


Sphere Cube::toSphere()
{
	return Sphere(center, std::max(std::max(center.x, center.y), center.z));
}