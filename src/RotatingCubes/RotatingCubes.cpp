#include "RotatingCubes.h"

namespace swifterGL {
	void onResize(GLFWwindow* window, int w, int h) {
		glViewport(0, 0, w, h);
	}

	void onKey(GLFWwindow* window, int key, int scancode, int action, int modes) {}
	void onMouseButton(GLFWwindow* window, int button, int action, int modes) {}
	void onMouseMove(GLFWwindow* window, double x, double y) {}
	void onMouseWheel(GLFWwindow* window, double x_offset, double y_offset) {}

	RotatingCubes::RotatingCubes(std::string new_title) { set_title(new_title); }

	void RotatingCubes::render(double current_time) {
		// 用顶点数组对象设置立方体的结构
		GLuint buffer;
		static const GLfloat vertex_positions[] = {
			-0.25f, 0.25f, -0.25f,
			-0.25f, -0.25f, -0.25f,
			0.25f, -0.25f, -0.25f,

			0.25f, -0.25f, -0.25f,
			0.25f, 0.25f, -0.25f,
			-0.25f, 0.25f, -0.25f,

			-0.25f, 0.25f, -0.25f,
			0.25f, 0.25f, -0.25f,
			0.25f, 0.25f, 0.25f,

			0.25f, 0.25f, 0.25f,
			-0.25f, 0.25f, 0.25f,
			-0.25f, 0.25f, -0.25f
		};

		glGenBuffers(1, &buffer);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER,
			sizeof(vertex_positions),
			vertex_positions,
			GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(0);

		// 构建 model-view 矩阵
		float f = (float)current_time * (float)M_PI * 0.1f;
		glm::vec3 base_point{ 0.0f, 0.0f, -4.0f };
		glm::mat4 mv_matrix{ 1.0f };
		glm::vec3 translate_point{ sinf(2.1f * f) * 0.5f, cosf(1.7f * f) * 0.5f,sinf(1.3f * f) * cosf(1.5f * f) * 2.0f };
		mv_matrix = glm::translate(mv_matrix, base_point * translate_point);

		mv_matrix = glm::rotate(mv_matrix, glm::radians((float)current_time*45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		mv_matrix = glm::rotate(mv_matrix, glm::radians((float)current_time * 81.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		
		auto aspect = (float)Application::get_window_width() / (float)Application::get_window_height();

		// 构建投影矩阵
		glm::mat4 proj_matrix = glm::perspective(glm::radians(50.0f), aspect, 0.1f, 1000.0f);

		float dark_green[]{ 0.2f, 0.3f, 0.3f, 1.0f };
		glClearBufferfv(GL_COLOR, 0, dark_green);

		// 激活程序
		Shader vs = Application::get_shader(ShaderType::VS);
		int mv_location = glGetUniformLocation(vs.get_shader_id(), "mv_matrix");
		//glUniformMatrix4fv(mv_)

		
	
	}
}