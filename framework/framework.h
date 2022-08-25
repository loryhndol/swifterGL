#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstdio>
#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>


namespace swifterGL {

	constexpr int kWindowWidth = 640;
	constexpr int kWindowHeight = 480;

	class VAOGuard {
	public:
		VAOGuard(const std::string& vs_path, const std::string& fs_path);
		~VAOGuard();

		VAOGuard(const VAOGuard&) = delete;
		VAOGuard& operator=(VAOGuard&) = delete;

		GLuint get_program();

	private:
		GLuint rendering_program;
		GLuint VAO; // vertex_array_object
	};

	class Application {
	public:
		Application();
		virtual ~Application() {}

		virtual void set_callbacks() = 0;
		virtual void render(double current_time, VAOGuard& vao_guard) = 0;

		void init();
		void run(const char* fs_path, const char* vs_path);
		GLFWwindow* get_window() { return window; }
		void set_title(std::string _title) { title = _title; }

	private:
		std::string title;
		int window_width;
		int window_height;
		int major_version;
		int minor_version;

		GLFWwindow* window;

	};

	GLuint compile_shaders(const std::string& vs_pathname, const std::string& fs_pathname);

	
}