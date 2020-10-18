#include "Graphics.h"
#include <GL/glew.h>
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexLayout.h"
#include "Shader.h"
#include "Time.h"
#include "Camera.h"
#define STB_IMAGE_IMPLEMENTATION
#include "CubeMap.h"
#include "Model.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <random>

float cubeVertices[] = {
	// positions          // normals
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};
float skyboxVertices[] = {
	// positions          
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f
};

Graphics::Graphics(unsigned int winWidth, unsigned int winHeight)
	: WindowWidth(winWidth), WindowHeight(winHeight)
{

	if (glewInit() != GLEW_OK) printf("Failed to initialize GLEW");

	glEnable(GL_DEPTH_TEST);

	ObjectShader = std::make_shared<Shader>("shaders/ObjectVert.glsl", "shaders/ObjectFrag.glsl");
	SkyBoxShader = std::make_shared<Shader>("shaders/SkyBoxVert.glsl", "shaders/SkyBoxFrag.glsl");
	HouseShader = std::make_shared<Shader>("shaders/HouseVert.glsl", "shaders/HouseFrag.glsl");
	
	ObjectVAO = std::make_shared<VertexArray>();
	ObjectVBuffer = std::make_shared<VertexBuffer>();
	ObjectVAO->Bind();
	ObjectVBuffer->Bind();
	ObjectVBuffer->SetData(cubeVertices, std::size(cubeVertices));
	ObjectVLayout = std::make_shared<VertexLayout>();
	ObjectVLayout->Attributes.emplace_back(3, 0);
	ObjectVLayout->Attributes.emplace_back(3, 3);
	ObjectVLayout->CreateAttributes();
	
	SkyBoxVAO = std::make_shared<VertexArray>();
	SkyBoxVBuffer = std::make_shared<VertexBuffer>();
	SkyBoxVAO->Bind();
	SkyBoxVBuffer->Bind();
	SkyBoxVBuffer->SetData(skyboxVertices, std::size(skyboxVertices));
	SkyBoxVLayout = std::make_shared<VertexLayout>();
	SkyBoxVLayout->Attributes.emplace_back(3, 0);
	SkyBoxVLayout->CreateAttributes();

	SkyBoxMap = std::make_shared<CubeMap>();
	SkyBoxMap->TexturePaths.push_back("resources/Textures/Cube Maps/Ocean/right.jpg");
	SkyBoxMap->TexturePaths.push_back("resources/Textures/Cube Maps/Ocean/left.jpg");
	SkyBoxMap->TexturePaths.push_back("resources/Textures/Cube Maps/Ocean/top.jpg");
	SkyBoxMap->TexturePaths.push_back("resources/Textures/Cube Maps/Ocean/bottom.jpg");
	SkyBoxMap->TexturePaths.push_back("resources/Textures/Cube Maps/Ocean/front.jpg");
	SkyBoxMap->TexturePaths.push_back("resources/Textures/Cube Maps/Ocean/back.jpg");
	SkyBoxMap->CreateCubeMap();

	//create camera with its position 20.f away from world origin using Z-axis
	CameraObject = std::make_shared<Camera>();

	Timer = std::make_shared<Time>();
	Timer->Start();

	house = std::make_shared<Model>("resources/Models/backpack.obj");

	//set background color to black
	glClearColor(0.f, 0.f, 0.f, 1.f);
	
}

void Graphics::Render(unsigned int key, float xoffset, float yoffset)
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	CameraObject->ProcessKeyboard((CameraDirection)key, Timer->GetDeltaTime());
	CameraObject->ProcessMouseMovement(xoffset, yoffset);

	ObjectShader->Bind();
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = CameraObject->GetViewMatrix();
	glm::mat4 projection = glm::perspective(glm::radians(CameraObject->Zoom), (float)WindowWidth / (float)WindowHeight, 0.1f, 100.0f);
	ObjectShader->SetMat4("model", model);
	ObjectShader->SetMat4("view", view);
	ObjectShader->SetMat4("projection", projection);
	ObjectShader->SetVec3("cameraPos", CameraObject->Position);
	ObjectShader->SetInt("SkyBox", 0);
	// cubes
	ObjectVAO->Bind();
	SkyBoxMap->Bind();
	glDrawArrays(GL_TRIANGLES, 0, 36);
	ObjectVAO->Unbind();

	glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
	SkyBoxShader->Bind();
	view = glm::mat4(glm::mat3(CameraObject->GetViewMatrix())); // remove translation from the view matrix
	SkyBoxShader->SetMat4("view", view);
	SkyBoxShader->SetMat4("projection", projection);
	// skybox cube
	SkyBoxVAO->Bind();
	SkyBoxMap->Bind();
	glDrawArrays(GL_TRIANGLES, 0, 36);
	SkyBoxVAO->Unbind();
	glDepthFunc(GL_LESS); // set depth function back to default

	HouseShader->Bind();
	HouseShader->SetMat4("projection", projection);
	view = CameraObject->GetViewMatrix();
	HouseShader->SetMat4("view", view);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.f, -10.0f)); // translate it down so it's at the center of the scene
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
	HouseShader->SetMat4("model", model);
	house->Draw(HouseShader.get());
	HouseShader->Unbind();
}

void Graphics::Resize(int x, int y, size_t width, size_t height)
{
	//resize viewport
	glViewport(x, y, width, height);
}
