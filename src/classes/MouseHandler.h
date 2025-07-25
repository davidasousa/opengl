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
	float sensitivity;

public:
	MouseHandler(Camera& _camera, float _prevX, float _prevY);
	static void mouseCallback(GLFWwindow* window, double xpos, double ypos); // Must Be Static C Func Ptr
	void handleMouseDrag(float xpos, float ypos);

};

#endif
