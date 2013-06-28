#include "sphere.h"
/*
float Sphere::getDiameter()
{
	return diameter;
}

vec3f Sphere::getLocation()
{
	return location;
}
*/

Sphere::Sphere() : Figure3D()
{
}

Sphere::Sphere(vec3f loc, float diameter) : Figure3D(loc, diameter) 
{

}

Sphere::~Sphere()
{

}

bool Sphere::intersects(Sphere sphere)
{
	if((center-sphere.center).length() < size.x / 2)
	{
		return true;
	}

	return false;
}

bool Sphere::contains(vec3f point)
{
	if((center - point).length() < size.x / 2)
	{
		return true;
	}

	return false;
}