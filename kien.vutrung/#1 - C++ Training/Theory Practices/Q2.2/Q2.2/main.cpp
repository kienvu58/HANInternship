#include <iostream>

int aCount = 0;

void a()
{
	std::cout << "a() is called" << std::endl;
	aCount++;
}

void b()
{
	static int bCount = 0;
	std::cout << "b() is called" << std::endl;
	bCount++;
	std::cout << "Times function b is called: " << bCount << std::endl;
}

void c(int& cCount)
{
	std::cout << "c() is called" << std::endl;
	cCount++;
}

int main()
{
	static int cCount = 0;
	a();
	b();
	c(cCount);
	std::cout << "Times function a is called: " << aCount << std::endl;
	std::cout << "Times function c is called: " << cCount << std::endl;
	system("pause");
	return 0;
}
