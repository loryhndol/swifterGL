#include "framework.h"

loryhndol::Application::Application()
	:title("OpenGL Application"),
	window_width(kWindowWidth),
	window_height(kWindowHeight),
	major_version(4),
	minor_version(5),
	window(nullptr)
{}

void loryhndol::Application::init() {

}

void loryhndol::Application::run() {
	bool running = true;

	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW\n");
		exit(1);
	}

	init();

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

	// startup();

	while (running){
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

	// shutdown();

	glfwDestroyWindow(window);
	glfwTerminate();
}