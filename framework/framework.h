#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstdio>
#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>

#include "VAOGuard.h"


namespace swifterGL {

	constexpr int kWindowWidth = 640;
	constexpr int kWindowHeight = 480;
	const std::string kDefaultTitle = "OpenGL Application";

	class Application {
	public:
		Application();
		virtual ~Application() {}

		virtual void set_callbacks() = 0;
		virtual void render(double current_time) = 0;

		void run(const char* fs_path, const char* vs_path);
		GLFWwindow* get_window() { return window; }

	protected:
		std::string title;

	private:
		int window_width;
		int window_height;
		int major_version;
		int minor_version;

		GLFWwindow* window;

	};
}