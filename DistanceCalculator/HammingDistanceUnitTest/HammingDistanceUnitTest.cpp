#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\HammingDistanceDLL\HammingDistanceDLL.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HammingDistanceUnitTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_METHOD(ascii2str)
		{
			char symOut = -1;
			int out = ascii2num('1', symOut);
			Assert::AreEqual(0, out, L"Error is generated for 1");
			Assert::AreEqual((char)1, symOut, L"Incorrect output for 1");

			symOut = -1;
			out = ascii2num('0', symOut);
			Assert::AreEqual(0, out, L"Error is generated for 0");
			Assert::AreEqual((char)0, symOut, L"Incorrect output for 0");

			symOut = -1;
			out = ascii2num('3', symOut);
			Assert::AreEqual(-3, out, L"Error is not generated for 3");

		}

		TEST_METHOD(str2ascii)
		{
			char symOut = -1;
			int out = num2ascii(1, symOut);
			Assert::AreEqual(0, out, L"Error is generated for 1");
			Assert::AreEqual((char)49, symOut, L"Incorrect output for 1");

			symOut = -1;
			out = num2ascii(0, symOut);
			Assert::AreEqual(0, out, L"Error is generated for 0");
			Assert::AreEqual((char)48, symOut, L"Incorrect output for 0");

			symOut = -1;
			out = num2ascii(3, symOut);
			Assert::AreEqual(-3, out, L"Error is not generated for 3");
		}


		TEST_METHOD(S2V_test)
		{
			char inStr[] = "011010";
			std::vector<char> outVec;

			int out = S2V(inStr, outVec);
			
			Assert::AreEqual(0, out, L"Error is generated for S2V_Test");
			Assert::AreEqual((char)0, outVec[0], L"Incorrect output for outVec[0]");
			Assert::AreEqual((char)1, outVec[1], L"Incorrect output for outVec[1]");
			Assert::AreEqual((char)1, outVec[2], L"Incorrect output for outVec[2]");
			Assert::AreEqual((char)0, outVec[3], L"Incorrect output for outVec[3]");
			Assert::AreEqual((char)1, outVec[4], L"Incorrect output for outVec[4]");
			Assert::AreEqual((char)0, outVec[5], L"Incorrect output for outVec[5]");
		}

		TEST_METHOD(V2S_test)
		{
			char *outStr = NULL;
			std::vector<char> inVec = {0,1,1,0,1,0}; 
			
			int out = V2S(inVec, outStr);

			Assert::AreEqual(0, out, L"Error is generated for V2S_Test");
			Assert::AreEqual((char)48, outStr[0], L"Incorrect output for outStr[0]");
			Assert::AreEqual((char)49, outStr[1], L"Incorrect output for outStr[1]");
			Assert::AreEqual((char)49, outStr[2], L"Incorrect output for outStr[2]");
			Assert::AreEqual((char)48, outStr[3], L"Incorrect output for outStr[3]");
			Assert::AreEqual((char)49, outStr[4], L"Incorrect output for outStr[4]");
			Assert::AreEqual((char)48, outStr[5], L"Incorrect output for outStr[5]");
			Assert::AreEqual((char)0,  outStr[6], L"Incorrect output for ending 0");
		}

		TEST_METHOD(HammingDistanceP_test)
		{

			int out = HammingDistanceP("0000", "0000");
			Assert::AreEqual(0, out, L"Incorrect output for HammingDistanceP(equal)");

			out = HammingDistanceP("0000", "1111");
			Assert::AreEqual(4, out, L"Error is generated for HammingDistanceP(different)");

			out = HammingDistanceP("0000", "11111");
			Assert::AreEqual(-2, out, L"Error is not generated for HammingDistanceP(different length)");

			out = HammingDistanceP("5000", "1111");
			Assert::AreEqual(-3, out, L"Error is not generated for HammingDistanceP(bad symbol)");

		}

		TEST_METHOD(HammingDistanceV_test)
		{
			int out = HammingDistanceP("0000", "0000");
			Assert::AreEqual(0, out, L"Incorrect output for HammingDistanceP(equal)");

			out = HammingDistanceP("0000", "1111");
			Assert::AreEqual(4, out, L"Error is generated for HammingDistanceP(different)");

			out = HammingDistanceP("0000", "11111");
			Assert::AreEqual(-2, out, L"Error is not generated for HammingDistanceP(different length)");

			out = HammingDistanceP("5000", "1111");
			Assert::AreEqual(-3, out, L"Error is not generated for HammingDistanceP(bad symbol)");

		}
	};
}


