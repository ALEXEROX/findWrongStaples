#include "pch.h"
#include "CppUnitTest.h"
#include "Header.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace findWrongStaplesTests
{
	TEST_CLASS(IsStaplesTests)
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

	TEST_CLASS(FindWrongStaplesSimpleTests)
	{
	public:

		TEST_METHOD(RoundStaples)
		{
			vector<string> code = { "()" };
			vector<vector<int>> positions;
			int wrongStaples = findWrongStaples(code, positions);
			int exp_wrongStaples = 0;
			Assert::AreEqual(exp_wrongStaples, wrongStaples);
		}
		TEST_METHOD(TwoPaarRoundStaples)
		{
			vector<string> code = { "()()" };
			vector<vector<int>> positions;
			int wrongStaples = findWrongStaples(code, positions);
			int exp_wrongStaples = 0;
			Assert::AreEqual(exp_wrongStaples, wrongStaples);
		}
	};
}
