// OpenGL Includes
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// General Includes
#include <iostream>
#include <cmath>

// Including Custom Classes
#include "classes/Types.h"

#include "classes/VertexBufferObject.h"
#include "classes/ShaderProgram.h"
#include "classes/Texture.h"
#include "classes/Camera.h"
#include "classes/Viewport.h"
#include "classes/MouseHandler.h"

#include "shapes/Rectangle.h"


shiftVector translations[] {
	{0.0f, 0.0f, 1.0f}, 
	{3.0f, -1.0f, 1.0f}
};

// Basic Vertex Shader
const char* vertexShaderSource = R"GLSL(
	#version 330 core
	layout (location = 0) in vec3 aPos;

	uniform mat4 modelMat;
	uniform mat4 viewMat;
	uniform mat4 projectionMat;

	void main() 
	{
		gl_Position = projectionMat * viewMat * modelMat * vec4(aPos, 1.0);
	}
)GLSL";

// Fragment Shader
const char* fragmentShaderSource = R"GLSL(
	#version 330 core
	out vec4 FragColor;

	uniform vec3 lightColor;

	void main()
	{
		FragColor = vec4(lightColor, 1.0);
	}
)GLSL";

static void // Polling
processInput(GLFWwindow* window, Camera& cam, float dT) { 
	// Esc Triggers Window Close
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	// WASD
	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		cam.translatePosZ(dT);
	}
	if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		cam.translatePosZ(-1 * dT);
	}
	if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		cam.translatePosX(dT);
	}
	if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		cam.translatePosX(-1 * dT);
	}

	// Toggle Sprint
	if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		cam.toggleSprint();
	}
	
}

int 
main() {
	// Init GLFW
	glfwInit();

	// OpenGL V3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Creating A Window
	float windowX = 800.0f, windowY = 600.0f;
	GLFWwindow* window = glfwCreateWindow(windowX, windowY, "MyWindow", NULL, NULL);
	if(window == NULL) {
		std::cout << "Failed To Create GLFW Window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Window Config
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	// Loading Glad
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	float aspectRatio = windowX / windowY;
	glViewport(0, 0, windowX, windowY);
	glEnable(GL_DEPTH_TEST); // Z Depth Conditional Rendering
													 
	Camera camera((posVector){0.0f, 0.0f, 3.0f});	

	// Input Handlers	
	MouseHandler mouseHandler(camera, windowX / 2.0f, windowY / 2.0f);
	
	glfwSetCursorPosCallback(window, &mouseHandler.dragCallback);
	glfwSetScrollCallback(window, &mouseHandler.scrollCallback);
	glfwSetWindowUserPointer(window, &mouseHandler);

	// Create Rectangle
	Rectangle rectangleModel;

	// Creating Object VAO
	unsigned int lightVAO;
	glGenVertexArrays(1, &lightVAO);

	glBindVertexArray(lightVAO);

	VertexBufferObject rectangleVBO;
	rectangleVBO.bindArrayBuf();
	rectangleVBO.bufferVertexAttrs(rectangleModel.getVerticies(), GL_STATIC_DRAW);
	rectangleVBO.configVertexAttrs(rectangleModel.getFormat(false));

	ColorManager lightManager("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
	ColorManager objectManager("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));

	ShaderProgram shaderProgram(vertexShaderSource, fragmentShaderSource);
	shaderProgram.addColorManager(lightManager);
	shaderProgram.addColorManager(objectManager);

	Viewport viewport(shaderProgram.getShaderProgram());	

	// Setting Colors
	// Frame Render Managers
	float deltaTime = 0.0f;
	float prevFrameTime = 0.0f;

	// Continuous Render Window
	while(!glfwWindowShouldClose(window)) {
		processInput(window, camera, deltaTime);

		glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindVertexArray(lightVAO);

		glUseProgram(shaderProgram.getShaderProgram());
		shaderProgram.bindColorManager(0);

		viewport.modelMatTranslate((shiftVector){0.0f, 0.0f, 1.0f});
		viewport.viewSetLookAt(camera);
		viewport.projectionSetPerspective(45.0f, aspectRatio, 0.1f, 100.0f);
		viewport.bindViewportTransform();

		glDrawArrays(GL_TRIANGLES, 0, 36);	

		glBindVertexArray(UNBIND_VAO);

		glfwSwapBuffers(window); // Back < -- > Front
		glfwPollEvents();

		// After All Processing & Rendering Update Previous Values -> Render Time, MousePos...

		float currentTime = glfwGetTime();
		deltaTime = currentTime - prevFrameTime;
		prevFrameTime = currentTime;
	}

	glfwTerminate();
	return 0;
}
