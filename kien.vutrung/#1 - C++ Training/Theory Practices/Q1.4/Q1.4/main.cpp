#include <stdio.h>
#include <Windows.h>

int main()
{
	SYSTEMTIME time;
	const int MILLISECONDS_PER_MINUTE = 1000;
	const int FRAME_RATE = 10;
	while (true)
	{
		GetLocalTime(&time);
		printf("%02d:%02d:%02d\n", time.wHour, time.wMinute, time.wSecond);
		Sleep(MILLISECONDS_PER_MINUTE/FRAME_RATE);
	}
	return 0;
}
