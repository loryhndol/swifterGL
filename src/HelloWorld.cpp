#include "HelloWorld.h"

namespace swifterGL {
	void onResize(GLFWwindow* window, int w, int h){
		glViewport(0, 0, w, h);
	}
	void onKey(GLFWwindow* window, int key, int scancode, int action, int modes){}
	void onMouseButton(GLFWwindow* window, int button, int action, int modes){}
	void onMouseMove(GLFWwindow* window, double x, double y){}
	void onMouseWheel(GLFWwindow* window, double x_offset, double y_offset){}

	HelloWorld::HelloWorld() {}

	HelloWorld::HelloWorld(std::string _title){
		if(_title != Application::title) 
			Application::title = _title;
	}

	HelloWorld::~HelloWorld() {}

	void HelloWorld::color_change_with_time(double current_time) {
		float r = static_cast<float>(sin(current_time)) * 0.5f + 0.5f;
		float g = static_cast<float>(cos(current_time)) * 0.5f + 0.5f;
		const GLfloat color[] = { r, g, 0.0f, 1.0f };
		glClearBufferfv(GL_COLOR, 0, color);
	}

	void HelloWorld::draw_a_point() {
		glPointSize(40.0f);
		glDrawArrays(GL_POINTS, 0, 1);
	}

	void HelloWorld::draw_a_triangle(double current_time) {
		GLfloat attrib_pos_offset[] = {
		(float)sin(current_time) * 0.5f,
		(float)cos(current_time) * 0.6f,
		0.0f,0.0f };

		glVertexAttrib4fv(0, attrib_pos_offset);

		GLfloat attrib_color[] = {
		(float)cos(current_time) * 0.5f,
		1.0f,
		0.0f,0.0f };

		glVertexAttrib4fv(1, attrib_color);

		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		glPointSize(5.0f);
		glDrawArrays(GL_PATCHES, 0, 3);
	}

	void HelloWorld::render(double current_time) {
		color_change_with_time(current_time);
		draw_a_point();
		//draw_a_triangle(current_time);

	}

}