#include "framework.h"

namespace swifterGL {
	Application::Application()
		:title(kDefaultTitle),
		window_width(kWindowWidth),
		window_height(kWindowHeight),
		major_version(4),
		minor_version(5),
		window(nullptr)
	{}

	void Application::run(const char* fs_path, const char* vs_path) {
		bool running = true;

		if (!glfwInit()) {
			fprintf(stderr, "Failed to initialize GLFW\n");
			exit(1);
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major_version);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor_version);

		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		window = glfwCreateWindow(window_width, window_height, title.c_str(), NULL, NULL);
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

		set_callbacks();

#ifdef _DEBUG
		fprintf(stderr, "VENDOR: %s\n", (char*)glGetString(GL_VENDOR));
		fprintf(stderr, "VERSION: %s\n", (char*)glGetString(GL_VERSION));
		fprintf(stderr, "RENDERER: %s\n", (char*)glGetString(GL_RENDERER));
#endif 

		VAOGuard vao_guard(fs_path, vs_path);

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
	};
}
