#include "IndexBuffer.h"
#include <GL/glew.h>


IndexBuffer::IndexBuffer()
{
	glGenBuffers(1, &idIBuffer);
}

IndexBuffer::~IndexBuffer()
{
	//clean up buffer
	glDeleteBuffers(1, &idIBuffer);
}

void IndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idIBuffer);
}

void IndexBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void IndexBuffer::SetData(const void* indices, size_t indexamount)
{
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * indexamount, indices, GL_STATIC_DRAW);
}
