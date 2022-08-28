#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstdio>
#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <memory>

#include "VAOGuard.h"


namespace swifterGL {
	constexpr int kWindowWidth = 640;
	constexpr int kWindowHeight = 480;
	constexpr int kMajorVersion = 4;
	constexpr int kMinorVersion = 5;
	const std::string kDefaultTitle = "OpenGL Application";

	void onResize(GLFWwindow* window, int w, int h);
	void onKey(GLFWwindow* window, int key, int scancode, int action, int modes);
	void onMouseButton(GLFWwindow* window, int button, int action, int modes);
	void onMouseMove(GLFWwindow* window, double x, double y);
	void onMouseWheel(GLFWwindow* window, double x_offset, double y_offset);

	class Application {
	public:
		Application();
		virtual ~Application() {}

		virtual void render(double current_time) = 0;
		void run(std::vector<std::string>& shader_path);

	protected:
		std::string title;

	private:
		int window_width;
		int window_height;
	};
}