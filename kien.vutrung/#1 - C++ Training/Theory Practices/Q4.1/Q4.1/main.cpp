#include <iostream>
#include <stdio.h>

int main()
{
	int a[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int b[10] = { 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };
	int c[20];
	int d[20];

	memcpy(c, a, 10 * sizeof(int));
	memcpy(c + 10, b, 10 * sizeof(int));
	for (int i = 0; i < 20; i++)
	{
		printf("%d ", c[i]);
	}
	std::cout << std::endl;	

	for (int i = 0; i < 10; i++)
	{
		d[i] = a[i];
		d[i + 10] = b[i];
	}

	for (int i = 0; i < 20; i++)
	{
		printf("%d ", d[i]);
	}
	std::cout << std::endl;
	system("pause");
}