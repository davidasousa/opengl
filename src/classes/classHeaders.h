// Definitions Of Classes + Methods

// Including STL Headers
#include <array>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>

// GLAD Dynamic OpenGL Includes
#include <glad/glad.h>

// Including GLM Math Library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Constants
#define UNBIND_VAO 0
#define MAX_TEXTURE_UNITS 16


// Enum
enum fileFormat { ERR = -1, JPG, PNG };

// Structs
typedef struct { float x; float y; float z; } tiltVector;
typedef struct { float x; float y; float z; } shiftVector;

class 
vertexBufferObject {
private:
	unsigned int vbo;
	GLenum target; // Purpose Of The VBO
	GLenum usage; // How The VBO Will Be Drawn

public:
	vertexBufferObject(GLenum _target, GLenum _usage);
	void bind();
	void bufferData(std::vector<float>& verticies);
};

class 
vertexAttributeObject {
private:

public:

};

class 
shaderProgramHandler {
private:
	unsigned int shaderProgram;
	bool shaderLinkageError;

public:
	shaderProgramHandler(const char*& vertexSrc, const char*& fragmentSrc);
	unsigned int getShaderProgramId() const;
};

// Shader Texture Class -> Group Textures Meant For A Shader
class 
textureHandler {
private:
	unsigned int shaderProgram;

	std::array<unsigned int, MAX_TEXTURE_UNITS> textureUnits;
	int availTexturePos;

public:
	textureHandler(unsigned int _shaderProgram);
	void loadConfigTexture(const std::string filepath);
	void bindTextureUnits(); 	// Bind Texture Units To Shader
	void bindTextures(); 		 	// Bind Textures To Texture Units (In Rendering)
};

// Viewport Transformations
class 
viewportHandler {
private:
	unsigned int shaderProgram;

	glm::mat4 modelMat; 			// Object Translations + Scaling -> Global World Space
	glm::mat4 viewMat; 			  // Camera Translations
	glm::mat4 projectionMat;  // Perspective Matrix

public:
	viewportHandler(unsigned int _shaderProgram);
	void modelMatRotate(float degreeStep, tiltVector tilt);
	void viewShiftCamera(shiftVector tilt);
	void projectionSetPerspective(float fovY, float aspectRatio, float nearPlaneDist, float farPlaneDist);
	void bindViewportTransform();

};
