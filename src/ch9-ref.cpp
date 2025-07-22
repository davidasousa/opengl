// OpenGL Includes
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// General Includes
#include <iostream>
#include <cmath>

// Including Custom Classes
#include "classes/classHeaders.h"

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

void 
processInput(GLFWwindow *window) {
	// Esc Triggers Window Close
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
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
	GLFWwindow* window = glfwCreateWindow(800, 600, "MyWindow", NULL, NULL);
	if(window == NULL) {
		std::cout << "Failed To Create GLFW Window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Loading Glad
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	float windowX = 800.0f, windowY = 600.0f;
	float aspectRatio = windowX / windowY;
	glViewport(0, 0, windowX, windowY);
	glEnable(GL_DEPTH_TEST); // Z Depth Conditional Rendering

	// Creating VAO
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	// Bind VAO
	glBindVertexArray(VAO);

	vertexBufferObject vbo;
	vbo.bindArrayBuf();
	vbo.bufferVertexAttrs(verticies, GL_STATIC_DRAW);
	vbo.configVertexAttr(0, 3, 5, 0);
	vbo.configVertexAttr(1, 2, 5, 3);

	shaderProgramHandler shaderProgram(vertexShaderSource, fragmentShaderSource);
	textureHandler shaderProgramTextures(shaderProgram.getShaderProgramId());
	viewportHandler viewportTransformations(shaderProgram.getShaderProgramId());	

	shaderProgramTextures.loadConfigTexture("src/recourses/container.jpg");
	shaderProgramTextures.loadConfigTexture("src/recourses/awesomeface.png");
	shaderProgramTextures.bindTextureUnits();
	
	// Continuous Render Window
	while(!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProgramTextures.bindTextures();

		viewportTransformations.modelMatRotate((float)glfwGetTime() * 50.0f, (tiltVector){0.5f, 1.0f, 0.0f});
		viewportTransformations.viewShiftCamera((shiftVector){0.0f, 0.0f, -3.0f});
		viewportTransformations.projectionSetPerspective(45.0f, aspectRatio, 0.1f, 100.0f);
		viewportTransformations.bindViewportTransform();

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);	
		glBindVertexArray(UNBIND_VAO);

		glfwSwapBuffers(window); // Back < -- > Front
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
