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

unsigned int 
ShaderProgram::getShaderProgram() const { return shaderProgram; }

void 
ShaderProgram::addUniform(std::string name, glm::vec3 vec) {
	uniforms[name] = vec;		
}

void 
ShaderProgram::addUniform(std::string name, float fl) {
	floatUniforms[name] = fl;		
}

void 
ShaderProgram::addUniform(std::string name, int in) {
	intUniforms[name] = in;		
}

void 
ShaderProgram::bindUniforms() {
	for(const std::pair<std::string, glm::vec3>& uniform : uniforms) {
		int uniformLoc = glGetUniformLocation(shaderProgram, uniform.first.c_str());
		glUniform3fv(uniformLoc, 1, glm::value_ptr(uniform.second));
	}

	for(const std::pair<std::string, float>& fl : floatUniforms) {
		int floatLoc = glGetUniformLocation(shaderProgram, fl.first.c_str());
		glUniform1f(floatLoc, fl.second);
	}

	for(const std::pair<std::string, float>& in : intUniforms) {
		int intLoc = glGetUniformLocation(shaderProgram, in.first.c_str());
		glUniform1i(intLoc, in.second);
	}
}
