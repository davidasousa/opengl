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
typedef struct { float x; float y; float z; } posVector;

class 
vertexBufferObject {
private:
	unsigned int vbo;

public:
	vertexBufferObject();
	unsigned int getVertexBufId();

	void bindArrayBuf();
	bool bufferVertexAttrs(std::vector<float>& verticies, GLenum usage);
	bool configVertexAttr(int attrPos, int attrWidth, int attrStride, int attrOffset);
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

class
cameraHandler {
private:
	glm::vec3 camPos;
	glm::vec3 camTarget;

	glm::vec3 camX; 
	glm::vec3 camY;
	glm::vec3 camZ;

	glm::mat4 lookAt;

public:
	cameraHandler(posVector _camPos, posVector _camTarget);
	glm::mat4 getLookAt();
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

	void modelMatTranslate(shiftVector shift);
	void modelMatRotate(float degreeStep, tiltVector tilt);

	void viewSetLookAt(glm::mat4 lookAt);
	void viewShiftCamera(shiftVector shift);

	void projectionSetPerspective(float fovY, float aspectRatio, float nearPlaneDist, float farPlaneDist);

	void bindViewportTransform();

};
