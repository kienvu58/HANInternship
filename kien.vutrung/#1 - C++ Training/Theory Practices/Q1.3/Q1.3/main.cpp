#include <stdio.h>
#include <iostream>

int main(int n, char** args)
{
	printf("Number of Param %d\n", n);
	for (int i = 0; i < n; i ++)
	{
		printf("param[%d] = %s\n", i, args[i]);
	}
	system("pause");
}