#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <string>

class ShaderProgram
{
public:
	ShaderProgram();
	ShaderProgram(const char* files); //no file extensions, function presumes .vert/.frag
	~ShaderProgram();

	bool create(const char* files);
	bool success;
//protected:
	unsigned int programHandle;
	unsigned int vertHandle, fragHandle, geoHandle;

	std::string shaderFileName;
	std::string vertShaderContent, fragShaderContent, geoShaderContent;
};

#endif //SHADERPROGRAM_H