#pragma once


#include <vector>



class VertexLayout {
public:
	VertexLayout();
	~VertexLayout();

	void Bind();
	void Unbind();
	//register vertex attributes in OpenGL after initializing Attributes vector
	void CreateAttributes();

private:
	//struct used to define the contents of each vertex attribute
	struct Attribute {
		Attribute( unsigned int numcomponents, size_t bufferoffset)
			:components(numcomponents), comp_offset(bufferoffset) {}
		unsigned int components; //how many components each attribute will have
		size_t comp_offset; //the offset in bytes from the start of each vertex to the start of this attribute
	};

public:
	//vector that stores all objects of type Attribute
	std::vector<Attribute> Attributes;
};