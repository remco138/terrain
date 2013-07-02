#include "GL/glew.h"
#include <SFML/OpenGL.hpp>

#include "ShaderProgram.h"
#include <fstream>
#include <iostream>

ShaderProgram::ShaderProgram() : success(false), programHandle(0), vertHandle(0), fragHandle(0), geoHandle(0)
{

}

ShaderProgram::ShaderProgram(const char* files) : success(false), programHandle(0), vertHandle(0), fragHandle(0), geoHandle(0)
{
	create(files);
}



ShaderProgram::~ShaderProgram()
{
	glUseProgram(0);
	//glDisableVertexAttribArray(0);
	//glDisableVertexAttribArray(1);
	glDetachShader(programHandle, vertHandle);
	glDetachShader(programHandle, fragHandle);
	glDeleteProgram(programHandle);
	glDeleteShader(vertHandle);
	glDeleteShader(fragHandle);
	//glDeleteBuffers(1, &vbo.at(0).handle);
	//glDeleteVertexArrays(1, &handle);
}

bool ShaderProgram::create(const char* files)
{
	shaderFileName = files;
	std::ifstream file;

	file.open((shaderFileName + ".vert").c_str(), std::ios::in);
	//file.read(vertShaderContent, file.tellg());
	vertShaderContent.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	file.close();
	vertShaderContent += '\0';

	file.open((shaderFileName + ".frag").c_str(), std::ios::in);
	fragShaderContent.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	file.close();
	fragShaderContent += '\0';

	std::cout << vertShaderContent + "\n------------------------------------------\n";
	std::cout << fragShaderContent + "\n\n";

	vertHandle = glCreateShader(GL_VERTEX_SHADER);
	const char* t = vertShaderContent.c_str();
	glShaderSource(vertHandle, 1, &t, 0);
	glCompileShader(vertHandle);

	int isCompiled = 999;
	char* log;
	int maxLogLength = 0;
	
	glGetShaderiv(vertHandle, GL_COMPILE_STATUS, &isCompiled);
	if(isCompiled == GL_FALSE)
	{
		int maxLogLength = 0;
		glGetShaderiv(vertHandle, GL_INFO_LOG_LENGTH, &maxLogLength);
		log = new char[maxLogLength];
		glGetShaderInfoLog(vertHandle, maxLogLength, &maxLogLength, log);
		std::cout << log;
		delete log;
		success = false;
		return false;	
	}
	
	const char* t2 = fragShaderContent.c_str();
	fragHandle = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragHandle, 1, &t2, 0);
	glCompileShader(fragHandle);

	isCompiled = -1;
	glGetShaderiv(fragHandle, GL_COMPILE_STATUS, &isCompiled);
	if(isCompiled == GL_FALSE)
	{
		glGetShaderiv(fragHandle, GL_INFO_LOG_LENGTH, &maxLogLength);
		log = new char[maxLogLength];
		glGetShaderInfoLog(fragHandle, maxLogLength, &maxLogLength, log);
		delete log;
		success = false;
		return false;
	}



	/* If we reached this point it means the vertex and fragment shaders compiled and are syntax error free. */
	/* We must link them together to make a GL shader program */
	/* GL shader programs are monolithic. It is a single piece made of 1 vertex shader and 1 fragment shader. */
	/* Assign our program handle a "name" */
	programHandle = glCreateProgram();
 
	/* Attach our shaders to our program */
	glAttachShader(programHandle, vertHandle);
	glAttachShader(programHandle, fragHandle);
 
	/* Bind attribute index 0 (coordinates) to in_Position and attribute index 1 (color) to in_Color */
	/* Attribute locations must be setup before calling glLinkProgram. */
	glBindAttribLocation(programHandle, 0, "in_Position");
			//glBindAttribLocation(programHandle, 1, "in_Color");
 
	/* Link our program */
	/* At this stage, the vertex and fragment programs are inspected, optimized and a binary code is generated for the shader. */
	/* The binary code is uploaded to the GPU, if there is no error. */
	glLinkProgram(programHandle);
 
	/* Again, we must check and make sure that it linked. If it fails, it would mean either there is a mismatch between the vertex */
	/* and fragment shaders. It might be that you have surpassed your GPU's abilities. Perhaps too many ALU operations or */
	/* too many texel fetch instructions or too many interpolators or dynamic loops. */

	int isLinked = 999;
	glGetProgramiv(programHandle, GL_LINK_STATUS, &isLinked);
	if(isLinked == GL_FALSE)
	{
	   /* Noticed that glGetProgramiv is used to get the length for a shader program, not glGetShaderiv. */
	   glGetProgramiv(programHandle, GL_INFO_LOG_LENGTH, &maxLogLength);
	
	   /* The maxLogLength includes the NULL character */
	   log = new char[maxLogLength];
 
	   /* Notice that glGetProgramInfoLog, not glGetShaderInfoLog. */
	   glGetProgramInfoLog(programHandle, maxLogLength, &maxLogLength, log);
 
	   /* Handle the error in an appropriate way such as displaying a message or writing to a log file. */
	   /* In this simple program, we'll just leave */
	   delete log;
	   success = false;
	   return false;
	}

	int error = -1;
	glValidateProgram(programHandle);
	glGetProgramiv(programHandle, GL_VALIDATE_STATUS, &error);
	if(error == GL_FALSE)
	{
	   glGetProgramiv(programHandle, GL_INFO_LOG_LENGTH, &maxLogLength);
	
	   log = new char[maxLogLength];
 
	   glGetProgramInfoLog(programHandle, maxLogLength, &maxLogLength, log);
 
	   delete log;
	   success = false;
	   return false;
	}

	//glDetachShader(programHandle, vertHandle);
	//glDetachShader(programHandle, fragHandle);

	success = true;
	return true;
}
