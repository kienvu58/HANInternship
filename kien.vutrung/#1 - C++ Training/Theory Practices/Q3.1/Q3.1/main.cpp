#include <stdio.h>
#include <iostream>

int main(int n, char** args)
{
	int i = 140;
	char c = i;
	printf("%d\n", c);
	int j = (c + 256) % 256;
	printf("%d\n", j);
	system("pause");
}
