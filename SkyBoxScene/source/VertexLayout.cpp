#include "VertexLayout.h"
#include <GL/glew.h>

VertexLayout::VertexLayout()
{
}

VertexLayout::~VertexLayout()
{
	Unbind();
}

void VertexLayout::Bind()
{
	//enable all attributes in Attributes vector
	for(int i = 0; i < Attributes.size(); i++)
		glEnableVertexAttribArray(i);
}

void VertexLayout::Unbind()
{
	//disable all attributes in Attributes vector
	for (int i = 0; i < Attributes.size(); i++)
		glDisableVertexAttribArray(i);
}

void VertexLayout::CreateAttributes()
{
	//how many bytes from the start of vertex to the end of vertex
	unsigned int stride = 0;
	//add the size of components in bytes of each attribute to stride
	for (int i = 0; i < Attributes.size(); i++)
	{
		stride += Attributes[i].components * sizeof(float);
	}
	//register each attribute to OpenGL for laying out the input
	for (int i = 0; i < Attributes.size(); i++) {
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, Attributes[i].components, GL_FLOAT, GL_FALSE, stride, 
			(void*)(Attributes[i].comp_offset * sizeof(float)));
	}
	
}
