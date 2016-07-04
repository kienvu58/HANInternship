#include <iostream>

void Invert(int input[], int num_elements)
{
	for (int i = 0; i < num_elements/2; i++)
	{
		int temp = input[i];
		input[i] = input[num_elements - i - 1];
		input[num_elements - i - 1] = temp;
	}
}

void Invert(const int input[], int num_elements, int output[])
{
	for (int i = 0; i < num_elements; i++)
	{
		output[i] = input[num_elements - i - 1];
	}
}

int main()
{
	const int num_elements = 5;
	int a[num_elements] = { 1, 2, 3, 4, 5 };
	int b[num_elements] = { 1, 2, 3, 4, 5 };
	int c[num_elements];

	Invert(a, num_elements);
	Invert(b, num_elements, c);
	for (int i = 0; i < num_elements; i++)
	{
		std::cout << a[i] << " ";
	}
	std::cout << std::endl;
	for (int i = 0; i < num_elements; i++)
	{
		std::cout << b[i] << " ";
	}
	std::cout << std::endl;
	for (int i = 0; i < num_elements; i++)
	{
		std::cout << c[i] << " ";
	}
	std::cout << std::endl;
	system("pause");
}