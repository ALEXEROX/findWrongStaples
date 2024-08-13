#include "pch.h"
#include "CppUnitTest.h"
#include "Header.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace findWrongStaplesTests
{
	TEST_CLASS(isStaplesTests)
	{
	public:
		
		TEST_METHOD(IsStaples)
		{
			char staples[] = { '(', ')', '[', ']', '{', '}' };
			for (int i = 0; i < 6; i++)
			{
				Assert::AreEqual(true, isStaple(staples[i]));
			}
		}

		TEST_METHOD(IsNotStaples)
		{
			char staples[] = { '<', '>', '\"', '\'', 'v', '^' };
			for (int i = 0; i < 6; i++)
			{
				Assert::AreEqual(false, isStaple(staples[i]));
			}
		}
	};
}
