#include "VertexArray.h"
#include <GL/glew.h>

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &idVAO);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &idVAO);
}

void VertexArray::Bind()
{
	glBindVertexArray(idVAO);
}

void VertexArray::Unbind()
{
	glBindVertexArray(NULL);
}
