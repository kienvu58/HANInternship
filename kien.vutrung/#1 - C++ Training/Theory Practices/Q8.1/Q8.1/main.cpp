#include <iostream>
#include <stdio.h>

void SayHello()
{
	printf("Hello world\n");
}

void SayHello(char* str)
{
	printf("Hello world, %s\n", str);
}

void SayHello(char* str, bool uppercase=false)
{
	if (uppercase)
	{
		int i = 0;
		while (str[i])
		{
			str[i] = toupper(str[i]);
			i++;
		}
	} 
	printf("Hello world, %s\n", str);
}

int main()
{
	char str[] = "Kien";
	SayHello(str, true);
	system("pause");
	return 0;
}