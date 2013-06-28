#ifndef CUBE_H
#define	CUBE_H

#include "sphere.h"
#include "vec.h"

class Cube
{
public:
	float& x;
	float& y;
	float& z;
	
	vec3f getSize();
	vec3f getLocation();
	vec3f getCenter();

	bool contains(vec3f point);
	bool contains(Cube box);

	Sphere toSphere();

	void render();

	Cube();
	//Cube(Cube& cube);
	Cube(vec3f location, vec3f size);
	Cube(vec3f center, float length);
	~Cube();
protected:
	vec3f location;
	vec3f size;
	vec3f center;
	vec3f extends; //the distance from center to side (maybe this should be to point?)
};

#endif