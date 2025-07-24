#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(const char*& vertexSrc, const char*& fragmentSrc) {
	shaderProgram = glCreateProgram();
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	GLint success;

	glShaderSource(vertexShader, 1, &vertexSrc, NULL);
	glShaderSource(fragmentShader, 1, &fragmentSrc, NULL);

	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram); 
	
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	shaderLinkageError = static_cast<bool>(success);
}

unsigned int ShaderProgram::getShaderProgram() const { return shaderProgram; }
