#pragma once
#include <vector>

class CubeMap {

public:
	CubeMap();
	~CubeMap();

	void Bind();
	void Unbind();

	void CreateCubeMap();
	std::vector<const char*> TexturePaths;

private:

	unsigned int idTexture;

};