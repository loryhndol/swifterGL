#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstdio>
#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#include "VAOGuard.h"

namespace swifterGL {

	constexpr int kWindowWidth = 640;
	constexpr int kWindowHeight = 480;
	constexpr int kMajorVersion = 4;
	constexpr int kMinorVersion = 5;

	class Application {
	public:
		explicit Application(std::string new_title="OpenGL Application");
		virtual ~Application() {}

		virtual void render(double current_time) = 0;
		void run(std::vector<std::string>& shader_path);

	protected:
		static void register_on_resize(int w, int h);
		static void register_on_key(int key, int scancode, int action, int modes);
		static void register_on_mouse_button(int button, int action, int modes);
		static void register_on_mouse_move(double x, double y);
		static void register_on_mouse_wheel(double x_offset, double y_offset);
		std::string title;

	private:
		int window_width;
		int window_height;
		static void observe_on_resize(GLFWwindow* window, int w, int h);
		static void observe_on_key(GLFWwindow* window, int key, int scancode, int action, int modes);
		static void observe_on_mouse_button(GLFWwindow* window, int button, int action, int modes);
		static void observe_on_mouse_move(GLFWwindow* window, double x, double y);
		static void observe_on_mouse_wheel(GLFWwindow* window, double x_offset, double y_offset);
	};
}