#include "Viewport.h"

Viewport::Viewport(unsigned int _shaderProgram) : 
	modelMat(glm::mat4(1.0f)), viewMat(glm::mat4(1.0f)), shaderProgram(_shaderProgram) {

}

void Viewport::modelMatTranslate(shiftVector shift) {
	modelMat = glm::translate(modelMat, glm::vec3(shift.x, shift.y, shift.z));
}

void Viewport::modelMatRotate(float degreeRotation, tiltVector tilt) {
	modelMat = glm::rotate(modelMat, glm::radians(degreeRotation), glm::vec3(tilt.x, tilt.y, tilt.z));
}

void Viewport::viewSetLookAt(const Camera& camera) {
	viewMat = camera.getLookAt();
}

void Viewport::viewShiftCamera(shiftVector shift) {
	viewMat = glm::translate(viewMat, glm::vec3(shift.x, shift.y, shift.z));
}

void Viewport::projectionSetPerspective(float fovY, float aspectRatio, float nearPlaneDist, float farPlaneDist) {
	projectionMat = glm::perspective(glm::radians(fovY), aspectRatio, nearPlaneDist, farPlaneDist);
}

void Viewport::bindViewportTransform() {
	int modelMatLoc = glGetUniformLocation(shaderProgram, "modelMat");
	int viewMatLoc = glGetUniformLocation(shaderProgram, "viewMat");
	int projectionMatLoc = glGetUniformLocation(shaderProgram, "projectionMat");

	glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
	glUniformMatrix4fv(viewMatLoc, 1, GL_FALSE, glm::value_ptr(viewMat));
	glUniformMatrix4fv(projectionMatLoc, 1, GL_FALSE, glm::value_ptr(projectionMat));
	
	*this = Viewport{shaderProgram};
}
