/*
#include "classHeaders.h"

MouseHandler::mouseHandler(Camera& _camera) :
	camera(_camera), prevX(0.0f), prevY(0.0f) {

}

static void 
MouseHandler::mouseCallback(GLFWwindow* window, double xpos, double ypos) {
	MouseHandler& instance = *(static_cast<const camera*>(glfwGetWindowUserPointer(window)));
	instance.shiftCameraTarget({xpos, ypos});
}

void
MouseHandler::shiftCameraTarget(const float xpos, const float ypos) {
	camera.translateTarget(glm::vec3(0.0f, 0.0f, 0.0f));
}
*/
