#ifndef MOUSE_HANDLER_H
#define MOUSE_HANDLER_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"

#include <iostream>

class
MouseHandler {
private:
	Camera& camera;
	float prevX;
	float prevY;
	float dragSens;
	float scrollSens;

public:
	MouseHandler(Camera& _camera, float _prevX, float _prevY);
	static void dragCallback(GLFWwindow* window, double xpos, double ypos); // Must Be Static C Func Ptr
	static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	void handleDrag(float xpos, float ypos);
	void handleScroll(float xoffset, float yoffset);

};

#endif
