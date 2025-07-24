#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

// GLAD Dynamic OpenGL Includes
#include <glad/glad.h>

class 
ShaderProgram {
private:
	unsigned int shaderProgram;
	bool shaderLinkageError;

public:
	ShaderProgram(const char*& vertexSrc, const char*& fragmentSrc);
	unsigned int getShaderProgram() const;
};

#endif
