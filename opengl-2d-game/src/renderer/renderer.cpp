#include "pch.h"

#include <globals/defs.h>
#include "Renderer.h"
#include <utils/logger.h>

namespace Renderer {
	void OpenGL::frame_buffer_size_callback(GLFWwindow* context, int f_width, int f_height) {
		glViewport(0, 0, f_width, f_height);
	}

	OpenGL::OpenGL(const char* Title, GLuint Width, GLuint Height) : title(Title), width(Width), height(Height) {
		this->window_context = nullptr;
	}

	OpenGL::~OpenGL()
	{
	}

	bool OpenGL::InitializeOpenGL() {
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_RESIZABLE, TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		this->window_context = glfwCreateWindow(this->width, this->height, this->title, nullptr, nullptr);
		if (this->window_context == nullptr) {
			LOGGER::Error("Renderer", "Failed to create Rendering window ", "[Title : ", this->title, "]" " [Width : ", this->width, "]" " [Height : ", this->height, "]");
			return false;
		}

		glfwMakeContextCurrent(this->window_context);
	}

	bool OpenGL::InitializeGLAD() {
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			LOGGER::Error("Renderer", "Failed to intitailize GLAD", " [Title : ", this->title, "]" " [Width : ", this->width, "]" " [Height : ", this->height, "]");
			glfwTerminate();
			return false;
		}

		return true;
	}

	void OpenGL::SetupViewport() {
		glfwSetFramebufferSizeCallback(this->window_context, frame_buffer_size_callback);
	}

	void OpenGL::ProcessBasicInputs() {
		if (this->GetKey(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(this->window_context, true);
			LOGGER::Information("Renderer Shutdown Exit Key (", GLFW_KEY_ESCAPE, ") Pressed");
		}

		if (this->GetKey(GLFW_KEY_F11) == GLFW_PRESS) {

		}
	}

	void OpenGL::SetupWindowStyles(Color window_color)
	{
		glClearColor(window_color.x, window_color.y, window_color.z, window_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGL::SwapAndPoll() {
		glfwSwapBuffers(this->window_context);
		glfwPollEvents();
	}

	void OpenGL::Shutdown() {
		glfwTerminate();
		LOGGER::Information("Renderer", "Renderer Shutdown [Title ", this->title, "] [ Width ", this->width, "] [ Height ", this->height, "]");
	}

	void OpenGL::UpdateFramebufferSize() {
		int newWidth, newHeight;
		glfwGetFramebufferSize(this->window_context, &newWidth, &newHeight);
		this->width = newWidth;
		this->height = newHeight;
	}
}


