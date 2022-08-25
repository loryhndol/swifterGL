#include "HelloWorld.h"

HelloWorld::HelloWorld(){
	set_title("Hello world");
}

HelloWorld::~HelloWorld(){}

void HelloWorld::color_change_with_time(double current_time) {
	float r = static_cast<float>(sin(current_time)) * 0.5f + 0.5f;
	float g = static_cast<float>(cos(current_time)) * 0.5f + 0.5f;
	const GLfloat color[] = { r, g, 0.0f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, color);
}

void HelloWorld::draw_a_point(swifterGL::VAOGuard& vao_guard) {
	glUseProgram(vao_guard.get_program());

	glPointSize(40.0f);

	glDrawArrays(GL_POINTS, 0, 1);
}

void HelloWorld::render(double current_time, swifterGL::VAOGuard& vao_guard) {
	color_change_with_time(current_time);

	draw_a_point(vao_guard);

}

void HelloWorld::set_callbacks() {
	glfwSetWindowSizeCallback(get_window(), on_resize);
	glfwSetKeyCallback(get_window(), on_key);
	glfwSetMouseButtonCallback(get_window(), on_mouse_button);
	glfwSetCursorPosCallback(get_window(), on_mouse_move);
	glfwSetScrollCallback(get_window(), on_mouse_wheel);
}

void HelloWorld::on_resize(GLFWwindow* window, int w, int h) {
	glViewport(0, 0, w, h);
}
void HelloWorld::on_key(GLFWwindow* window, int key, int scancode,int action, int modes) {}
void HelloWorld::on_mouse_button(GLFWwindow* window, int button, int action, int modes) {}
void HelloWorld::on_mouse_move(GLFWwindow* window, double x, double y) {}
void HelloWorld::on_mouse_wheel(GLFWwindow* window, double x_offset, double y_offset) {}