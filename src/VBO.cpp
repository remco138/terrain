#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <fstream>

#include "VBO.h"

BufferObject::BufferObject()
{
}
/*
BufferObject::BufferObject(GLfloat* data, int dataCount)
{
	create(data, dataCount);
}*/

IBO::IBO()
{
}

GLboolean IBO::create(GLuint* data, int dataCount)
{
	glGenBuffers(1, &handle);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, dataCount * sizeof(GLuint), data, GL_STATIC_DRAW);

	this->dataCount = dataCount;
	return true;
}
VBO::VBO()
{
}

VBO::VBO(GLfloat* data, int dataCount)
{
	create(data, dataCount);
}

GLboolean VBO::create(GLfloat* data, int dataCount)
{
	this->dataCount = dataCount;
	glGenBuffers(1, &handle);
	glBindBuffer(GL_ARRAY_BUFFER, handle);
	//dataCount should be "1024*1024 * sizeof(GLfloat)" for a 1024*1024 heightmap
	glBufferData(GL_ARRAY_BUFFER, dataCount*3*sizeof(GLfloat), data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return true;
}

VAO::VAO()
{
}

VAO::~VAO()
{
	    /* Cleanup all the things we bound and allocated */
	/*
    glUseProgram(0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDetachShader(shaderProgram, vertShaderHandle);
    glDetachShader(shaderProgram, fragShaderHandle);
    glDeleteProgram(shaderProgram);
    glDeleteShader(vertShaderHandle);
    glDeleteShader(fragShaderHandle);
	glDeleteBuffers(1, &vbo.at(0).handle);
    glDeleteVertexArrays(1, &handle);
	*/
}

void VAO::create()
{
	glGenVertexArrays(1, &handle);
}

void VAO::addVbo(VBO vbo)
{
	//bind the VAO so opengl knows to which VBO it shall assign
	glBindVertexArray(handle);
	//bind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, vbo.handle);
//	glVertexPointer(3, GL_FLOAT, 0, 0);

	//enable it so vertecis actually get passed (bindAttrib is needed to assign to a shader var)
	glEnableVertexAttribArray(0);

	//assign "vertex data" to index 0(in the VAO), stride could be of use for LOD?
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER, 0); <- doing this inside VAO will actually deactivate it again
	glBindVertexArray(0);

	this->vbo.push_back(vbo);
}

void VAO::addIBO(IBO ibo)
{
	glBindVertexArray(handle);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo.handle);
	glBindVertexArray(0);
	this->ibo.push_back(ibo);
}

void VAO::setShader(std::string files)
{
	glBindVertexArray(handle);
	shader.create(files.c_str());
	glUseProgram(shader.programHandle);
	glBindVertexArray(0);
}

void VAO::setShader(ShaderProgram shadr)
{
	glBindVertexArray(handle);
	shader = shadr;

	glUseProgram(shader.programHandle);
	glBindVertexArray(0);
}

void VAO::render()
{
	if(shader.success)
	{
		glUseProgram(shader.programHandle);
	}
	if(ibo.size() != 0)
	{
		glBindVertexArray(handle);	
		glDrawElements(GL_TRIANGLES, ibo[0].dataCount, GL_UNSIGNED_INT, NULL );//0 may have to be set to indexes handle
		glBindVertexArray(0);
	}
	else
	{
	glBindVertexArray(handle);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_POINTS,0, vbo.at(0).dataCount);
	glBindVertexArray(0);
	}
}
