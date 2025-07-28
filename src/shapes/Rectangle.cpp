#include "Rectangle.h"

// 36 x 5 {1,2,3} -> VertexCoords {4,5} -> TexCoords
std::vector<float> Rectangle::verticies = { 
 -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 
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

std::vector<attrVec> Rectangle::verticiesFormat = { {0, 3, 5, 0}, {1, 2, 5, 3} };

std::vector<float>& Rectangle::getVerticies() { return std::ref(verticies); }

std::vector<attrVec>& Rectangle::getVerticiesFormat() { return std::ref(verticiesFormat); }
