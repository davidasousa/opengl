#ifndef COLOR_H
#define COLOR_H

// GLAD Dynamic OpenGL Includes
#include <glad/glad.h>

// Including GLM Math Library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

#include "Types.h"

class
ColorManager {
private:
	std::string shaderColorName; 
	glm::vec3 color;

public:
	ColorManager(std::string _shaderColorName, glm::vec3 _color);
	const char* getName();
	glm::vec3 getColor();

};


#endif
