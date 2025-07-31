#ifndef VIEWPORT_H
#define VIEWPORT_H

// GLAD Dynamic OpenGL Includes
#include <glad/glad.h>

// Including GLM Math Library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include "Camera.h"
#include "Types.h"

class 
Viewport {
private:
	std::vector<unsigned int>* shaders;

	glm::mat4 modelMat; 			// Object Translations + Scaling -> Global World Space
	glm::mat4 viewMat; 			  // Camera Translations
	glm::mat4 projectionMat;  // Perspective Matrix

public:
	Viewport(std::vector<unsigned int>* _shadersAddr);
	Viewport& operator=(Viewport&& other) noexcept; // Move Assignment

	void modelMatTranslate(shiftVector shift);
	void modelMatRotate(float degreeStep, tiltVector tilt);
	void modelMatScale(scaleVector scale);

	void viewSetLookAt(const Camera& camera);
	void viewShiftCamera(shiftVector shift);

	void projectionSetPerspective(float fovY, float aspectRatio, float nearPlaneDist, float farPlaneDist);

	void bindViewportTransform(int idx);

};

#endif
