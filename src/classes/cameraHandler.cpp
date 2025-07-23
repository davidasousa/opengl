#include "classHeaders.h"

cameraHandler::cameraHandler(posVector _camPos, posVector _camTarget) :
	camPos(glm::vec3(_camPos.x, _camPos.y, _camPos.z)),
	camTarget(glm::vec3(_camTarget.x, _camTarget.y, _camTarget.z)) {
	
	computeBasisVectors();
}

void cameraHandler::translate(shiftVector shift) {
	camPos += glm::vec3(shift.x, shift.y, shift.z);
	computeBasisVectors();
}

void cameraHandler::computeBasisVectors() {
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	camBasisZ = glm::normalize(camPos - camTarget);
	camBasisX = glm::normalize(glm::cross(up, camBasisZ));
	camBasisY = glm::cross(camBasisZ, camBasisX);
}

glm::mat4 cameraHandler::getLookAt() const {
	return glm::lookAt(camPos, camTarget, camBasisY);
}
