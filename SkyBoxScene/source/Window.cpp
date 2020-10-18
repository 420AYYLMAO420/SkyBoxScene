#include "Window.h"
#include <GLFW/glfw3.h>
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"

unsigned int Window::Width = 0;
unsigned int Window::Height = 0;
int Window::PosX = 0, Window::PosY = 0;
float Window::OffsetX = 0.f, Window::OffsetY = 0.f;
float lastX = 0.f;
float lastY = 0.f;



Window::Window(const char* title, unsigned int width, unsigned int height)
	:Title(title)
{
	Width = width;
	Height = height;
	if (glfwInit() != GLFW_TRUE) printf("Failed to initialize GLFW");
	//suggest to window that the app wants OpenGL 4.3 core
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//create the window and OpenGL context
	pWindow = glfwCreateWindow(Width, Height, Title, nullptr, nullptr);
	PosX = Width / 2;
	PosY = Height / 2;
	lastX = (float)Width / 2.0;
	lastY = (float)Height / 2.0;

	glfwMakeContextCurrent(pWindow);
	//set the resize window callback function
	glfwSetWindowSizeCallback(pWindow, OnResized);
	glfwSetInputMode(pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPos(pWindow, 0, 0);
	glfwSetCursorPosCallback(pWindow, OnMouseEvent);

	////intialize ImGui and create ImGui context
	//PRINT_IF_ELSE(ImGui::CreateContext(), "Created ImGui context", "Failed to create ImGui context");
	//PRINT_IF_ELSE(ImGui_ImplGlfw_InitForOpenGL(pWindow, false), "Intialized ImGui for GLFW", "Failed to initialize ImGui for GLFW");
	//PRINT_IF_ELSE(ImGui_ImplOpenGL3_Init(), "Intialized ImGui for OpenGL", "Failed to initialize ImGui for OpenGL");
	//ImGui::StyleColorsDark();


}

Window::~Window()
{
	//clean up window
	glfwDestroyWindow(pWindow);
	glfwTerminate();
	/*ImGui_ImplGlfw_Shutdown();*/
}

unsigned int Window::HandleEvents()
{
	//retrieve and handle non-keyboard events
	glfwPollEvents();

	//return corresponding macro with key press
	if (glfwGetKey(pWindow, GLFW_KEY_W) == GLFW_PRESS)
		return GLFW_KEY_W;
	if (glfwGetKey(pWindow, GLFW_KEY_S) == GLFW_PRESS)
		return GLFW_KEY_S;
	if (glfwGetKey(pWindow, GLFW_KEY_A) == GLFW_PRESS)
		return GLFW_KEY_A;
	if (glfwGetKey(pWindow, GLFW_KEY_D) == GLFW_PRESS)
		return GLFW_KEY_D;
	if (glfwGetKey(pWindow, GLFW_KEY_Q) == GLFW_PRESS)
		return GLFW_KEY_Q;
	if (glfwGetKey(pWindow, GLFW_KEY_E) == GLFW_PRESS)
		return GLFW_KEY_E;
	if (glfwGetKey(pWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(pWindow, GLFW_TRUE);
		return GLFW_KEY_ESCAPE;
	}
		

	//return null if no key was pressed
	return NULL;
}

//void Window::ProcessImGui(int* InputInt)
//{
//	//start new frame
//	ImGui_ImplOpenGL3_NewFrame();
//	ImGui_ImplGlfw_NewFrame();
//	ImGui::NewFrame();
//	//create window that allows user to input number of cubes
//	ImGui::Begin("Cube Generator");
//	ImGui::InputInt("How many cubes?", InputInt);
//	//prevent user from entering a negative number of cubes
//	if (*InputInt < 0) *InputInt = 0;
//	//end frame and render
//	ImGui::End();
//	ImGui::Render();
//	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
//}

int Window::IsNotClosed()
{
	return !glfwWindowShouldClose(pWindow);
}

void Window::SwapBuffers()
{
	glfwSwapBuffers(pWindow);
}

void Window::OnResized(GLFWwindow* window, int width, int height)
{
	Width = width;
	Height = height;
}



bool firstMouse = true;
void Window::OnMouseEvent(GLFWwindow* window, double xpos, double ypos)
{

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	OffsetX = xoffset;
	OffsetY = yoffset;


}

