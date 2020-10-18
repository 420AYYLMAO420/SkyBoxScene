#pragma once

#include <vector>

class VertexArray {
public:

	VertexArray();
	~VertexArray();

	void Bind();
	void Unbind();

private:
	unsigned int idVAO;
};