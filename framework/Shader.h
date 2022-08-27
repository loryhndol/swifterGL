#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstdio>
#include <cstdlib>
#include <string>
#include <fstream>
#include <vector>

namespace swifterGL {
	class Shader {
	public:
		explicit Shader(const std::vector<std::string>& shader_path);
		GLuint compile_shaders();
		std::string read_shader_source(const std::string& path);
	private:
		std::string fs_pathname;
		std::string vs_pathname;
		std::string tcs_pathname;
		std::string tes_pathname;
		std::string gs_pathname;
	};

}