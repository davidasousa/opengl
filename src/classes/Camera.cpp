#include "Camera.h"

Camera::Camera(posVector _camPos) : 
	pitch(0.0f), yaw(-90.0f), camSpeed(0.01f) {
			
	camPos = glm::vec3(_camPos.x, _camPos.y, _camPos.z);
	camDir = glm::vec3(0.0f, 0.0f, 1.0f);
	camUp = glm::vec3(0.0f, 1.0f, 0.0f);
	
	findLookAt();
}

void
Camera::findLookAt() {
	lookAt = glm::lookAt(camPos, camPos + camDir, camUp);
}

glm::mat4 
Camera::getLookAt() const { return lookAt; }

void 
Camera::translatePosX(float dX) {
	camPos += glm::normalize(glm::cross(camDir, camUp)) * camSpeed;
	findLookAt();
}

void 
Camera::translatePosZ(float dZ) {
	camPos += camSpeed * camDir;
	findLookAt();
}

void 
Camera::setCamera(float xoffset, float yoffset) {

	pitch = std::min(pitch - yoffset, 89.0f);
	yaw = std::min(yaw + xoffset, 89.0f);

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	camDir = glm::normalize(direction);
	findLookAt();
}
