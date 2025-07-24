#ifndef VERTEX_BUFFER_OBJECT_H
#define VERTEX_BUFFER_OBJECT_H

// OPENGL
#include <glad/glad.h>

// STL
#include <vector>

class 
VertexBufferObject {
private:
	unsigned int vbo;

public:
	VertexBufferObject();
	unsigned int getVertexBufId();

	void bindArrayBuf();
	bool bufferVertexAttrs(std::vector<float>& verticies, GLenum usage);
	bool configVertexAttr(int attrPos, int attrWidth, int attrStride, int attrOffset);
};

#endif
