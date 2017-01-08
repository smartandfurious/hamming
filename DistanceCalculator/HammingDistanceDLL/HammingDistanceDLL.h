#pragma once
#include <vector>

// calculates hamming distance between two binary vectors represented as ASCII characters, '0's and '1's 
__declspec(dllexport) int HammingDistanceP(const char *operand1str, const char *operand2str);

// calculates hamming distance between two binary vectors represented as vectors of 0s and 1s 
__declspec(dllexport) int HammingDistanceV(std::vector<char> operand1v, std::vector<char> operand2v);

// calculates hamming distance between two binary vectors represented as individual bits combined in vectors
__declspec(dllexport) int HammingDistanceB(std::vector<unsigned long> operand1b, std::vector<unsigned long> operand2b);



// converts character to number (only 0s and 1s)
__declspec(dllexport) int ascii2num(const char symbolIn, char &symbolOut);
// converts number to character (only 0s and 1s)
__declspec(dllexport) int num2ascii(const char symbolIn, char &symbolOut);


// converts binary blob from character representation to number representation
__declspec(dllexport) int S2V(const char *symbolIn, std::vector<char> &operandOut);
// converts binary blob from number representation to character representation
__declspec(dllexport) int V2S(std::vector<char> operandIn, char *&symbolsOut);