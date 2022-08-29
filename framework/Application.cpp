#include "Application.h"

namespace swifterGL {
	Application::Application(std::string new_title)
		:title(new_title),
		window_width(swifterGL::kWindowWidth),
		window_height(swifterGL::kWindowHeight)
	{}

	int Application::get_window_width() { return window_width; }
	int Application::get_window_height() { return window_height; }
	void Application::set_title(std::string new_title) { title = new_title; }

	const Shader& Application::get_shader(ShaderType t) {
		for (auto& i : shaders) {
			if (i.get_shader_type() == t) {
				return i;
			}
		}
		return Shader(ShaderType::NIL, "");
	}

	void Application::run(std::unordered_map<ShaderType,std::string>& shader_path) {
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


		for (auto & i : shader_path) {
			shaders.emplace_back( i.first, i.second );
		}


		for (auto &shader : shaders) {
			shader.compile(swifterGL::read_shader_code(shader.get_pathname()));
		}

		GLuint program = glCreateProgram();
		
		for (auto & shader : shaders) {
			glAttachShader(program, shader.get_shader_id());
		}
		
		glLinkProgram(program);

		GLuint VAO;
		glCreateVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		glUseProgram(program);

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

		glDeleteVertexArrays(1, &VAO);
		glDeleteProgram(program);
		glDeleteVertexArrays(1, &VAO);

		glfwDestroyWindow(window);
		glfwTerminate();
	}
}
