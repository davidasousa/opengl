#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

// GLAD Dynamic OpenGL Includes
#include <glad/glad.h>

// Including GLM Math Library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <unordered_map>
#include <utility>

class 
ShaderProgram {
private:
	unsigned int shaderProgram;
	bool shaderLinkageError;
	std::unordered_map<std::string, glm::vec3> uniforms;

public:
	ShaderProgram(const char*& vertexSrc, const char*& fragmentSrc);
	unsigned int getShaderProgram() const;
	void addUniform(std::string name, glm::vec3 vec);
	void bindUniforms();

};

#endif
