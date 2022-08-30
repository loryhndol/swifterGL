#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstdio>
#include <cstdlib>
#include <string>
#include <fstream>
#include <vector>

namespace swifterGL {
	enum class ShaderType { VS, TCS, TES, GS, FS, CS, NIL};
	std::string read_shader_code(std::string path);

	class Shader {
	public:
		Shader(ShaderType t, std::string new_code_path);
		~Shader();

		const std::string& get_pathname();
		GLuint& get_shader_id();
		ShaderType get_shader_type();

		void compile(std::string code_content);

	private:
		ShaderType my_type;
		std::string code_path;
		std::string code_content;
		GLuint ID;
	};
}

