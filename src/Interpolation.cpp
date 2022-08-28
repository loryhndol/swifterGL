#include "Interpolation.h"

namespace swifterGL {

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