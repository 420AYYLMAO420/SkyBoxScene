#include "VertexBuffer.h"
#include <GL/glew.h>


VertexBuffer::VertexBuffer()
{
	glGenBuffers(1, &idVBuffer);
}

VertexBuffer::~VertexBuffer()
{
	//clean up buffer
	glDeleteBuffers(1, &idVBuffer);
}

void VertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, idVBuffer);
}

void VertexBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::SetData(const void* vertices, size_t vertexamount)
{
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * vertexamount, vertices, GL_STATIC_DRAW);
}
