#include "classHeaders.h"

cameraHandler::cameraHandler(posVector _camPos, posVector _camTarget) :
	camPos(glm::vec3(_camPos.x, _camPos.y, _camPos.z)),
	camTarget(glm::vec3(_camTarget.x, _camTarget.y, _camTarget.z)) {

	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	camZ = glm::normalize(camPos - camTarget);
	camX = glm::normalize(glm::cross(up, camZ));
	camY = glm::cross(camZ, camX);

}

glm::mat4 cameraHandler::getLookAt() {
	glm::mat4 lookAt = glm::lookAt(camPos, camTarget, camY);
	return lookAt;
}
