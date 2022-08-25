#include<memory>

#include "HelloWorld.h" // 添加想要运行的程序类

int main() {
	std::unique_ptr<HelloWorld> app(new HelloWorld);
	app->run();
	return 0;
}