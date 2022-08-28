#include "Shader.h"

namespace swifterGL {
	Shader::Shader(const std::vector<std::string>& shader_path) {
		for (int i = 0; i < shader_path.size(); i++) {
			switch (i) {
			case 0:
				fs_pathname = shader_path[i];
				break;
			case 1:
				vs_pathname = shader_path[i];
				break;
			case 2:
				tcs_pathname = shader_path[i];
				break;
			case 3:
				tes_pathname = shader_path[i];
				break;
			case 4:
				gs_pathname = shader_path[i];
				break;
			default:
				break;
			}
		}
	}

	std::string Shader::read_shader_source(const std::string& path) {
		std::string shader_code;
		std::ifstream input_stream{ path };
		input_stream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			while (!input_stream.eof()) {
				std::string s;
				std::getline(input_stream, s);
				shader_code.append(s + "\n");
			}
		}
		catch (std::ifstream::failure e)
		{
			fprintf(stderr, "Reading Shader file: %s failed!\n", path.c_str());
			exit(1);
		}

		return shader_code;
	}

	GLuint Shader::compile_shaders() {
		// 文件 IO
		std::string fragment_shader_source = read_shader_source(fs_pathname);

		std::string vertex_shader_source = read_shader_source(vs_pathname);

		// Optional: Tessellation Control Shader
		GLuint tc_shader{};
		if (tcs_pathname.length() > 0) {
			std::string tc_shader_source = read_shader_source(tcs_pathname);
			const GLchar* p = tc_shader_source.c_str();
			
			tc_shader = glCreateShader(GL_TESS_CONTROL_SHADER);
			glShaderSource(tc_shader, 1, &p, NULL);
			glCompileShader(tc_shader);
		}

		// Optional: Tessellation Evaluation Shader
		GLuint te_shader{};
		if (tes_pathname.length() > 0) {
			
			std::string te_shader_source = read_shader_source(tes_pathname);
			const GLchar* p = te_shader_source.c_str();

			te_shader = glCreateShader(GL_TESS_EVALUATION_SHADER);
			glShaderSource(te_shader, 1, &p, NULL);
			glCompileShader(te_shader);
		}

		// Optional: Geometry Shader
		GLuint geo_shader{};
		if (gs_pathname.length() > 0) {

			std::string geo_shader_source = read_shader_source(gs_pathname);
			const GLchar* p = geo_shader_source.c_str();

			geo_shader = glCreateShader(GL_GEOMETRY_SHADER);
			glShaderSource(geo_shader, 1, &p, NULL);
			glCompileShader(geo_shader);
		}

		// 创建并编译着色器，创建程序来链接不同的着色器
		GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		const GLchar* p_v = vertex_shader_source.c_str();
		glShaderSource(vertex_shader, 1, &p_v, NULL);
		glCompileShader(vertex_shader);

		GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		const GLchar* p_f = fragment_shader_source.c_str();
		glShaderSource(fragment_shader, 1, &p_f, NULL);
		glCompileShader(fragment_shader);

		GLuint program = glCreateProgram();
		glAttachShader(program, vertex_shader);
		if (tcs_pathname.length() > 0)
			glAttachShader(program, tc_shader);
		if (tes_pathname.length() > 0)
			glAttachShader(program, te_shader);
		if (gs_pathname.length() > 0)
			glAttachShader(program, geo_shader);
		glAttachShader(program, fragment_shader);
		glLinkProgram(program);

		glDeleteShader(vertex_shader);
		glDeleteShader(tc_shader);
		glDeleteShader(te_shader);
		glDeleteShader(geo_shader);
		glDeleteShader(fragment_shader);

		return program;
	};

}