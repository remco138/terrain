#include "figure3D.h"

vec3f Figure3D::getLocation()
{
	return location;
}

vec3f Figure3D::getSize()
{
	return size;
}

vec3f Figure3D::getCenter()
{
	return center;
}

vec3f Figure3D::getExtends()
{
	return extends;
}


void Figure3D::setLocation(const vec3f&  arg)
{
	center += location - arg;
	location = arg;
}

void Figure3D::setSize(const vec3f&  arg)
{
	extends += size - arg;
	size = arg;
}

void Figure3D::setCenter(const vec3f&  arg)
{
	location += center -arg;
	center = arg;
}

void Figure3D::setExtends(const vec3f&  arg)
{
	size += extends - arg;
	extends = arg;
}

void Figure3D::render()
{

}


Figure3D::Figure3D() : center(), location(), size(), extends()
{

}

Figure3D::Figure3D(vec3f centr, float len) : location(centr - vec3f(len, len, len) / 2), size(vec3f(len, len, len)), extends(vec3f(len, len, len) / 2), center(centr)
{

}

Figure3D::Figure3D(vec3f centr, vec3f len) : location(centr - len / 2), size(len), extends(len / 2), center(centr)
{

}
