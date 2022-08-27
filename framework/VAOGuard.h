#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstdio>
#include <cstdlib>
#include <string>
#include <fstream>

namespace swifterGL {

	GLuint compile_shaders(const std::string& vs_pathname, const std::string& fs_pathname);

	class VAOGuard {
	public:
		explicit VAOGuard(const std::string& fs_path, const std::string& vs_path);
		~VAOGuard();

		VAOGuard(const VAOGuard&) = delete;
		VAOGuard& operator=(VAOGuard&) = delete;

	private:
		GLuint rendering_program;
		GLuint VAO; // vertex_array_object
	};
}