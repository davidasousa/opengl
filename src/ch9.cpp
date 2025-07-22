// OpenGL Includes
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// General Includes
#include <iostream>
#include <cmath>

// Including Texture Loading File
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Including Math Library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

float vertices[] = {
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

	// Specify Version Of OpenGL Being Used
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

	// Creating VBO
	unsigned int VBO;
	glGenBuffers(1, &VBO); 

	// Creating Vertex Shader Object
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// Creating Fragment Shader Object
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// Creating A Shader Program
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram); 
	
	// Using Program & Deleting Shaders After Linkage
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Creating VAO
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	// Bind VAO
	glBindVertexArray(VAO);

	// Binding VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // Binding Array Buffer To VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Sending The Triangle Data
	
	// Define Attribute 0 Reading
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Define Attr 1 -> Texture
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Setting Window Position & Dimensions
	glViewport(0, 0, 800, 600);

	// Loading A Texture	
	int width, height, nrChannels;
	// Wooden Container
	unsigned char *data = stbi_load("src/recourses/container.jpg", &width, &height, &nrChannels, 0);

	// Generating The Texture
	unsigned int texture1, texture2;

	glGenTextures(1, &texture1);
	
	// Binding The Texture
	glBindTexture(GL_TEXTURE_2D, texture1);

	// Set the texture wrapping/filtering options (on currently bound texture)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Generating Texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Free Image Data
	stbi_image_free(data);

	// Loading And Setting Smiley Face
	stbi_set_flip_vertically_on_load(true); // Flips Images On Loading
	data = stbi_load("src/recourses/awesomeface.png", &width, &height, &nrChannels, 0);

	glGenTextures(1, &texture2);
	
	// Binding The Texture
	glBindTexture(GL_TEXTURE_2D, texture2);

	// Set the texture wrapping/filtering options (on currently bound texture)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Generating Texture -> Png Has Alpha (opacity) -> Make RGBA
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Free Image Data
	stbi_image_free(data);

	// Bind Shader Prior To Set Texture Units	
	glUseProgram(shaderProgram);
	glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0); // TU1
	glUniform1i(glGetUniformLocation(shaderProgram, "texture2"), 1); // TU2

	// Enable Z Depth Conditional Rendering
	glEnable(GL_DEPTH_TEST);

	// Continuous Render Window
	while(!glfwWindowShouldClose(window)) {
		processInput(window);

		// Clearing Screen
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Using & Updating The Shader
		glUseProgram(shaderProgram);

		// Set Active And Bind
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		// Find Locations Of Transformation Uniforms
		
		glm::mat4 modelMat = glm::mat4(1.0f);
		glm::mat4 viewMat = glm::mat4(1.0f);
		glm::mat4 projectionMat;

		modelMat = glm::rotate(modelMat, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
		viewMat = glm::translate(viewMat, glm::vec3(0.0f, 0.0f, -3.0f));
		projectionMat = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

		int modelMatLoc = glGetUniformLocation(shaderProgram, "modelMat");
		int viewMatLoc = glGetUniformLocation(shaderProgram, "viewMat");
		int projectionMatLoc = glGetUniformLocation(shaderProgram, "projectionMat");

		glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
		glUniformMatrix4fv(viewMatLoc, 1, GL_FALSE, glm::value_ptr(viewMat));
		glUniformMatrix4fv(projectionMatLoc, 1, GL_FALSE, glm::value_ptr(projectionMat));

		// Bind Current Vao + Render
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		// Unbind Vao
		glBindVertexArray(0);

		// Render & Listen
		glfwSwapBuffers(window); // Back < -- > Front
		glfwPollEvents();
	}

	// Close GLFW
	glfwTerminate();
	return 0;
}
