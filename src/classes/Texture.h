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

	std::array<unsigned int, MAX_TEXTURE_UNITS> textureUnits;
	int availTexturePos;

public:
	Texture(unsigned int _shaderProgram);
	void loadConfigTexture(const std::string filepath, bool flipImage);
	void bindTextureUnits(); 	// Bind Texture Units To Shader
	void bindTextures(); 		 	// Bind Textures To Texture Units (In Rendering)
};

#endif
