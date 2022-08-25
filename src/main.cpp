#include<memory>

#include "HelloWorld.h" // �����Ҫ���еĳ�����

int main(int argc, char* argv[]) {
	if (argc != 3) {
		fprintf(stderr, "Usage: %s [Vertex Shader Path] [Fragment Shader Path]\n", argv[0]);
		exit(1);
	}

	std::unique_ptr<HelloWorld> app(new HelloWorld);
	app->run(argv[1], argv[2]);
	return 0;
}