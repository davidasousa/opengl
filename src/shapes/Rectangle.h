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
private:
	static std::vector<float> verticies;
	static std::vector<attrVec> verticiesFormat;

public:
	static std::vector<float>& getVerticies();
	static std::vector<attrVec>& getVerticiesFormat();

};

#endif
