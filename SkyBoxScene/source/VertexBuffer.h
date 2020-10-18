#pragma once

class VertexBuffer {
public:
	VertexBuffer();
	~VertexBuffer();

	void Bind();
	void Unbind();

	void SetData(const void* vertices, size_t vertexamount);

private:
	unsigned int idVBuffer;
};