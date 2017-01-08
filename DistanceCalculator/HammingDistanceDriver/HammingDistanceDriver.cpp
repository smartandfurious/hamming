#include "stdafx.h"

#include "..\HammingDistanceDLL\HammingDistanceDLL.h"

#ifdef _DEBUG
#pragma comment(lib, "HammingDistanceDLL_d")
#else
#pragma comment(lib, "HammingDistanceDLL")
#endif


#define ERROR_TOO_LONG -1 //operand too long
#define ERROR_UNEVEN   -2 //different length of operands 
#define ERROR_SYMBOL   -3 //incorrect symbol in operand
#define ERROR_RUN	   -4 //processing error


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

int main(int argc, char *argv[])
{
	int distanceP;

	if (argc >= 3) // if the number of input parameters is correct
	{
		distanceP = HammingDistanceP(argv[1], argv[2]);
	}
	else // incorrect input parameters 
	{
		distanceP = ERROR_RUN; // assign result the error code 
	}

	std::cout << "HAMMING_DISTANCE: " << std::endl;
	std::cout << distanceP << std::endl; // output result, 
	// this 2nd line is also analyzed by functional test

	if (distanceP < 0)
	{
		switch (distanceP)
		{
		case ERROR_TOO_LONG:
			std::cout << "ERROR: operands too long " << std::endl;
			break;
		case ERROR_UNEVEN:
			std::cout << "ERROR: operands of different length" << std::endl;
			break;
		case ERROR_SYMBOL:
			std::cout << "ERROR: incorrect symbol in operand" << std::endl;
			break;
		case ERROR_RUN:
			std::cout << "ERROR: incorrect number of operands" << std::endl;
			break;
		default:;
		}

		std::cout << std::endl << "Calculate the Hamming distance: " << std::endl;
		std::cout << "HammingDistanceDriver.exe operand1 operand2" << std::endl;
		std::cout << "operands are BINARY blobs" << std::endl;
		std::cout << "Example: HammingDistanceDriver.exe 0111010 1010111" << std::endl << std::endl;
	}

	if (strcmp(argv[argc - 1], "-q")) // quiet mode for functional testing
	{
		std::cout << "Press ENTER to complete" << std::endl;
		getchar();
	}

	return (distanceP < 0); // 0 - successful, 1 - unsuccessful
	 
}
