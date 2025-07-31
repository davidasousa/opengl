#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <vector>

typedef struct { 
	int attrPos; 
	int attrWidth; 
	int attrStride; 
	int attrOffset;
} attrVec;

class 
Rectangle {
public:
	static std::vector<float> verticies;
	static std::vector<attrVec> attrs;

};

#endif
