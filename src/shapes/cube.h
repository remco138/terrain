#ifndef CUBE_H
#define	CUBE_H

#include "sphere.h"
#include "vec.h"

class Cube : public vec3f
{
public:

  vec3f getLocation();
  vec3f getSize();
	bool contains(vec3f point);
	bool contains(Cube box);

	Sphere toSphere();

	void render();

	Cube();
	//Cube(Cube& cube);
	Cube(vec3f location, vec3f size);
	Cube(vec3f location, float size);
	~Cube();
protected:
	
	vec3f size;
};

#endif
