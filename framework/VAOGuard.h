#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstdio>
#include <cstdlib>
#include <string>
#include <fstream>
#include <vector>
#include "Shader.h"

namespace swifterGL {
	class VAOGuard {
	public:
		explicit VAOGuard(const std::vector<std::string>& shader_path);
		~VAOGuard();

		VAOGuard(const VAOGuard&) = delete;
		VAOGuard& operator=(VAOGuard&) = delete;

	private:
		GLuint rendering_program;
		GLuint VAO; // vertex_array_object
	};
}


