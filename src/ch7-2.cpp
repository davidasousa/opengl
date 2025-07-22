// OpenGL Includes
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// General Includes
#include <iostream>
#include <cmath>

// Including Texture Loading File
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Defining A Triangle
float vertices[] = {
// positions 				 // colors 				 // texture coords
	 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
	 0.5f,-0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
	-0.5f,-0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
	-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f // top left
};

unsigned int indicies[] = {
	0, 1, 3, 
	1, 2, 3
};

// Basic Vertex Shader
const char* vertexShaderSource = R"GLSL(
	#version 330 core
	layout (location = 0) in vec3 aPos;
	layout (location = 1) in vec3 aColor;
	layout (location = 2) in vec2 aTexCoord;

	out vec3 ourColor;
	out vec2 TexCoord;

	void main() 
	{
		gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
		ourColor = vec3(aColor.x, aColor.y, aColor.z);
		TexCoord = vec2(aTexCoord.x, aTexCoord.y);
	}
)GLSL";

// Fragment Shader
const char* fragmentShaderSource = R"GLSL(
	#version 330 core
	out vec4 FragColor;

	in vec3 ourColor;
	in vec2 TexCoord;

	uniform sampler2D texture1;
	uniform sampler2D texture2;


	void main()
	{
		FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.5);
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
	
	// Creating EBO
	unsigned int EBO;
	glGenBuffers(1, &EBO);

	// Binding EBO (Indicies)
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);
	
	// Define Attribute 0 Reading
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Define Attr 1 -> Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Define Attr 2 -> Texture
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

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
	glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
	glUniform1i(glGetUniformLocation(shaderProgram, "texture2"), 1);

	// Continuous Render Window
	while(!glfwWindowShouldClose(window)) {
		processInput(window);

		// Clearing Screen
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Using & Updating The Shader
		glUseProgram(shaderProgram);

		// Set Active And Bind
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0); // Unbind Current VAO

		// Render & Listen
		glfwSwapBuffers(window); // Back < -- > Front
		glfwPollEvents();
	}

	// Close GLFW
	glfwTerminate();
	return 0;
}
