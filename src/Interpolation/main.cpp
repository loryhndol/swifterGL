#include "Interpolation.h"

int main(int argc, char* argv[]) {
	if (argc != 3) {
		fprintf(stderr, "Usage: %s [FragS] [VertS]\n", argv[0]);
		exit(1);
	}

	std::unordered_map<swifterGL::ShaderType, std::string> shader_path{
		{swifterGL::ShaderType::FS, argv[1]},
		{swifterGL::ShaderType::VS, argv[2]}
	};


	swifterGL::Interpolation app{ "Quadratic Bezier" };
	app.run(shader_path);
	return 0;
}