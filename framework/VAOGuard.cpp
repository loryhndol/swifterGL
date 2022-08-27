#include "VAOGuard.h"

namespace swifterGL {
	VAOGuard::VAOGuard(const std::vector<std::string>& shader_path){
		Shader my_shader{ shader_path };
		rendering_program = my_shader.compile_shaders();
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