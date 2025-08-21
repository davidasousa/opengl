#ifndef TEXTURE_H
#define TEXTURE_H

// GLAD Dynamic OpenGL Includes
#include <glad/glad.h>

// STL Libraries
#include <array>
#include <string>
#include <iostream>

#define MAX_TEXTURE_UNITS 16
#define UNBIND_VAO 0

enum class fileFormat { ERR = -1, JPG, PNG };

class 
Texture {
private:
	unsigned int shaderProgram;
	size_t arrayPos;
	std::array<std::string, MAX_TEXTURE_UNITS> textureNames;
	std::array<unsigned int, MAX_TEXTURE_UNITS> textureIds;

public:
	Texture(unsigned int _shaderProgram);
	void loadAddTexture(const std::string filepath, std::string name, bool flipImage = false);
	void bindTextureUnit(); 	// Bind Texture Units To Shader
	void bindTexture(); 		 	// Bind Textures To Texture Units (In Rendering)
};

#endif
