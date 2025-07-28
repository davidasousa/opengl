#include "VertexBufferObject.h"

VertexBufferObject::VertexBufferObject() {	
	glGenBuffers(1, &vbo);
}

unsigned int 
VertexBufferObject::getVertexBufId() {
	return vbo;
}

void 
VertexBufferObject::bindArrayBuf() {
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

static bool 
isBound(unsigned int vboId) {
	GLint boundVBO;
	glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &boundVBO);
	if(boundVBO != vboId) { return false; }
	return true;
}

bool 
VertexBufferObject::bufferVertexAttrs(std::vector<float>& verticies, GLenum usage) {
	if(!isBound(getVertexBufId())) { return false; }

	size_t verticiesSize = sizeof(float) * verticies.size();
	glBufferData(GL_ARRAY_BUFFER, verticiesSize, verticies.data(), usage);
	return true;
}

bool 
VertexBufferObject::configVertexAttrs(std::vector<attrVec>& attrs) {
	if(!isBound(getVertexBufId())) { return false; }

	for(attrVec attr : attrs) {
		size_t strideSize = sizeof(float) * attr.attrStride;
		size_t offsetSize = sizeof(float) * attr.attrOffset;
		glVertexAttribPointer(attr.attrPos, attr.attrWidth, GL_FLOAT, GL_FALSE, strideSize , (void*)(offsetSize));
		glEnableVertexAttribArray(attr.attrPos);
	}
	return true;
}
