#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

// GLAD Dynamic OpenGL Includes
#include <glad/glad.h>

#include <vector>

#include "ColorManager.h"

class 
ShaderProgram {
private:
	unsigned int shaderProgram;
	bool shaderLinkageError;
	std::vector<ColorManager> colorManagerVec;

public:
	ShaderProgram(const char*& vertexSrc, const char*& fragmentSrc);
	unsigned int getShaderProgram() const;
	void addColorManager(ColorManager cm);
	void bindColorManager(int idx);

};

#endif
