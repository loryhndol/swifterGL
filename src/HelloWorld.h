#pragma once
#include "../my-opengl-framework/framework.h"

class HelloWorld : public loryhndol::Application {
public:
	HelloWorld();
	~HelloWorld();

	void render(double current_time) override;
	void set_callbacks() override;

private:
	static void on_resize(GLFWwindow* window, int w, int h);
	static void on_key(GLFWwindow* window, int key, int scancode, int action, int modes);
	static void on_mouse_button(GLFWwindow* window, int button, int action, int modes);
	static void on_mouse_move(GLFWwindow* window, double x, double y);
	static void on_mouse_wheel(GLFWwindow* window, double x_offset, double y_offset);
};