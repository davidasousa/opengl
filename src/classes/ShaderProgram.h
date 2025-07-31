#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

// GLAD Dynamic OpenGL Includes
#include <glad/glad.h>

// Including GLM Math Library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

typedef struct {
	const char* name;
	glm::vec3 rgb;
} ColorUniform;

class 
ShaderProgram {
private:
	unsigned int shaderProgram;
	bool shaderLinkageError;
	std::vector<ColorUniform> colorUniforms;

public:
	ShaderProgram(const char*& vertexSrc, const char*& fragmentSrc);
	unsigned int getShaderProgram() const;
	void addColorUniform(const char* name, glm::vec3 rgb);
	void bindColors();

};

#endif
