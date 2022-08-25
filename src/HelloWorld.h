#pragma once
#include "../framework/framework.h"
#include <cmath>

class HelloWorld : public swifterGL::Application {
public:
	HelloWorld();
	~HelloWorld();

	void render(double current_time, swifterGL::VAOGuard& vao_guard) override;
	void set_callbacks() override;

private:
	static void on_resize(GLFWwindow* window, int w, int h);
	static void on_key(GLFWwindow* window, int key, int scancode, int action, int modes);
	static void on_mouse_button(GLFWwindow* window, int button, int action, int modes);
	static void on_mouse_move(GLFWwindow* window, double x, double y);
	static void on_mouse_wheel(GLFWwindow* window, double x_offset, double y_offset);

	void color_change_with_time(double current_time);
	void draw_a_point(swifterGL::VAOGuard& vao_guard);

};