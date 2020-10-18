#pragma once

class IndexBuffer {
public:
	IndexBuffer();
	~IndexBuffer();

	void Bind();
	void Unbind();

	void SetData(const void* indices, size_t indexamount);

private:
	unsigned int idIBuffer;
};