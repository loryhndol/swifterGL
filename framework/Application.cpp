#include "Application.h"

namespace swifterGL {
	Application::Application(std::string new_title)
		:title(new_title),
		window_width(swifterGL::kWindowWidth),
		window_height(swifterGL::kWindowHeight)
	{}

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

		glfwSetWindowSizeCallback(window, onResize);
		glfwSetKeyCallback(window, onKey);
		glfwSetMouseButtonCallback(window, onMouseButton);
		glfwSetCursorPosCallback(window, onMouseMove);
		glfwSetScrollCallback(window, onMouseWheel);

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
