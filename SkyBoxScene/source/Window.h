#pragma once

#include <memory>

class Window {

public:
	Window(const char* title, unsigned int width, unsigned int height);
	~Window();

	unsigned int HandleEvents();//handle keyboard events
	//void ProcessImGui(int* InputInt);//handle ImGui processing
	int IsNotClosed();//if user closed the window, return false
	void SwapBuffers();
	unsigned int GetWidth() const { return Width; }
	unsigned int GetHeight() const { return Height; }
	float GetOffsetX() const { return OffsetX; }
	float GetOffsetY() const { return OffsetY; }
private:
	//When window gets resized
	static void OnResized(struct GLFWwindow* window, int width, int height);
	static void OnMouseEvent(GLFWwindow* window, double xpos, double ypos);

	//pointer to the window
	struct GLFWwindow* pWindow;
	//title of window
	const char* Title;
	//dimensions of window
	static int PosX, PosY;
	static unsigned int Width, Height;
	static float OffsetX, OffsetY;

};