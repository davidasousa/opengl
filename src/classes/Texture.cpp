#include "Texture.h"

// Including STBI Fileloader -> Must Be In CPP File
#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

enum fileFormat { ERR = -1, JPG, PNG };

Texture::Texture(unsigned int _shaderProgram) : 
	availTexturePos(0), shaderProgram(_shaderProgram) {

	std::fill(textureUnits.begin(), textureUnits.end(), 0);
}

static fileFormat 
getInternalFormat(std::string filepath) {
	size_t dotPos = filepath.find_last_of('.');
	std::string filetype;

	if(dotPos == std::string::npos) { return ERR; }
	else { filetype =	filepath.substr(dotPos + 1); }

	if(filetype == "jpg") { return JPG; }
	else if(filetype == "png") { return PNG; }
	else { return ERR; }
}

// Returns Pos On Load, -1 On Error
void 
Texture::loadConfigTexture(const std::string filepath) {
	if(availTexturePos == textureUnits.size()) { return; }

	int width, height, nrChannels;	
	unsigned char *data = stbi_load(filepath.c_str(), &width, &height, &nrChannels, 0);
	if(!data) { std::cout << stbi_failure_reason() << std::endl; }

	glGenTextures(1, &textureUnits[availTexturePos]);
	glBindTexture(GL_TEXTURE_2D, textureUnits[availTexturePos]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	switch (getInternalFormat(filepath)) {
	case JPG:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		break;
	case PNG:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		break;
	}

	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
	availTexturePos++;
}

void 
Texture::bindTextureUnits() {
	glUseProgram(shaderProgram);
	for(size_t idx = 0; idx < availTexturePos; idx++) {
		std::string textureName = std::string("texture") + std::to_string(idx + 1);
		glUniform1i(glGetUniformLocation(shaderProgram, textureName.c_str()), idx);
	}
}

void 
Texture::bindTextures() {
	glUseProgram(shaderProgram);
	for(size_t idx = 0; idx < availTexturePos; idx++) {
		glActiveTexture(GL_TEXTURE0 + idx);
		glBindTexture(GL_TEXTURE_2D, textureUnits[idx]);
	}
}
