#include "ColorManager.h"

ColorManager::ColorManager(std::string _shaderColorName, glm::vec3 _color) :
	shaderColorName(_shaderColorName), color(_color) {

}

const char* ColorManager::getName() { return shaderColorName.c_str(); }

glm::vec3 ColorManager::getColor() { return color; }
