#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(const char*& vertexSrc, const char*& fragmentSrc) {
	colorUniforms.clear();	

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
ShaderProgram::addColorUniform(const char* name, glm::vec3 rgb) {
	colorUniforms.push_back((ColorUniform){name, rgb});		
}

void 
ShaderProgram::bindColors() {
	for(ColorUniform cu : colorUniforms) {
		int colorLoc = glGetUniformLocation(shaderProgram, cu.name);
		glUniform3fv(colorLoc, 1, glm::value_ptr(cu.rgb));
	}
}
