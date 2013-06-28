#ifndef SPHERE_H
#define SPHERE_H

#include "figure3D.h"
#include "vec.h"

class Sphere : public Figure3D
{
public:
	/*
	float& x;
	float& y;
	float& z;
	*/
	bool contains(vec3f point);
	bool intersects(Sphere sphere);

	Sphere();
	Sphere(vec3f loc, float diameter); 
	~Sphere();
};

#endif //SPHERE_H