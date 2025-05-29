#pragma once
#include <globals/defs.h>
#include <utils/color.h>

namespace Renderer {

	class OpenGL {
	private:
		const char* title;
		GLuint width;
		GLuint height;

		float time = 0.0f;
		float last_frame = 0.0f;
		float delta_time = 0.0f;

		GLFWwindow* window_context;

		static void frame_buffer_size_callback(GLFWwindow* context, int width, int height);
	public:
		OpenGL(const char* Title, GLuint Width, GLuint Height);
		~OpenGL();

		bool InitializeOpenGL();
		bool InitializeGLAD();
		void SetupViewport();

		void ProcessBasicInputs();
		void SetupWindowStyles(Color window_color);
		void SwapAndPoll();
		void Shutdown();
		void UpdateFramebufferSize();

		bool IsRendererRunning() {
			return !glfwWindowShouldClose(this->window_context);
		}

		void EnableVSync(bool val) {
			glfwSwapInterval(val);
		}

		void EnableAlphaChannel(bool val) {
			if (val) {
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			}
		}

		void Tick() {
			this->time = glfwGetTime();
			this->delta_time = glfwGetTime() - this->last_frame;
			this->last_frame = glfwGetTime();
		}

	public: // Getters
		GLFWwindow*& GetWindowContext() {
			return this->window_context;
		}

		GLuint& GetWidth() {
			return this->width;
		}

		GLuint& GetHeight() {
			return this->height;
		}

		const char* GetTitle() {
			return this->title;
		}

		int GetKey(int Key) {
			return glfwGetKey(this->window_context, Key);
		}

		float& GetTime() {
			return this->time;
		}

		float& GetDeltaTime() {
			return this->delta_time;
		}
		
	public: // Setters
		void SetName(const char* name) {
			this->title = name;
		}
	};

}