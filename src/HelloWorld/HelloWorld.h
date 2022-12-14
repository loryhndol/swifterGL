#pragma once
#include "../../framework/Application.h"
#include <cmath>

namespace swifterGL {
	class HelloWorld : public Application {
	public:
		explicit HelloWorld(std::string new_title);
		~HelloWorld();

		void render(double current_time) override;

	private:

		void color_change_with_time(double current_time);

		void draw_a_point();
		void draw_a_triangle(double current_time);
	};
}
