#ifndef CUBE_H
#define	CUBE_H

#include "sphere.h"
#include "vec.h"

class Cube : public vec3f
{
public:

  //vec3f getLocation();
	vec3f getCenter();
	vec3f getMinCorner();
	vec3f getMaxCorner();
	vec3f getSize();

	void setCenter(vec3f location);
	void setCenter(float x, float y, float z);
	void setRotation(vec3f rotation);
	void setRotation(float x, float y, float z);
	void setSize(vec3f size);
	void setSize(float x, float y, float z);


	bool contains(vec3f point);
	bool contains(Cube box);

	Sphere toSphere();

	void render();

	Cube();
	//Cube(Cube& cube);
	Cube(vec3f location, vec3f size);
	Cube(vec3f location, float size);
	static Cube createMinCorner(vec3f location, vec3f size);
	static Cube createMinCorner(vec3f location, float size);
	~Cube();
protected:
	vec3f rotation;
	vec3f size;
	using::vec3f::x;
	using::vec3f::y;
	using::vec3f::z;
};

#endif
