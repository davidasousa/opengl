#include "Camera.h"

Camera::Camera(posVector _camPos) : 
	pitch(0.0f), yaw(-90.0f), camSpeed(2.0f), sprintFlag(false), sprintScale(3.0f) {
			
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
	glm::vec3 updateVec = camSpeed * dX * glm::normalize(glm::cross(camDir, camUp));
	if(sprintFlag) { updateVec *= sprintScale; }
	camPos += updateVec;
	findLookAt();
}

void 
Camera::translatePosY(float dY) {
	glm::vec3 updateVec = camSpeed * dY * camUp;
	if(sprintFlag) { updateVec *= sprintScale; }
	camPos += updateVec;
	findLookAt();
}

void 
Camera::translatePosZ(float dZ) {
	glm::vec3 updateVec = camSpeed * dZ * camDir;
	if(sprintFlag) { updateVec *= sprintScale; }
	camPos += updateVec;
	findLookAt();
}

void 
Camera::setCamera(float xoffset, float yoffset) {

	yaw += xoffset;
	pitch = std::clamp(pitch - yoffset, -89.99f, 89.99f); // Mouse Inverted By Default

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	camDir = glm::normalize(direction);
	findLookAt();
}

void
Camera::toggleSprint() {
	sprintFlag = !sprintFlag;
}
