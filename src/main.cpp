#include<memory>

#include "HelloWorld.h" // �����Ҫ���еĳ�����

int main() {
	std::unique_ptr<HelloWorld> app(new HelloWorld);
	app->run();
	return 0;
}