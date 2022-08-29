#include "Application.h"

namespace swifterGL {
	Application::Application(std::string new_title)
		:title(new_title),
		window_width(swifterGL::kWindowWidth),
		window_height(swifterGL::kWindowHeight)
	{}

	void Application::observe_on_resize(GLFWwindow* window, int w, int h) {
		register_on_resize(w, h);
	}
	void Application::observe_on_key(GLFWwindow* window, int key, int scancode, int action, int modes) {
		register_on_key(key, scancode, action, modes);
	}
	void Application::observe_on_mouse_button(GLFWwindow* window, int button, int action, int modes) {
		register_on_mouse_button(button, action, modes);
	}
	void Application::observe_on_mouse_move(GLFWwindow* window, double x, double y) {
		register_on_mouse_move(x, y);
	}
	void Application::observe_on_mouse_wheel(GLFWwindow* window, double x_offset, double y_offset) {
		register_on_mouse_wheel(x_offset, y_offset);
	}

	void Application::run(std::vector<std::string>& shader_path) {
		bool running = true;

		if (!glfwInit()) {
			fprintf(stderr, "Failed to initialize GLFW\n");
			exit(1);
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, swifterGL::kMajorVersion);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, swifterGL::kMinorVersion);

		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		GLFWwindow* window = glfwCreateWindow(window_width, window_height, title.c_str(), NULL, NULL);
		if (!window) {
			fprintf(stderr, "Failed to create GLFW window\n");
			glfwTerminate();
			exit(1);
		}

		glfwMakeContextCurrent(window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			fprintf(stderr, "Failed to initialize GLAD\n");
			exit(1);
		}

		glfwSetWindowSizeCallback(window, observe_on_resize);
		glfwSetKeyCallback(window, observe_on_key);
		glfwSetMouseButtonCallback(window, observe_on_mouse_button);
		glfwSetCursorPosCallback(window, observe_on_mouse_move);
		glfwSetScrollCallback(window, observe_on_mouse_wheel);

#ifdef _DEBUG
		fprintf(stderr, "VENDOR: %s\n", (char*)glGetString(GL_VENDOR));
		fprintf(stderr, "VERSION: %s\n", (char*)glGetString(GL_VERSION));
		fprintf(stderr, "RENDERER: %s\n", (char*)glGetString(GL_RENDERER));
#endif 

		VAOGuard vao_guard(shader_path);

		while (running) {


			render(glfwGetTime());

			glfwSwapBuffers(window);
			glfwPollEvents();

			if (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_RELEASE) {
				running = false;
			}

			if (glfwWindowShouldClose(window)) {
				running = false;
			}

		}

		glfwDestroyWindow(window);
		glfwTerminate();
	}
}
