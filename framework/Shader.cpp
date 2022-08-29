#include "Shader.h"

namespace swifterGL {
	std::string read_shader_code(std::string path) {
		std::string code_content;

		std::ifstream input_stream{ path };
		input_stream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			while (!input_stream.eof()) {
				std::string s;
				std::getline(input_stream, s);
				code_content.append(s + "\n");
			}
		}
		catch (std::ifstream::failure e)
		{
			fprintf(stderr, "Reading Shader file: %s failed!\n", path.c_str());
			exit(1);
		}

		return code_content;
	}

	Shader::Shader(ShaderType t, std::string new_code_path) :my_type(t), code_path(new_code_path), ID{}{}
	Shader::~Shader() { glDeleteShader(ID); }
	ShaderType Shader::get_shader_type() { return my_type; }

	const std::string& Shader::get_pathname() { return code_path; }

	GLuint Shader::get_shader_id() { return ID; }

	void Shader::compile(std::string code_content) {
		switch (my_type)
		{
		case swifterGL::ShaderType::VS:
			ID = glCreateShader(GL_VERTEX_SHADER);
			break;
		case swifterGL::ShaderType::TCS:
			ID = glCreateShader(GL_TESS_CONTROL_SHADER);
			break;
		case swifterGL::ShaderType::TES:
			ID = glCreateShader(GL_TESS_EVALUATION_SHADER);
			break;
		case swifterGL::ShaderType::GS:
			ID = glCreateShader(GL_GEOMETRY_SHADER);
			break;
		case swifterGL::ShaderType::FS:
			ID = glCreateShader(GL_FRAGMENT_SHADER);
			break;
		case swifterGL::ShaderType::CS:
			ID = glCreateShader(GL_COMPUTE_SHADER);
			break;
		default:
			break;
		}
		
		const GLchar* p_v = code_content.c_str();
		glShaderSource(ID, 1, &p_v, NULL);
		glCompileShader(ID);
	}


}