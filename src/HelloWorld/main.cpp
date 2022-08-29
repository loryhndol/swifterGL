#include "HelloWorld.h" 

int main(int argc, char* argv[]) {
	if (argc != 6) {
		fprintf(stderr, "Usage: %s [FragS] [VertS] [TCS] [TES] [GS]\n", argv[0]);
		exit(1);
	}

	std::unordered_map<swifterGL::ShaderType, std::string> shader_path{
		{swifterGL::ShaderType::FS, argv[1]},
		{swifterGL::ShaderType::VS, argv[2]},
		{swifterGL::ShaderType::TCS, argv[3]},
		{swifterGL::ShaderType::TES, argv[4]},
		{swifterGL::ShaderType::GS, argv[5]}
	};


	swifterGL::HelloWorld app{ "Hello, World" };
	app.run(shader_path);
	return 0;
}