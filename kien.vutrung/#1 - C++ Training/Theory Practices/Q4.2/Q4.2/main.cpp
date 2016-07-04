#include <stdio.h>
#include <iostream>

int main(int n, char** args)
{
	int a[10];
	for (int i = 0; i < 10; i++)
	{
		a[i] = i * 10;
	}
	printf("0x%x 0x%x 0x%x\n", a, *a, &a);
	printf("0x%x 0x%x 0x%x 0x%x\n", (a + 9), *(a + 1), *a + 1, &a + 1);
	system("pause");
}
