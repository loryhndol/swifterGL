#include "framework.h"

namespace swifterGL {
	Application::Application()
		:title("OpenGL Application"),
		window_width(kWindowWidth),
		window_height(kWindowHeight),
		major_version(4),
		minor_version(5),
		window(nullptr)
	{};

	void Application::init() {

	};

	void Application::run(const char* fs_path, const char* vs_path) {
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
		VAOGuard vao_guard(fs_path, vs_path);

		while (running) {
			render(glfwGetTime(), vao_guard);

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
	};

	GLuint compile_shaders(const std::string& fs_pathname, const std::string& vs_pathname) {
		// 文件 IO
		std::string fragment_shader_input;
		std::ifstream fs_stream{ fs_pathname };
		fs_stream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			while (!fs_stream.eof()) {
				std::string s;
				std::getline(fs_stream, s);
				fragment_shader_input.append(s + "\n");
			}
		}
		catch (std::ifstream::failure e)
		{
			fprintf(stderr, "Reading Fragment Shader file failed!\n");
			exit(1);
		}

		const char* fragment_shader_source = fragment_shader_input.c_str();

		std::string vertex_shader_input;
		std::ifstream vs_stream{ vs_pathname };
		vs_stream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			while (!vs_stream.eof()) {
				std::string s;
				std::getline(vs_stream, s);
				vertex_shader_input.append(s + "\n");
			}
		}
		catch (std::ifstream::failure e) {
			fprintf(stderr, "Reading Vertex Shader file failed!\n");
			exit(1);
		}

		const char* vertex_shader_source = vertex_shader_input.c_str();

		// 创建并编译着色器，创建程序来链接不同的着色器
		GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
		glCompileShader(vertex_shader);

		GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
		glCompileShader(fragment_shader);

		GLuint program = glCreateProgram();
		glAttachShader(program, vertex_shader);
		glAttachShader(program, fragment_shader);
		glLinkProgram(program);

		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);

		return program;
	};

	VAOGuard::VAOGuard(const std::string& fs_path, const std::string& vs_path)
		:rendering_program(compile_shaders(fs_path, vs_path))
	{
		glCreateVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
	};

	VAOGuard::~VAOGuard() {
		glDeleteVertexArrays(1, &VAO);
		glDeleteProgram(rendering_program);
		glDeleteVertexArrays(1, &VAO);

	};

	GLuint swifterGL::VAOGuard::get_program()
	{
		return rendering_program;
	}

}
