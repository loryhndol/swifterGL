#pragma once

#include "../framework/Application.h"

namespace swifterGL {

	class Interpolation :public Application {
	public:
		explicit Interpolation(std::string new_title);
		~Interpolation() {}

		void render(double current_time) override;
	};
}