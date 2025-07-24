#ifndef CAMERA_H
#define CAMERA_H

// Including GLM Math Library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Types.h"

class
Camera {
private:
	glm::vec3 camPos;
	glm::vec3 targetPos;

	glm::vec3 camBasisX; // Basis Vectors Define The Orthogonal Directions Of The Cameras View
	glm::vec3 camBasisY;
	glm::vec3 camBasisZ;

	glm::mat4 lookAt;

	void computeBasisVectors();

public:
	Camera(posVector _camPos, posVector _camTarget);
	void translatePos(shiftVector shift);
	void translateTarget(shiftVector shift);
	glm::mat4 getLookAt() const;
};

#endif
