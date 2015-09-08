#include <functional>
#include <iostream>

class View {

public:
	void onClick(int x, int y)
	{
		std::cout << "X : " << x << ", Y : " << y << std::endl;
	}
};

// 定义function类型, 三个参数
std::function<void(View*, int, int)> clickCallback;

//
int std_function_test(void* noUse)
{
	View button;
	// 指向成员函数
	clickCallback = &View::onClick;
	// 进行调用
	clickCallback(&button, 10, 123);
	return 0;
}