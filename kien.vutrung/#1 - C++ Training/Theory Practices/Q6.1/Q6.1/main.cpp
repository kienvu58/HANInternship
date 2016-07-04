#include <iostream>
#include <stdio.h>

void clone(char *input, char *output)
{
	int i = 0;
	while (char next = *(input + i))
	{
		if (next == '\0')
		{
			break;
		}
		*(output + i) = next;
		i++;
	}
	*(output + i) = '\0';
}

int main()
{
	char* input = "This is my happy face.";
	int i = 0;
	while (char next = *(input + i))
	{
		if (next == '\0')
		{
			break;
		}
		i++;
	}
	char* output = new char[i];
	clone(input, output);
	printf("%s\n", output);
	system("pause");
	return 0;
}