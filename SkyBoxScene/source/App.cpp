#include "App.h"
#include "Window.h"
#include "Graphics.h"

App::App(const char* title, unsigned int width, unsigned int height)
{
	//make App components
	window = std::make_unique<Window>(title, width, height);
	graphics = std::make_unique<Graphics>(width, height);
}

App::~App() {}

void App::Run()
{
	while (window->IsNotClosed()) {
		//resize the viewport so that it matches with the size of the window
		graphics->Resize(0, 0, window->GetWidth(), window->GetHeight());
		
		//render to back buffer using input from user
		graphics->Render(window->HandleEvents(), window->GetOffsetX(), window->GetOffsetY()); 
		//handle any ImGui processing
		//window->ProcessImGui(&graphics->NumCubes); 
		//swap back and front buffers
		window->SwapBuffers();
	}
}
