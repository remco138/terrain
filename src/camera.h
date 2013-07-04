#ifndef CAMERA_H
#define CAMERA_H

#include "shapes/vec.h"
#include "Input.h"
#include <SFML/OpenGL.hpp>

class Camera : public Cube
{
public:
	Camera();

	void correctHeight(const HeightMap& hm);

	//vec3f getLocation();
	//vec3f getAngle();

	//void setLocation(vec3f location);
	//void setAngle(vec2f angle);

	void render();
	void update();
private:
	float sensitivity;
	float speed;
};
/*
class Spectator : 
{
public:

}*/

#endif