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

std::vector<float> verticies = {
 -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // 36 x 5 {1,2,3} -> VertexCoords {4,5} -> TexCoords
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
 -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
 -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

 -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
 -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
 -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

 -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
 -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
 -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
 -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
 -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
 -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

 -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
 -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
 -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

 -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
 -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
 -0.5f, 0.5f, -0.5f, 0.0f, 1.0f

};

shiftVector cubePositions[] = {
	{  0.0f, 0.0f, 0.0f  },
	{  2.0f, 5.0f,-15.0f },
	{ -1.5f,-2.2f,-2.5f  },
	{ -3.8f,-2.0f,-12.3f },
	{  2.4f,-0.4f, -3.5f },
	{ -1.7f, 3.0f, -7.5f },
	{  1.3f,-2.0f, -2.5f },
	{  1.5f, 2.0f, -2.5f },
	{  1.5f, 0.2f, -1.5f },
	{ -1.3f, 1.0f, -1.5f }
};

// Basic Vertex Shader
const char* vertexShaderSource = R"GLSL(
	#version 330 core
	layout (location = 0) in vec3 aPos;
	layout (location = 1) in vec2 aTexCoord;

	out vec2 TexCoord;

	uniform mat4 modelMat;
	uniform mat4 viewMat;
	uniform mat4 projectionMat;

	void main() 
	{
		gl_Position = projectionMat * viewMat * modelMat * vec4(aPos, 1.0);
		TexCoord = vec2(aTexCoord.x, aTexCoord.y);
	}
)GLSL";

// Fragment Shader
const char* fragmentShaderSource = R"GLSL(
	#version 330 core
	out vec4 FragColor;

	in vec2 TexCoord;

	uniform sampler2D texture1;
	uniform sampler2D texture2;

	void main()
	{
		FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
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
													 
	Camera camera((posVector){0.0f, 0.0f, -3.0f});	

	// Input Handlers	
	MouseHandler mouseHandler(camera, windowX / 2.0f, windowY / 2.0f);
	
	glfwSetCursorPosCallback(window, &mouseHandler.mouseCallback);
	glfwSetWindowUserPointer(window, &mouseHandler);

	// Creating VAO
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	// Bind VAO
	glBindVertexArray(VAO);

	VertexBufferObject vbo;
	vbo.bindArrayBuf();
	vbo.bufferVertexAttrs(verticies, GL_STATIC_DRAW);
	vbo.configVertexAttr(0, 3, 5, 0);
	vbo.configVertexAttr(1, 2, 5, 3);

	ShaderProgram shaderProgram(vertexShaderSource, fragmentShaderSource);
	Texture texture(shaderProgram.getShaderProgram());
	Viewport viewport(shaderProgram.getShaderProgram());	

	texture.loadConfigTexture("src/recourses/container.jpg");
	texture.loadConfigTexture("src/recourses/awesomeface.png");
	texture.bindTextureUnits();

	// Frame Render Managers
	float deltaTime = 0.0f;
	float prevFrameTime = 0.0f;

	// Continuous Render Window
	while(!glfwWindowShouldClose(window)) {
		processInput(window, camera, deltaTime);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		texture.bindTextures();
		
		glBindVertexArray(VAO);

		for(size_t idx = 0; idx < 10; idx++) {
			viewport.modelMatTranslate(cubePositions[idx]);
			viewport.modelMatRotate(glfwGetTime() * 40.0f * idx, (tiltVector){0.5f, 1.0f, 0.75f});

			viewport.viewSetLookAt(camera);

			viewport.projectionSetPerspective(45.0f, aspectRatio, 0.1f, 100.0f);

			viewport.bindViewportTransform();
			glDrawArrays(GL_TRIANGLES, 0, 36);	
		}

		glBindVertexArray(UNBIND_VAO);

		glfwSwapBuffers(window); // Back < -- > Front
		glfwPollEvents();

		// After All Processing & Rendering Update Previous Values -> Render Time, MousePos...

		float currentTime = glfwGetTime();
		deltaTime = currentTime - prevFrameTime;
		prevFrameTime = currentTime;

		std::cout << 1.0f / deltaTime << std::endl << std::flush;
	}

	glfwTerminate();
	return 0;
}
