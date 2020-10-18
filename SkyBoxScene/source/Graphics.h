#pragma once

#include <memory>

class Graphics {
public:
	Graphics(unsigned int winWidth, unsigned int winHeight);
	~Graphics() {}

	//clear back buffer and draw
	void Render(unsigned int key, float xoffset, float yoffset);
	void Resize(int x, int y, size_t width, size_t height);

private:
	unsigned int WindowWidth, WindowHeight;//dimensions of window

	//components of Graphics
	std::shared_ptr<class VertexArray> SkyBoxVAO;
	std::shared_ptr<class VertexArray> ObjectVAO;
	std::shared_ptr<class VertexBuffer> SkyBoxVBuffer;
	std::shared_ptr<class VertexBuffer> ObjectVBuffer;
	std::shared_ptr<class Shader> ObjectShader;
	std::shared_ptr<class Shader> SkyBoxShader;
	std::shared_ptr<class VertexLayout> ObjectVLayout;
	std::shared_ptr<class VertexLayout> SkyBoxVLayout;
	std::shared_ptr<class Camera> CameraObject;
	std::shared_ptr<class Time> Timer;
	std::shared_ptr<class CubeMap> SkyBoxMap;
	std::shared_ptr<class Shader> HouseShader;
	std::shared_ptr<class Model> house;

};