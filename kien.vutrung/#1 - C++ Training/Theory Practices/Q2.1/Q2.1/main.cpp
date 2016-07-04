#include <stdio.h>
#include <iostream>

void calculate(int val)
{
	static int count = 10;
	static int value;
	printf("%d %d\n", value, count++);
	value = val;
}

int main(int n, char** args)
{
	int i = 1, j = 2;
	calculate(i);
	calculate(j);
	system("pause");
}