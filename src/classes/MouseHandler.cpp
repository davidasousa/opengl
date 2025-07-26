#include "MouseHandler.h"

MouseHandler::MouseHandler(Camera& _camera, float _prevX, float _prevY) :
	camera(_camera), prevX(_prevX), prevY(_prevY), dragSens(0.05f), scrollSens(0.1f) {
	
}

void 
MouseHandler::dragCallback(GLFWwindow* window, double xpos, double ypos) {
	MouseHandler& instance = *(static_cast<MouseHandler*>(glfwGetWindowUserPointer(window)));
	instance.handleDrag(static_cast<float>(xpos), static_cast<float>(ypos));
}

void
MouseHandler::handleDrag(float xpos, float ypos) {
	float xoffset = dragSens * (xpos - prevX);
	float yoffset = dragSens * (ypos - prevY);

	camera.setCamera(xoffset, yoffset);

	prevX = xpos;
	prevY = ypos;
}

void 
MouseHandler::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	MouseHandler& instance = *(static_cast<MouseHandler*>(glfwGetWindowUserPointer(window)));
	instance.handleScroll(static_cast<float>(xoffset), static_cast<float>(yoffset));
}

void
MouseHandler::handleScroll(float xoffset, float yoffset) {
	camera.translatePosY(scrollSens * yoffset);
}
