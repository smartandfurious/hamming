#include "stdafx.h"
#include <string.h>
#include <windows.h>
#include <iostream>

int main(int argc, char *argv[])
{
#define MAX_OPERAND_LENGTH 4800

	char testDataFilePath[] = "..\\MATLAB\\hamming_test.txt"; //where test data is stored
	

	// opening the file with test data 
	FILE *dataTest;
	errno_t err = fopen_s(&dataTest, testDataFilePath, "rt");
		if (err != 0) //bad test file
	{
		std::cout << "Data file " << testDataFilePath << " is corrupted " << std::endl;
		Sleep(2000);
		return -1;
	}

	int numOfTestSets = -1;
	fscanf_s(dataTest, "%d", &numOfTestSets);

	if (numOfTestSets <= 0)
	{
		std::cout << "Data file " << testDataFilePath << " is corrupted " << std::endl;
		Sleep(2000);
		return -1;
	}

	char op1[MAX_OPERAND_LENGTH];
	char op2[MAX_OPERAND_LENGTH];
	for (int k = 0; k < numOfTestSets; k++)
	{
		//reading blob size from file 
		int blobSize;
		fscanf_s(dataTest, "%d\n", &blobSize);

		memset(op1, 0, MAX_OPERAND_LENGTH);
		memset(op2, 0, MAX_OPERAND_LENGTH);
		if (blobSize != 0)
		{
			char c;
			//reading 1st operand from file 
			for (int n = 0; n < MAX_OPERAND_LENGTH; n++)
			{
				c = fgetc(dataTest);
				if (c == '\n') break;
				op1[n] = c;
			}
			if (c != '\n')
			{
				std::cout << "Blob is too long" << std::endl;
				continue; //go to next test case
			}
			//reading 2nd operand from file 
			for (int n = 0; n < MAX_OPERAND_LENGTH; n++)
			{
				c = fgetc(dataTest);
				if (c == '\n') break;
				op2[n] = c;
			}
			if (c != '\n')
			{
				std::cout << "Blob is too long" << std::endl;
				continue; //go to next test case
			}
		}

		//reading expected (true) distance from file 
		int expectedDistance;
		fscanf_s(dataTest, "%d\n", &expectedDistance);


		// starting test case
		char commandLine[2 * MAX_OPERAND_LENGTH];
		sprintf_s(commandLine, "HammingDistanceDriver.exe %s %s -q", op1, op2);
		FILE   *pPipe;
		if ((pPipe = _popen(commandLine, "rt")) == NULL) return(-1);

		// reading result from the pipe 
		char   psBuffer[MAX_OPERAND_LENGTH];
		fgets(psBuffer, 255, pPipe); // skipping 1st line
		fgets(psBuffer, 255, pPipe); // 2nd line contains the distance/error code

		//getting actual distance from program output 
		int actualDistance;
		sscanf_s(psBuffer, "%d", &actualDistance);

		while (fgets(psBuffer, 255, pPipe))	{} //readout the rest of output

		if (feof(pPipe)) //close the pipe
		{
			_pclose(pPipe);
		}
		else // display error message
		{
			std::cout << "ERROR: Cannot readout the pipe" << std::endl;
		}

		// logging test data
		std::cout << "Blob size: " << blobSize << " Expected/Result:  " << expectedDistance
			<< "/" << actualDistance;

		// adding test result
		if (expectedDistance == actualDistance) std::cout << " PASSED" << std::endl;
		if (expectedDistance != actualDistance) std::cout << " FAILED" << std::endl;

	}
	fclose(dataTest);

	std::cout << "Press ENTER to complete" << std::endl;
	getchar();

	return 0;

}


