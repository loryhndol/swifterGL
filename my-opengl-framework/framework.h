#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstdio>
#include <cstdlib>
#include <string>


namespace loryhndol {

	constexpr int kWindowWidth = 640;
	constexpr int kWindowHeight = 480;

	class Application {
	public:
		Application();
		virtual ~Application() {}

		virtual void set_callbacks() = 0;
		virtual void render(double current_time) = 0;

		void init();
		void run();
		GLFWwindow* get_window() { return window; }
		void set_title(std::string _title) { title = _title; }

	private:
		std::string title;
		int window_width;
		int window_height;
		int major_version;
		int minor_version;

		GLFWwindow* window;

	

	};
}