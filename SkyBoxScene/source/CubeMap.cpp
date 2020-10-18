#include "CubeMap.h"
#include <GL/glew.h>
#include <stb/stb_image.h>


CubeMap::CubeMap() 
	:idTexture(NULL)
{

}

CubeMap::~CubeMap()
{
	glDeleteTextures(1, &idTexture);
}

void CubeMap::Bind()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, idTexture);
}

void CubeMap::Unbind()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, NULL);
}


void CubeMap::CreateCubeMap()
{
	glGenTextures(1, &idTexture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, idTexture);

	int width, height, nrComponents;
	for (unsigned int i = 0; i < TexturePaths.size(); i++)
	{
		unsigned char* data = stbi_load(TexturePaths[i], &width, &height, &nrComponents, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			printf("Cubemap texture failed to load at path: %s", TexturePaths[i]);
			stbi_image_free(data);
		}
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

}