// OpenGL Includes
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// General Includes
#include <iostream>
#include <cmath>
#include <vector>

// Including Custom Classes
#include "classes/Types.h"

#include "classes/VertexBufferObject.h"
#include "classes/ShaderProgram.h"
#include "classes/Texture.h"
#include "classes/Camera.h"
#include "classes/Viewport.h"
#include "classes/MouseHandler.h"

#include "shapes/Rectangle.h"

// Basic Vertex Shader
const char* vertexShaderSource = R"GLSL(
	#version 330 core
	layout (location = 0) in vec3 aPos;
	layout (location = 1) in vec3 aNormal;
	layout (location = 2) in vec2 aTexCoords;

	out vec3 FragPos;
	out vec3 Normal;
	out vec2 TexCoords;

	uniform mat4 modelMat;
	uniform mat4 viewMat;
	uniform mat4 projectionMat;

	void main() 
	{
		gl_Position = projectionMat * viewMat * modelMat * vec4(aPos, 1.0);

		FragPos = vec3(modelMat * vec4(aPos, 1.0f)); // Model Matrix Yields The Position Of The Object
		Normal = aNormal;
		TexCoords = aTexCoords;
	}
)GLSL";

// Fragment Shader - Light Source
const char* lightFragmentShaderSource = R"GLSL(
	#version 330 core
	out vec4 FragColor;

	uniform vec3 lightColor;

	void main()
	{
		FragColor = vec4(lightColor, 1.0);
	}
)GLSL";

// Fragment Shader - Object
const char* objectFragmentShaderSource = R"GLSL(
	#version 330 core
	out vec4 FragColor;

	in vec3 FragPos;
	in vec3 Normal;
	in vec2 TexCoords;

	struct Material {
		sampler2D diffuse;
		vec3 specular;
		float shininess;
	};

	struct LightObject {
		vec3 ambient;
		vec3 diffuse;
		vec3 specular;
	};

	uniform Material material;
	uniform LightObject light;

	uniform vec3 lightPos;
	uniform vec3 viewPos;

	// Ambient
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

	// Diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
	
	// Specular
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * (spec * material.specular);

	vec3 result = ambient + diffuse + specular;

	void main()
	{
		FragColor = vec4(result, 1.0);
	}
)GLSL";

const char* fragmentShaders[] = {
	lightFragmentShaderSource,
	objectFragmentShaderSource
};

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

	// Frame Render Managers
	float deltaTime = 0.0f;
	float prevFrameTime = 0.0f;

	float aspectRatio = windowX / windowY;
	glViewport(0, 0, windowX, windowY);
	glEnable(GL_DEPTH_TEST); // Z Depth Conditional Rendering
													 
	Camera camera((posVector){0.0f, 0.0f, 3.0f});	

	// Input Handlers	
	MouseHandler mouseHandler(camera, windowX / 2.0f, windowY / 2.0f);
	
	glfwSetCursorPosCallback(window, &mouseHandler.dragCallback);
	glfwSetScrollCallback(window, &mouseHandler.scrollCallback);
	glfwSetWindowUserPointer(window, &mouseHandler);

	// Creating Object VAO
	unsigned int vao;
	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);

	VertexBufferObject vbo;
	vbo.bindArrayBuf();
	vbo.bufferVertexAttrs(std::ref(Rectangle::verticies), GL_STATIC_DRAW);
	vbo.configVertexAttrs(Rectangle::attrs);

	glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 1.0f);

	ShaderProgram objProgram1(vertexShaderSource, lightFragmentShaderSource);
	objProgram1.addUniform("lightColor", lightColor);

	ShaderProgram objProgram2(vertexShaderSource, objectFragmentShaderSource);
	objProgram2.addUniform("lightPos", lightPos);

	objProgram2.addUniform("light.ambient", glm::vec3(1.0f, 1.0f, 1.0f));
	objProgram2.addUniform("light.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
	objProgram2.addUniform("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));

	objProgram2.addUniform("material.diffuse", 0);
	objProgram2.addUniform("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
	objProgram2.addUniform("material.shininess", 32.0f);

	Texture texture(objProgram2.getShaderProgram(), "material.diffuse");
	texture.loadTexture("src/recourses/container.jpg");

	Viewport viewport;

	// Continuous Render Window
	while(!glfwWindowShouldClose(window)) {
		processInput(window, camera, deltaTime);

		glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindVertexArray(vao);

		// Light Source 	
		glUseProgram(objProgram1.getShaderProgram());
		objProgram1.bindUniforms();

		viewport.modelMatTranslate((shiftVector){0.0f, 0.0f, 1.0f});
		viewport.viewSetLookAt(camera); // Get View Before Rendering Object 
		viewport.projectionSetPerspective(45.0f, aspectRatio, 0.1f, 100.0f);

		viewport.bindViewportTransform(objProgram1.getShaderProgram());
		glDrawArrays(GL_TRIANGLES, 0, 36);	

		// Object
		glUseProgram(objProgram2.getShaderProgram());

		objProgram2.addUniform("viewPos", camera.getCamPos());
		objProgram2.bindUniforms();

		viewport.modelMatTranslate((shiftVector){2.0f, 1.0f, -1.0f});
		viewport.viewSetLookAt(camera);
		viewport.projectionSetPerspective(45.0f, aspectRatio, 0.1f, 100.0f);

		viewport.bindViewportTransform(objProgram2.getShaderProgram());

		texture.bindTextureUnit();
		texture.bindTexture();
		glDrawArrays(GL_TRIANGLES, 0, 36);	

		// Unbind
		glBindVertexArray(UNBIND_VAO);

		// Back < -- > Front
		glfwSwapBuffers(window); 
		glfwPollEvents();

		// After All Processing & Rendering Update Previous Values -> Render Time, MousePos...
		float currentTime = glfwGetTime();
		deltaTime = currentTime - prevFrameTime;
		prevFrameTime = currentTime;
	}

	glfwTerminate();
	return 0;
}
