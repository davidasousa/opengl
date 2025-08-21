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
	std::unordered_map<std::string, float> floatUniforms;
	std::unordered_map<std::string, int> intUniforms;

public:
	ShaderProgram(const char*& vertexSrc, const char*& fragmentSrc);
	unsigned int getShaderProgram() const;
	void addUniform(std::string name, glm::vec3 vec);
	void addUniform(std::string name, float fl);
	void addUniform(std::string name, int in);
	void bindUniforms();

};

#endif
