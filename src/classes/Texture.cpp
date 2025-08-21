#include "Texture.h"

// Including STBI Fileloader -> Must Be In CPP File
#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

Texture::Texture(unsigned int _shaderProgram, std::string _textureName) : 
	shaderProgram(_shaderProgram), textureName(_textureName) {}

static fileFormat 
getInternalFormat(std::string filepath) {
	size_t dotPos = filepath.find_last_of('.');
	std::string filetype;

	if(dotPos == std::string::npos) { return fileFormat::ERR; }
	else { filetype =	filepath.substr(dotPos + 1); }

	return [](std::string filetype){
		if(filetype == "jpg") { return fileFormat::JPG; }
		if(filetype == "png") { return fileFormat::PNG; }
		return fileFormat::ERR;
	}(filetype);

}

// Returns Pos On Load, -1 On Error
void 
Texture::loadTexture(const std::string filepath, bool flipImage) {
	int width, height, nrChannels;	
	if(flipImage) { stbi_set_flip_vertically_on_load(true); }
	else { stbi_set_flip_vertically_on_load(false); }
	
	unsigned char *data = stbi_load(filepath.c_str(), &width, &height, &nrChannels, 0);
	if(!data) { std::cout << stbi_failure_reason() << std::endl; }

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	switch (getInternalFormat(filepath)) {
	case fileFormat::JPG:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		break;
	case fileFormat::PNG:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		break;
	}

	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
}

void 
Texture::bindTextureUnit() {
	glUseProgram(shaderProgram);
	glUniform1i(glGetUniformLocation(shaderProgram, textureName.c_str()), 0);
}

void 
Texture::bindTexture() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
}
