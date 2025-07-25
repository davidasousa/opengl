#include "MouseHandler.h"

MouseHandler::MouseHandler(Camera& _camera, float _prevX, float _prevY) :
	camera(_camera), prevX(_prevX), prevY(_prevY), sensitivity(0.05f) {
	
}

void 
MouseHandler::mouseCallback(GLFWwindow* window, double xpos, double ypos) {
	MouseHandler& instance = *(static_cast<MouseHandler*>(glfwGetWindowUserPointer(window)));
	instance.handleMouseDrag(static_cast<float>(xpos), static_cast<float>(ypos));
}

void
MouseHandler::handleMouseDrag(float xpos, float ypos) {
	float xoffset = sensitivity * (xpos - prevX);
	float yoffset = sensitivity * (ypos - prevY);

	camera.setCamera(xoffset, yoffset);

	prevX = xpos;
	prevY = ypos;
}
