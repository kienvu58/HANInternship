#include <iostream>

void sort(int *arr, int count, int(*order) (int, int));
int CheckBigger(int a, int b) { return a>b; }
int CheckSmaller(int a, int b) { return a<b; }
void swap(int* a, int* b);

int main()
{
	const int count = 5;
	int a[count] = { 4, 3, 1, 2, 5 };
	int b = 5;
	int c = 6;
	swap(&b, &c);
	sort(a, count, CheckBigger);
	for (int i = 0; i < count; i++)
	{
		std::cout << a[i] << std::endl;
	}
	system("pause");
	return 0;
}

void sort(int *arr, int count, int(*order) (int, int))
{
	bool swapped = true;
	while (swapped)
	{
		swapped = false;
		for (int i = 1; i < count; i++)
		{
			if (order(arr[i - 1], arr[i]))
			{
				swap(&arr[i - 1], &arr[i]);
				swapped = true;
			}
		}
		count--;
	}
}

void swap(int * a, int * b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
