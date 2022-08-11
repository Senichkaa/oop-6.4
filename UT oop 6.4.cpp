#include "pch.h"
#include "CppUnitTest.h"
#include "../oop 6.4/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UToop64
{
	TEST_CLASS(UToop64)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Matrix<int> A(4);
			Assert::AreEqual(A.get_size(), 4);
		}
	};
}
