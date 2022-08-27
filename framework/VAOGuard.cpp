#include "VAOGuard.h"

namespace swifterGL {
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
		glUseProgram(rendering_program);
	};

	VAOGuard::~VAOGuard() {
		glDeleteVertexArrays(1, &VAO);
		glDeleteProgram(rendering_program);
		glDeleteVertexArrays(1, &VAO);

	};
}