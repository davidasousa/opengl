#ifndef CAMERA_H
#define CAMERA_H

#include <algorithm>

// Including GLM Math Library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Types.h"

#include <iostream>


class
Camera {
private:
	glm::vec3 camPos;
	glm::vec3 camDir;
	glm::vec3 camUp;

	float pitch;
	float yaw;
	float camSpeed;

	bool sprintFlag;
	float sprintScale;

	glm::mat4 lookAt;

public:
	Camera(posVector _camPos);
	void findLookAt();
	glm::mat4 getLookAt() const;
	void translatePosX(float dX);
	void translatePosY(float dY);
	void translatePosZ(float dZ);
	void setCamera(float xoffset, float yoffset);
	void toggleSprint();
};

#endif
