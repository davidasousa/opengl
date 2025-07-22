// OpenGL Includes
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// General Includes
#include <iostream>
#include <cmath>

// Defining A Triangle + Colors
float verticies[] = {
	// Points					 // Colors
	0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
 -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
	0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
};

// Basic Vertex Shader 
// Split Up Input Vector Into Points & Colors
const char* vertexShaderSource = R"GLSL(
	#version 330 core
	layout (location = 0) in vec3 aPos;
	layout (location = 1) in vec3 aColor;

	out vec3 ourColor;

	void main() 
	{
		gl_Position = vec4(aPos, 1.0);
		ourColor = aColor;
	}
)GLSL";

// Fragment Shader
const char* fragmentShaderSource = R"GLSL(
	#version 330 core
	in vec3 ourColor;
	
	out vec4 FragColor;

	void main()
	{
		FragColor = vec4(ourColor, 1.0);
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW); // Sending The Triangle Data To VBO

	// Define Attribute 0 Reading -> Points
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Define Attribute 1 Reading -> Colors
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Setting Window Position & Dimensions
	glViewport(0, 0, 800, 600);

	// Continuous Render Window
	while(!glfwWindowShouldClose(window)) {
		processInput(window);

		// Clearing Screen
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Rendering Commands
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0); // Unbind Current VAO

		// Render & Listen
		glfwSwapBuffers(window); // Back < -- > Front
		glfwPollEvents();
	}

	// Close GLFW
	glfwTerminate();
	return 0;
}
