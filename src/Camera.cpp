#include "heightMap.h"
#include "camera.h"

Camera::Camera()
{
	sensitivity = 1;
	speed = 1;
}

vec3f Camera::getLocation()
{
	return location;
}

vec2f Camera::getAngle()
{
	return angle;
}

void Camera::correctHeight(const HeightMap& hm)
{
	if(isKeyPressed(sf::Keyboard::C))
	{
		location = hm.getNearestVertex(location);//+ vec3f(0, 15, 0);
	}
}

/*
 *
 *temporary global variables, these should go into a player class
 *
 */
bool isWalking = false;

vec3f velocity;
//float speed = 0;

float dotProduct(vec3f arg1, vec3f arg2) { return arg1.x*arg2.x + arg1.y*arg2.y + arg1.z*arg2.z;  }
//vec3f normalize(vec3f arg) { int t = arg.length(); return   }

void Camera::update()
{
	//test!
	/*
	wishSpeed = normalize(wishDir)


	 * currentSpeed = dotProduct(velocity, wishDir); (wishDir = camera direction? z/depth =?)
	 * addSpeed = wishSpeed - currentSpeed; //wishSpeed = ?
	 * if(addSpeed <= 0) return
	 * accelSpeed = accel*frameTime*wishSpeed;
	 * if(accepSpeedl > addSpeed) accelSpeed = addSpeed
	 *
	 * velocity += accelSpeed * wishDir
	 */

	//printf("%f, %f, %f\n", location.x, location.y, location.z);
	vec2i mouseDifference = getMouseDifference();
	angle.x += mouseDifference.y * sensitivity; //lack of operators in my vector classes, this needs cleaning up
	angle.y += mouseDifference.x * sensitivity;


	vec3f wishDir;
	if(isKeyPressed(sf::Keyboard::E))
	{
		speed = 10;
	}
	else if(isKeyPressed(sf::Keyboard::Q))
	{
		speed = 0.1;
	}
	else
	{
		speed = 1;
	}
	if(isKeyPressed(sf::Keyboard::W))
	{
		float xrad = angle.x / 180 * 3.141592654f;
		float yrad = angle.y / 180 * 3.141592654f;
		wishDir.x += sin(yrad) * speed;
		wishDir.z -= cos(yrad) * speed;
		wishDir.y -= sin(xrad) * speed;
	}
	if(isKeyPressed(sf::Keyboard::S))
	{
		float xrad = angle.x / 180 * 3.141592654f;
		float yrad = angle.y / 180 * 3.141592654f;
		wishDir.x -= sin(yrad) * speed;
		wishDir.z += cos(yrad) * speed;
		wishDir.y += sin(xrad) * speed;
	}
	if(isKeyPressed(sf::Keyboard::A))
	{
		float xrad = angle.x / 180 * 3.141592654f;
		float yrad = angle.y / 180 * 3.141592654f;
		wishDir.x -= cos(yrad) * speed;
		wishDir.z -= sin(yrad) * speed;

	}
	if(isKeyPressed(sf::Keyboard::D))
	{
		float xrad = angle.x / 180 * 3.141592654f;
		float yrad = angle.y / 180 * 3.141592654f;
		wishDir.x += cos(yrad) * speed;
		wishDir.z += sin(yrad) * speed;
	}
	if(isKeyPressed(sf::Keyboard::Space))
	{
		wishDir.y += 1 * speed;
	}

	if(isKeyPressed(sf::Keyboard::LControl))
	{
		wishDir.y -= 1 * speed;
	}


	//incoming accel argument is a constant (4.0f => water accel)
	//float addSpeed = 0, accelSpeed = 0, currentSpeed = 0;
	/*float accel = 4;

	float currentSpeed = dotProduct(velocity, wishDir); //(wishDir = camera direction? z/depth =?)
	float wishSpeed = wishDir.length(); //normalize->length
	float addSpeed = wishSpeed - currentSpeed; //wishSpeed = ?
	if(addSpeed <= 0) return;
	float accelSpeed = accel*wishSpeed;
	if(accelSpeed > addSpeed) accelSpeed = addSpeed;
	*/

	//velocity = vec3f(accelSpeed, accelSpeed, accelSpeed) * wishDir;
	location += wishDir;
	velocity = vec3f(0, 0, 0);
}

void Camera::setLocation(vec3f location)
{
	this->location = location;
}

void Camera::setAngle(vec2f angle)
{
	this->angle = angle;
}

void Camera::render()
{
	glRotatef(angle.x, 1.0, 0.0, 0.0);
	glRotatef(angle.y, 0.0, 1.0, 0.0);
	glTranslatef(-location.x, -location.y, -location.z);
}