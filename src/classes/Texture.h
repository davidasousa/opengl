#ifndef TEXTURE_H
#define TEXTURE_H

// GLAD Dynamic OpenGL Includes
#include <glad/glad.h>

// STL Libraries
#include <unordered_map>
#include <string>
#include <iostream>

#define MAX_TEXTURE_UNITS 16
#define UNBIND_VAO 0

enum class fileFormat { ERR = -1, JPG, PNG };

class 
Texture {
private:
	unsigned int shaderProgram;
	std::string textureName;
	unsigned int textureID;

public:
	Texture(unsigned int _shaderProgram, std::string _textureName);
	void loadTexture(const std::string filepath, bool flipImage = false);
	void bindTextureUnit(); 	// Bind Texture Units To Shader
	void bindTexture(); 		 	// Bind Textures To Texture Units (In Rendering)
};

#endif
