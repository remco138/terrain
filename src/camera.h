#ifndef CAMERA_H
#define CAMERA_H

#include "shapes/vec.h"
#include "Input.h"
#include <SFML/OpenGL.hpp>

/*
class AbstractInput
{
};

class AbstractCamera
{
};

class AbstractPlayerController
{
};

class Camera : public AbstractCamera
{
};


class MyInput : public AbstractInput
{
	MyInput( MyController* ctrl ) : ctrl(ctrl) { }
	MyController* ctrl
};
//------------------------------------------------------


class InputComponent
{
public:
	bindKey(const char* name, 
};

//-------------------------------------------------------
*/
class Camera
{
public:
	Camera();

	void correctHeight(const HeightMap& hm);

	vec3f getLocation();
	vec2f getAngle();

	void setLocation(vec3f location);
	void setAngle(vec2f angle);

	void render();
	void update();
private:
	float sensitivity;
	float speed;
	vec3f location;
	vec2f angle;
};

#endif