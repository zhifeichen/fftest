#include <functional>
#include <iostream>

class View {

public:
	void onClick(int x, int y)
	{
		std::cout << "X : " << x << ", Y : " << y << std::endl;
	}
};

// ����function����, ��������
std::function<void(View*, int, int)> clickCallback;

//
int std_function_test(void* noUse)
{
	View button;
	// ָ���Ա����
	clickCallback = &View::onClick;
	// ���е���
	clickCallback(&button, 10, 123);
	return 0;
}