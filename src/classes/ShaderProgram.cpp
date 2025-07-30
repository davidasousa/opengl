#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(const char*& vertexSrc, const char*& fragmentSrc) {
	colorManagerVec.clear();	

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

unsigned int 
ShaderProgram::getShaderProgram() const { return shaderProgram; }

void 
ShaderProgram::addColor(ColorManager cm) {
	colorManagerVec.push_back(cm);		
}

void 
ShaderProgram::bindColors() {
	for(ColorManager cm : colorManagerVec) {
		int colorLoc = glGetUniformLocation(shaderProgram, cm.getName());
		glUniform3fv(colorLoc, 1, glm::value_ptr(cm.getColor()));
	}
}
