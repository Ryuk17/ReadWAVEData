#include "ReadWAVE.h"
#include <iostream>

int main()
{
	ReadWAVE test("sample.wav");

	std::cout << test.GetState() << std::endl;

	std::cout << test.GetWaveData(2) << std::endl;

	return 0;
}