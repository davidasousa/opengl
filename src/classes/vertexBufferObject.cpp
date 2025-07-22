#include "classHeaders.h"

vertexBufferObject::vertexBufferObject() {	
	glGenBuffers(1, &vbo);
}

unsigned int vertexBufferObject::getVertexBufId() {
	return vbo;
}

void vertexBufferObject::bindArrayBuf() {
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

static bool isBound(unsigned int vboId) {
	GLint boundVBO;
	glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &boundVBO);
	if(boundVBO != vboId) { return false; }
	else { return true; }
}

bool vertexBufferObject::bufferVertexAttrs(std::vector<float>& verticies, GLenum usage) {
	if(!isBound(getVertexBufId())) { return false; }

	size_t verticiesSize = sizeof(float) * verticies.size();
	glBufferData(GL_ARRAY_BUFFER, verticiesSize, verticies.data(), usage);
	return true;
}

bool vertexBufferObject::configVertexAttr(int attrPos, int attrWidth, int attrStride, int attrOffset) {
	if(!isBound(getVertexBufId())) { return false; }

	size_t strideSize = sizeof(float) * attrStride;
	size_t offsetSize = sizeof(float) * attrOffset;
	glVertexAttribPointer(attrPos, attrWidth, GL_FLOAT, GL_FALSE, strideSize , (void*)(offsetSize));
	glEnableVertexAttribArray(attrPos);
	return true;
}
