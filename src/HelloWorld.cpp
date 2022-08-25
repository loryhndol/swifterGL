#include "HelloWorld.h"

HelloWorld::HelloWorld(){
	set_title("Hello world");
}

HelloWorld::~HelloWorld(){}

void HelloWorld::render(double current_time) {
	static const GLfloat red[] = {1.0f, 0.0f, 0.0f, 1.0f};
	glClearBufferfv(GL_COLOR, 0, red);
}

void HelloWorld::set_callbacks() {
	glfwSetWindowSizeCallback(get_window(), on_resize);
	glfwSetKeyCallback(get_window(), on_key);
	glfwSetMouseButtonCallback(get_window(), on_mouse_button);
	glfwSetCursorPosCallback(get_window(), on_mouse_move);
	glfwSetScrollCallback(get_window(), on_mouse_wheel);
}

void HelloWorld::on_resize(GLFWwindow* window, int w, int h) {}
void HelloWorld::on_key(GLFWwindow* window, int key, int scancode,int action, int modes) {}
void HelloWorld::on_mouse_button(GLFWwindow* window, int button, int action, int modes) {}
void HelloWorld::on_mouse_move(GLFWwindow* window, double x, double y) {}
void HelloWorld::on_mouse_wheel(GLFWwindow* window, double x_offset, double y_offset) {}