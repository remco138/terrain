#ifndef FIGURE3D_H
#define FIGURE3D_H

#include "vec.h"

class Figure3D
{
public:
	vec3f getLocation();
	vec3f getSize();
	vec3f getCenter();
	vec3f getExtends();

	void setLocation(const vec3f&  arg);
	void setSize(const vec3f&  arg);
	void setCenter(const vec3f&  arg);
	void setExtends(const vec3f&  arg);

	virtual void render();

	Figure3D();
	Figure3D(vec3f centr, float len); //presume symmetry, len is corner to corner
	Figure3D(vec3f centr, vec3f len); //len is corner to corner



protected:
	vec3f location;
	vec3f size;
	vec3f center; //the middle of the object
	vec3f extends; //vector from the center to the outer end
};

#endif //FIGURE3D_h