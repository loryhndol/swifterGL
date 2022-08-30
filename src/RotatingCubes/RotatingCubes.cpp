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

	void RotatingCubes::gen_buffers() {
		// 用顶点数组对象设置立方体的结构
		static const GLfloat vertex_positions[] =
		{
			/*bottom*/
			-0.25f,  0.25f, -0.25f,
			-0.25f, -0.25f, -0.25f,
			 0.25f, -0.25f, -0.25f,

			 0.25f, -0.25f, -0.25f,
			 0.25f,  0.25f, -0.25f,
			-0.25f,  0.25f, -0.25f,

			/*front*/
			 0.25f, -0.25f, -0.25f,
			 0.25f, -0.25f,  0.25f,
			 0.25f,  0.25f, -0.25f,

			 0.25f, -0.25f,  0.25f,
			 0.25f,  0.25f,  0.25f,
			 0.25f,  0.25f, -0.25f,

			 /*top*/
			 0.25f, -0.25f,  0.25f,
			-0.25f, -0.25f,  0.25f,
			 0.25f,  0.25f,  0.25f,

			-0.25f, -0.25f,  0.25f,
			-0.25f,  0.25f,  0.25f,
			 0.25f,  0.25f,  0.25f,

			 /*back*/
			-0.25f, -0.25f,  0.25f,
			-0.25f, -0.25f, -0.25f,
			-0.25f,  0.25f,  0.25f,

			-0.25f, -0.25f, -0.25f,
			-0.25f,  0.25f, -0.25f,
			-0.25f,  0.25f,  0.25f,

			/*left*/
			-0.25f, -0.25f,  0.25f,
			 0.25f, -0.25f,  0.25f,
			 0.25f, -0.25f, -0.25f,

			 0.25f, -0.25f, -0.25f,
			-0.25f, -0.25f, -0.25f,
			-0.25f, -0.25f,  0.25f,

			/*right*/
			-0.25f,  0.25f, -0.25f,
			 0.25f,  0.25f, -0.25f,
			 0.25f,  0.25f,  0.25f,

			 0.25f,  0.25f,  0.25f,
			-0.25f,  0.25f,  0.25f,
			-0.25f,  0.25f, -0.25f
		};

		GLuint& app_buffer = Application::get_buffer();

		glGenBuffers(1, &app_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, app_buffer);
		glBufferData(GL_ARRAY_BUFFER,
			sizeof(vertex_positions),
			vertex_positions,
			GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(0);

		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CW);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
	}

	void RotatingCubes::render(double current_time) {
		float dark_green[]{ 0.2f, 0.3f, 0.3f, 1.0f };
		static const GLfloat one = 1.0f;
		glClearBufferfv(GL_COLOR, 0, dark_green);
		glClearBufferfv(GL_DEPTH, 0, &one);


		Shader vs = Application::get_shader(ShaderType::VS);
		auto aspect = (float)Application::get_window_width() / (float)Application::get_window_height();
		// 构建投影矩阵
		glm::mat4 proj_matrix = glm::perspective(glm::radians(50.0f), aspect, 0.1f, 100.0f);
		glUniformMatrix4fv(1, 1, GL_FALSE, glm::value_ptr(proj_matrix));

		for (int i = 0; i < 24; i++) {
			// 构建 model-view 矩阵
			float f = (float)i + (float)current_time * (float)M_PI * 0.5f;
			glm::vec3 base_point{ 0.0f, (float)i/6-2, -5.0f + (float)i / 6};
			glm::vec3 translate_point{ sinf(2.1f * f) * 0.5f, cosf(1.7f * f) * 0.5f,sinf(1.3f * f) * cosf(1.5f * f) * 2.0f };
			glm::mat4 mv_matrix(1.0f);
			mv_matrix = glm::translate(mv_matrix, base_point);
			mv_matrix = glm::rotate(mv_matrix, glm::radians((float)current_time * 45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			mv_matrix = glm::translate(mv_matrix, translate_point);
			mv_matrix = glm::rotate(mv_matrix, glm::radians((float)current_time * 81.0f), glm::vec3(1.0f, 0.0f, 0.0f));

			// 激活程序
			glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(mv_matrix));

			// 6个面，每个面2个三角形，每个三角形3个顶点，因此一共有36个顶点
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	}
}