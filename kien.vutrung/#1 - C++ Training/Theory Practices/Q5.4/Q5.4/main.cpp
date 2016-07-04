#include <iostream>
using namespace std;
#define COUNT 10
#define MAX(a, b) ((a) > (b) ? (a):(b))

void main()
{
	int* p = new int[COUNT];
	int a[COUNT];
	for (int i = 0; i < sizeof(a)/sizeof(int); i++)
	{
		a[i] = i;
	}
	for (int i = 0; i < sizeof(a)/sizeof(int); i++)
	{
		p[i] = i;
	}
	for (int i = 0; i < MAX(sizeof(a)/sizeof(int), sizeof(p)); i++)
	{
		printf("%d %d\n", a[i], p[i]);
	}
	system("pause");
}
