#include "Interpolation.h"

namespace swifterGL {
	void onResize(GLFWwindow* window, int w, int h) {
		glViewport(0, 0, w, h);
	}

	void onKey(GLFWwindow* window, int key, int scancode, int action, int modes) {}
	void onMouseButton(GLFWwindow* window, int button, int action, int modes) {}
	void onMouseMove(GLFWwindow* window, double x, double y) {}
	void onMouseWheel(GLFWwindow* window, double x_offset, double y_offset) {}

	Interpolation::Interpolation(std::string new_title) { set_title(new_title); }

	void Interpolation::render(double current_time) {
		const GLfloat color[] = { 0.0, 0.0, 0.0f, 1.0f };
		glClearBufferfv(GL_COLOR, 0, color);

		glUniform1f(0, 0.5 * sin(current_time * 2) + 0.5);

		glPointSize(20.0f);
		glDrawArrays(GL_POINTS, 0, 2);
		
	}
}