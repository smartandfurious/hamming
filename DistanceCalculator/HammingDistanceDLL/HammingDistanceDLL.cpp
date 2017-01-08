#include "stdafx.h"
#include "HammingDistanceDLL.h"


#define MAX_OPERAND_LENGTH 4000  //max length of one operand
#define ASCII_ZERO 48 // ASCII code of 0
#define ASCII_ONE 49 // ASCII code of 1
#define EOS 0 // string terminator 


#define ERROR_TOO_LONG -1 //operand too long
#define ERROR_UNEVEN   -2 //different length of operands 
#define ERROR_SYMBOL   -3 //incorrect symbol in operand
#define ERROR_RUN	   -4 //processing error



__declspec(dllexport) int ascii2num(const char symbolIn, char &symbolOut)
{
	switch (symbolIn)
	{
	case ASCII_ZERO:
		symbolOut = 0;
		break;
	case ASCII_ONE:
		symbolOut = 1;
		break;
	default:
		return ERROR_SYMBOL; // unacceptable symbol
	}

	return 0; // no conversion errors
}



__declspec(dllexport) int HammingDistanceP(const char *operand1str, const char *operand2str)
{

	int hammingDistance = 0;

	for (int k = 0; k <= MAX_OPERAND_LENGTH; k++) // = to handle ending zero
	{
		if ((EOS == operand1str[k]) && (EOS == operand2str[k])) //end of both operands reached
		{
			return hammingDistance;
		}

		if ((EOS == operand1str[k]) != (EOS == operand2str[k]))
		{
			return ERROR_UNEVEN; //unequal length of operands
		}

		char operand1num;
		char operand2num;

		// convert symbols to numbers
		if (ascii2num(operand1str[k], operand1num)) return ERROR_SYMBOL;
		if (ascii2num(operand2str[k], operand2num)) return ERROR_SYMBOL;

		hammingDistance += operand1num ^ operand2num; // increment the distance
	}

	return ERROR_TOO_LONG; //strings exceed max length
}


__declspec(dllexport) int HammingDistanceV(std::vector<char> operand1v, std::vector<char> operand2v)
{
	int hammingDistance = 0;

	if (operand1v.size() != operand2v.size()) return ERROR_UNEVEN; //unequal length of operands

	for (int k = 0; k < operand1v.size(); k++)
	{
		// validate values of operands
		if ((operand1v[k] != 0) && (operand1v[k] != 1)) return ERROR_SYMBOL;
		if ((operand2v[k] != 0) && (operand2v[k] != 1)) return ERROR_SYMBOL;

		hammingDistance += operand1v[k] ^ operand2v[k]; // increment the distance
	}

	return hammingDistance;
}


__declspec(dllexport) int HammingDistanceB(std::vector<unsigned long> operand1b, std::vector<unsigned long> operand2b)
{
	int hammingDistance = 0;

	if (operand1b.size() != operand2b.size()) return ERROR_UNEVEN; //unequal length of operands

	for (int k = 0; k < operand1b.size(); k++)
	{
		unsigned long fragm1b = operand1b[k];
		unsigned long fragm2b = operand2b[k];

		for (int m = 0; m < sizeof(fragm1b)* 8; m++)
		{
			hammingDistance += (fragm1b & 1) ^ (fragm2b & 1); // //mask last bit and increment the distance

			//shift to next bit
			fragm1b >>= 1;
			fragm2b >>= 1;
		}
	}
	return hammingDistance;
}




__declspec(dllexport) int num2ascii(const char symbolIn, char &symbolOut)
{
	switch (symbolIn)
	{
	case 0:
		symbolOut = ASCII_ZERO;
		break;
	case 1:
		symbolOut = ASCII_ONE;
		break;
	default:
		return ERROR_SYMBOL; // unacceptable symbol
	}
	return 0; // no conversion errors
}



__declspec(dllexport) int S2V(const char *symbolIn, std::vector<char> &operandOut)
{
	operandOut.clear();

	for (int k = 0; k < MAX_OPERAND_LENGTH; k++)
	{
		if (EOS == symbolIn[k]) //end of operand reached
		{
			return 0; // no conversion errors
		}

		// convert symbols to numbers
		char outValue;
		if (ascii2num(symbolIn[k], outValue))
		{
			operandOut.clear();
			return ERROR_SYMBOL;
		}
		operandOut.push_back(outValue);
	}

	operandOut.clear();
	return ERROR_TOO_LONG;
}


__declspec(dllexport) int V2S(std::vector<char> operandIn, char *&symbolsOut)
{
	if (symbolsOut != NULL) return ERROR_RUN;

	if (operandIn.size() == 0) return ERROR_RUN;

	symbolsOut = new char[operandIn.size() + 1]; // + 1 for ending 0

	for (int k = 0; k < operandIn.size(); k++)
	{
		// convert numbers to symbols
		if (num2ascii(operandIn[k], symbolsOut[k]))
		{
			delete[] symbolsOut;
			return ERROR_SYMBOL;
		}
	}

	symbolsOut[operandIn.size()] = EOS;  // add ending 0

	return 0; // no conversion errors
}



