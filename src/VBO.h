#ifndef VBO_H
#define VBO_H

#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <vector>
#include <string>

#include "ShaderProgram.h"


class BufferObject
{
public:
	GLvoid* data;
	GLint dataCount; //3 vertecis -> 3
	GLint dataSize;	//3 vertecis -> 3*sizeof(GLfloat)
	GLuint handle;
	BufferObject();
	BufferObject(const BufferObject& copy);
	//BufferObject(GLfloat* data, int dataCount);
	//raw data size, meaning vertex*GLFLOAT
	//GLboolean create(GLfloat* data, int dataCount);//needs args

};

class IBO : public BufferObject
{
public:
	IBO();
	IBO(const IBO& copy);
	GLboolean create(GLuint* data, int dataCount);
};


//Vertex Buffer Object: contains actual vertex data (in GPU memory): vertecis(3/4f)
class VBO : public BufferObject 
{
public:
	VBO();
	VBO(const VBO& copy);
	VBO(GLfloat* data, int dataCount);
	GLboolean create(GLfloat* data, int dataCount);
};


//Vertex Array Object: a VBO "container"
class VAO : public BufferObject
{
public:
	VAO();
	VAO(const VAO& copy);
	~VAO();
	void create();//perhaps a bool would be more appropriate
	void addVbo(VBO vbo);
	void addIBO(IBO ibo);

	void setShader(ShaderProgram shadr);
	void setShader(std::string files); //leave out the extension, it will presume .vert and .frag shaders

	void render();


protected:
	std::vector<VBO> vbo;
	std::vector<IBO> ibo;
	ShaderProgram shader;
};

#endif