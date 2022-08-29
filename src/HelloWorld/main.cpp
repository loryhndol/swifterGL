#include "HelloWorld.h" 

int main(int argc, char* argv[]) {
	if (argc < 3) {
		fprintf(stderr, "Usage: %s [FragS] [VertS] [option: TCS] [option: TES] [option:GS] [option:CompS]\n", argv[0]);
		exit(1);
	}

	std::vector<std::string> shader_path{ argv[1], argv[2] };
	for (int i = 3; i < argc; i++) {
		shader_path.push_back(argv[i]);
	}


	swifterGL::HelloWorld app{ "Hello, World" };
	app.run(shader_path);
	return 0;
}