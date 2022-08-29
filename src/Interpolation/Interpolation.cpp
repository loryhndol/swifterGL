#include "Interpolation.h"

namespace swifterGL {
	void Application::register_on_resize(int w, int h) {
		glViewport(0, 0, w, h);
	}

	void Application::register_on_key(int key, int scancode, int action, int modes) {}
	void Application::register_on_mouse_button(int button, int action, int modes) {}
	void Application::register_on_mouse_move(double x, double y) {}
	void Application::register_on_mouse_wheel(double x_offset, double y_offset) {}

	Interpolation::Interpolation(std::string new_title) {
		if (new_title != Application::title)
			Application::title = new_title;
	}

	void Interpolation::render(double current_time) {
		const GLfloat color[] = { 0.0, 0.0, 0.0f, 1.0f };
		glClearBufferfv(GL_COLOR, 0, color);

		glUniform1f(0, 0.5 * sin(current_time * 2) + 0.5);

		glPointSize(20.0f);
		glDrawArrays(GL_POINTS, 0, 2);
		
	}
}