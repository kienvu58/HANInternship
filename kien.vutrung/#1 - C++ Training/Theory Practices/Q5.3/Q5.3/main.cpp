#include <iostream>

int main()
{
	int* p = new int[10];
	
	for (int i = 0; i < 10; i++)
	{
		*(p + i) = i;
	}
	int* p1 = p + 2;
	delete p;
	std::cout << *p1 << std::endl;
	system("pause");
	return 0;
}