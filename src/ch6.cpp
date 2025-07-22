// OpenGL Includes
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// General Includes
#include <iostream>
#include <cmath>

// Defining A Triangle
float verticies[] = {
	0.5f,-0.5f, 0.0f,
 -0.5f,-0.5f, 0.0f,
 -0.5f, 0.5f, 0.0f
};

// Basic Vertex Shader
const char* vertexShaderSource = R"GLSL(
	#version 330 core
	layout (location = 0) in vec3 aPos;

	void main() 
	{
		gl_Position = vec4(aPos.x, aPos. y, aPos.z, 1.0);
	}
)GLSL";

// Fragment Shader
const char* fragmentShaderSource = R"GLSL(
	#version 330 core
	out vec4 FragColor;

	uniform vec4 ourColor;

	void main()
	{
		FragColor = ourColor;
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW); // Sending The Triangle Data
	
	// Define Attribute 0 Reading
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Setting Window Position & Dimensions
	glViewport(0, 0, 800, 600);

	// Continuous Render Window
	while(!glfwWindowShouldClose(window)) {
		processInput(window);

		// Clearing Screen
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Chaning Uniform FragmentShader Vec4
		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");

		// Using & Updating The Shader
		glUseProgram(shaderProgram);
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f); // Shade Of Green Oscillates With The Time

		// Rendering Commands
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
