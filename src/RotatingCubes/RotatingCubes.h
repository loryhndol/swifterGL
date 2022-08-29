#pragma once
#define _USE_MATH_DEFINES
#include "../../framework/Application.h"
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>

namespace swifterGL {
	class RotatingCubes :public Application {
	public:
		explicit RotatingCubes(std::string new_title);
		~RotatingCubes() {}

		void render(double current_time) override;
	};
}