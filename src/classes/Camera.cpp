#include "Camera.h"

Camera::Camera(posVector _camPos, posVector _camTarget) :
	camPos(glm::vec3(_camPos.x, _camPos.y, _camPos.z)),
	targetPos(glm::vec3(_camTarget.x, _camTarget.y, _camTarget.z)) {
	
	computeBasisVectors();
}

void Camera::translatePos(shiftVector shift) {
	camPos += glm::vec3(shift.x, shift.y, shift.z);
	computeBasisVectors();
}

void Camera::translateTarget(shiftVector shift) {
	targetPos += glm::vec3(shift.x, shift.y, shift.z);
	computeBasisVectors();
}

void Camera::computeBasisVectors() {
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	camBasisZ = glm::normalize(camPos - targetPos);
	camBasisX = glm::normalize(glm::cross(up, camBasisZ));
	camBasisY = glm::cross(camBasisZ, camBasisX);
}

glm::mat4 Camera::getLookAt() const {
	return glm::lookAt(camPos, targetPos, camBasisY);
}
