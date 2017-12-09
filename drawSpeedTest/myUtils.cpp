#include"myUtils.h"
#include<Windows.h>
#include<iostream>

void printFPS()
{
	static long timeStanp = timeGetTime();
	static int fps = 0;

	fps++;
	if (timeGetTime() > timeStanp + 1000)
	{
		timeStanp = timeGetTime();
		std::cout << fps << std::endl;
		fps = 0;
	}
}