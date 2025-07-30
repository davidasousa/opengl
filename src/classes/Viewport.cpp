#include "Viewport.h"

Viewport::Viewport(std::vector<unsigned int> _shaders) : 
	modelMat(glm::mat4(1.0f)), viewMat(glm::mat4(1.0f)), shaders(_shaders) {	

}

void 
Viewport::addShader(unsigned int sp) {
	shaders.push_back(sp);
}

void 
Viewport::modelMatTranslate(shiftVector shift) {
	modelMat = glm::translate(modelMat, glm::vec3(shift.x, shift.y, shift.z));
}

void 
Viewport::modelMatRotate(float degreeRotation, tiltVector tilt) {
	modelMat = glm::rotate(modelMat, glm::radians(degreeRotation), glm::vec3(tilt.x, tilt.y, tilt.z));
}

void 
Viewport::modelMatScale(scaleVector scale) {
	modelMat = glm::scale(modelMat, glm::vec3(scale.x, scale.y, scale.z));
}

void 
Viewport::viewSetLookAt(const Camera& camera) {
	viewMat = camera.getLookAt();
}

void 
Viewport::viewShiftCamera(shiftVector shift) {
	viewMat = glm::translate(viewMat, glm::vec3(shift.x, shift.y, shift.z));
}

void 
Viewport::projectionSetPerspective(float fovY, float aspectRatio, float nearPlaneDist, float farPlaneDist) {
	projectionMat = glm::perspective(glm::radians(fovY), aspectRatio, nearPlaneDist, farPlaneDist);
}

void 
Viewport::bindViewportTransform() {
	for(unsigned int sp : shaders) {
		int modelMatLoc = glGetUniformLocation(sp, "modelMat");
		int viewMatLoc = glGetUniformLocation(sp, "viewMat");
		int projectionMatLoc = glGetUniformLocation(sp, "projectionMat");

		glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
		glUniformMatrix4fv(viewMatLoc, 1, GL_FALSE, glm::value_ptr(viewMat));
		glUniformMatrix4fv(projectionMatLoc, 1, GL_FALSE, glm::value_ptr(projectionMat));		
	}
	*this = Viewport(shaders);
}
