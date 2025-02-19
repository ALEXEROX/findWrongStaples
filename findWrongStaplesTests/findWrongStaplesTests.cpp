#include "pch.h"
#include "CppUnitTest.h"
#include "Header.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace findWrongStaplesTests
{
	TEST_CLASS(IsPairedStaplesTest)
	{
	public:

		TEST_METHOD(PairedRoundStaples)
		{
			char firstStaple = '(';
			char secondStaple = ')';
			bool pairedStaples = isPairedStaples(firstStaple, secondStaple);
			bool exp_pairedStaples = true;
			Assert::AreEqual(exp_pairedStaples, pairedStaples);
		}

		TEST_METHOD(PairedSquareStaples)
		{
			char firstStaple = '[';
			char secondStaple = ']';
			bool pairedStaples = isPairedStaples(firstStaple, secondStaple);
			bool exp_pairedStaples = true;
			Assert::AreEqual(exp_pairedStaples, pairedStaples);
		}

		TEST_METHOD(PairedFigureStaples)
		{
			char firstStaple = '{';
			char secondStaple = '}';
			bool pairedStaples = isPairedStaples(firstStaple, secondStaple);
			bool exp_pairedStaples = true;
			Assert::AreEqual(exp_pairedStaples, pairedStaples);
		}

		TEST_METHOD(DifferentStaples)
		{
			char firstStaple = '(';
			char secondStaple = ']';
			bool pairedStaples = isPairedStaples(firstStaple, secondStaple);
			bool exp_pairedStaples = false;
			Assert::AreEqual(exp_pairedStaples, pairedStaples);
		}

		TEST_METHOD(OneSidedStaples)
		{
			char firstStaple = ']';
			char secondStaple = ']';
			bool pairedStaples = isPairedStaples(firstStaple, secondStaple);
			bool exp_pairedStaples = false;
			Assert::AreEqual(exp_pairedStaples, pairedStaples);
		}

		TEST_METHOD(ExpandetStaples)
		{
			char firstStaple = ']';
			char secondStaple = '[';
			bool pairedStaples = isPairedStaples(firstStaple, secondStaple);
			bool exp_pairedStaples = false;
			Assert::AreEqual(exp_pairedStaples, pairedStaples);
		}
	};

	TEST_CLASS(FindWordsInCodeTest)
	{
	public:

		TEST_METHOD(SingleChar)
		{
			vector<string> code = { "a" };
			vector<string> words = { "a" };
			vector<vector<int>> positions;
			int wordsCount = findWordsInCode(code, words, positions);
			int exp_wordsCount = 1;
			vector<vector<int>> exp_positions = { {0,0} };
			Assert::AreEqual(exp_wordsCount, wordsCount);
			for (int i = 0; i < exp_wordsCount; i++)
			{
				Assert::AreEqual(exp_positions[i][0], positions[i][0]);
				Assert::AreEqual(exp_positions[i][1], positions[i][1]);
			}
		}

		TEST_METHOD(SingleWord)
		{
			vector<string> code = { "Code" };
			vector<string> words = { "Code" };
			vector<vector<int>> positions;
			int wordsCount = findWordsInCode(code, words, positions);
			int exp_wordsCount = 1;
			vector<vector<int>> exp_positions = { {0,0} };
			Assert::AreEqual(exp_wordsCount, wordsCount);
			for (int i = 0; i < exp_wordsCount; i++)
			{
				Assert::AreEqual(exp_positions[i][0], positions[i][0]);
				Assert::AreEqual(exp_positions[i][1], positions[i][1]);
			}
		}

		TEST_METHOD(TwoChars)
		{
			vector<string> code = { "b a" };
			vector<string> words = { "a", "b"};
			vector<vector<int>> positions;
			int wordsCount = findWordsInCode(code, words, positions);
			int exp_wordsCount = 2;
			vector<vector<int>> exp_positions = { {0,0}, {0,2} };
			Assert::AreEqual(exp_wordsCount, wordsCount);
			for (int i = 0; i < exp_wordsCount; i++)
			{
				Assert::AreEqual(exp_positions[i][0], positions[i][0]);
				Assert::AreEqual(exp_positions[i][1], positions[i][1]);
			}
		}

		TEST_METHOD(TwoWords)
		{
			vector<string> code = { "Code cpp" };
			vector<string> words = { "cpp", "Code" };
			vector<vector<int>> positions;
			int wordsCount = findWordsInCode(code, words, positions);
			int exp_wordsCount = 2;
			vector<vector<int>> exp_positions = { {0,0}, {0,5} };
			Assert::AreEqual(exp_wordsCount, wordsCount);
			for (int i = 0; i < exp_wordsCount; i++)
			{
				Assert::AreEqual(exp_positions[i][0], positions[i][0]);
				Assert::AreEqual(exp_positions[i][1], positions[i][1]);
			}
		}

		TEST_METHOD(WordInOtherWord)
		{
			vector<string> code = { "Expected" };
			vector<string> words = { "ect" };
			vector<vector<int>> positions;
			int wordsCount = findWordsInCode(code, words, positions);
			int exp_wordsCount = 1;
			vector<vector<int>> exp_positions = { {0,3} };
			Assert::AreEqual(exp_wordsCount, wordsCount);
			for (int i = 0; i < exp_wordsCount; i++)
			{
				Assert::AreEqual(exp_positions[i][0], positions[i][0]);
				Assert::AreEqual(exp_positions[i][1], positions[i][1]);
			}
		}

		TEST_METHOD(OneWordTwoTimes)
		{
			vector<string> code = { "codecode" };
			vector<string> words = { "code" };
			vector<vector<int>> positions;
			int wordsCount = findWordsInCode(code, words, positions);
			int exp_wordsCount = 2;
			vector<vector<int>> exp_positions = { {0,0}, {0,4} };
			Assert::AreEqual(exp_wordsCount, wordsCount);
			for (int i = 0; i < exp_wordsCount; i++)
			{
				Assert::AreEqual(exp_positions[i][0], positions[i][0]);
				Assert::AreEqual(exp_positions[i][1], positions[i][1]);
			}
		}

		TEST_METHOD(OneWordTwoTimesInDifferentLines)
		{
			vector<string> code = { "code", "code"};
			vector<string> words = { "code" };
			vector<vector<int>> positions;
			int wordsCount = findWordsInCode(code, words, positions);
			int exp_wordsCount = 2;
			vector<vector<int>> exp_positions = { {0,0}, {1,0} };
			Assert::AreEqual(exp_wordsCount, wordsCount);
			for (int i = 0; i < exp_wordsCount; i++)
			{
				Assert::AreEqual(exp_positions[i][0], positions[i][0]);
				Assert::AreEqual(exp_positions[i][1], positions[i][1]);
			}
		}

		TEST_METHOD(IntersectingWords)
		{
			vector<string> code = { "corocoroco" };
			vector<string> words = { "coroco" };
			vector<vector<int>> positions;
			int wordsCount = findWordsInCode(code, words, positions);
			int exp_wordsCount = 1;
			vector<vector<int>> exp_positions = { {0,0} };
			Assert::AreEqual(exp_wordsCount, wordsCount);
			for (int i = 0; i < exp_wordsCount; i++)
			{
				Assert::AreEqual(exp_positions[i][0], positions[i][0]);
				Assert::AreEqual(exp_positions[i][1], positions[i][1]);
			}
		}

		TEST_METHOD(TornWord)
		{
			vector<string> code = { "coro", "co" };
			vector<string> words = { "coroco" };
			vector<vector<int>> positions;
			int wordsCount = findWordsInCode(code, words, positions);
			int exp_wordsCount = 0;
			Assert::AreEqual(exp_wordsCount, wordsCount);
		}
	};

	TEST_CLASS(FindWrongStaplesTest)
	{
	public:

		TEST_METHOD(VoidString)
		{
			vector<string> code = { "" };
			vector<vector<int>> positions;
			int wrongStaples = findWrongStaples(code, positions);
			int exp_wrongStaples = 0;
			Assert::AreEqual(exp_wrongStaples, wrongStaples);
		}

		TEST_METHOD(SingleStaple)
		{
			vector<string> code = { "(" };
			vector<vector<int>> positions;
			vector<vector<int>> exp_positions{ {0, 0} };
			int wrongStaples = findWrongStaples(code, positions);
			int exp_wrongStaples = 1;
			Assert::AreEqual(exp_wrongStaples, wrongStaples);
			for (int i = 0; i < exp_wrongStaples; i++)
			{
				Assert::AreEqual(exp_positions[i][0], positions[i][0]);
				Assert::AreEqual(exp_positions[i][1], positions[i][1]);
			}
		}

		TEST_METHOD(RoundStaples)
		{
			vector<string> code = { "()" };
			vector<vector<int>> positions;
			int wrongStaples = findWrongStaples(code, positions);
			int exp_wrongStaples = 0;
			Assert::AreEqual(exp_wrongStaples, wrongStaples);
		}

		TEST_METHOD(ExpandedRoundStaples)
		{
			vector<string> code = { ")(" };
			vector<vector<int>> positions;
			vector<vector<int>> exp_positions{ {0, 0}, {0, 1} };
			int wrongStaples = findWrongStaples(code, positions);
			int exp_wrongStaples = 2;
			Assert::AreEqual(exp_wrongStaples, wrongStaples);
			for (int i = 0; i < exp_wrongStaples; i++)
			{
				Assert::AreEqual(exp_positions[i][0], positions[i][0]);
				Assert::AreEqual(exp_positions[i][1], positions[i][1]);
			}
		}

		TEST_METHOD(TwoPaarsRoundStaples)
		{
			vector<string> code = { "()()" };
			vector<vector<int>> positions;
			int wrongStaples = findWrongStaples(code, positions);
			int exp_wrongStaples = 0;
			Assert::AreEqual(exp_wrongStaples, wrongStaples);
		}

		TEST_METHOD(TwoPaarsNestedRoundStaples)
		{
			vector<string> code = { "(())" };
			vector<vector<int>> positions;
			int wrongStaples = findWrongStaples(code, positions);
			int exp_wrongStaples = 0;
			Assert::AreEqual(exp_wrongStaples, wrongStaples);
		}

		TEST_METHOD(RoundStaplesInFigureStaples)
		{
			vector<string> code = { "{()}" };
			vector<vector<int>> positions;
			int wrongStaples = findWrongStaples(code, positions);
			int exp_wrongStaples = 0;
			Assert::AreEqual(exp_wrongStaples, wrongStaples);
		}

		TEST_METHOD(IntersectingStaples)
		{
			vector<string> code = { "{(})" };
			vector<vector<int>> positions;
			vector<vector<int>> exp_positions { {0, 1}, {0, 3} };
			int wrongStaples = findWrongStaples(code, positions);
			int exp_wrongStaples = 2;
			Assert::AreEqual(exp_wrongStaples, wrongStaples);
			for (int i = 0; i < exp_wrongStaples; i++)
			{
				Assert::AreEqual(exp_positions[i][0], positions[i][0]);
				Assert::AreEqual(exp_positions[i][1], positions[i][1]);
			}
		}

		TEST_METHOD(ThreePaarsNestedStaples)
		{
			vector<string> code = { "{[()]}" };
			vector<vector<int>> positions;
			int wrongStaples = findWrongStaples(code, positions);
			int exp_wrongStaples = 0;
			Assert::AreEqual(exp_wrongStaples, wrongStaples);
		}

		TEST_METHOD(MultiTest)
		{
			vector<string> code = { "{(})()([[]])([[)" };
			vector<vector<int>> positions;
			vector<vector<int>> exp_positions{ {0, 1}, {0, 3}, {0, 13}, {0, 14} };
			int wrongStaples = findWrongStaples(code, positions);
			int exp_wrongStaples = 4;
			Assert::AreEqual(exp_wrongStaples, wrongStaples);
			for (int i = 0; i < exp_wrongStaples; i++)
			{
				Assert::AreEqual(exp_positions[i][0], positions[i][0]);
				Assert::AreEqual(exp_positions[i][1], positions[i][1]);
			}
		}

		TEST_METHOD(DefaultCppProject)
		{
			vector<string> code =  { "#include <iostream>",
			"",
			"using namespace std;",
			"",
			"int main(int argc, char* argv[])",
			"{",
			"    cout << \"Hello world\" << endl;",
			"",
			"    return 0;",
			"}"};

			vector<vector<int>> positions;
			int wrongStaples = findWrongStaples(code, positions);
			int exp_wrongStaples = 0;
			Assert::AreEqual(exp_wrongStaples, wrongStaples);
		}

		TEST_METHOD(SkippedSquareStaple)
		{
			vector<string> code =  { "#include <iostream>",
			"",
			"using namespace std;",
			"",
			"int main(int argc, char* argv])",
			"{",
			"    cout << \"Hello world\" << endl;",
			"",
			"    return 0;",
			"}"};

			vector<vector<int>> positions;
			vector<vector<int>> exp_positions{ {4, 29} };
			int wrongStaples = findWrongStaples(code, positions);
			int exp_wrongStaples = 1;
			Assert::AreEqual(exp_wrongStaples, wrongStaples);
			for (int i = 0; i < exp_wrongStaples; i++)
			{
				Assert::AreEqual(exp_positions[i][0], positions[i][0]);
				Assert::AreEqual(exp_positions[i][1], positions[i][1]);
			}
		}

		TEST_METHOD(SkippedRoundStaple)
		{
			vector<string> code =  { "#include <iostream>",
			"",
			"using namespace std;",
			"",
			"int main(int argc, char* argv[]",
			"{",
			"    cout << \"Hello world\" << endl;",
			"",
			"    return 0;",
			"}"};

			vector<vector<int>> positions;
			vector<vector<int>> exp_positions{ {4, 8} };
			int wrongStaples = findWrongStaples(code, positions);
			int exp_wrongStaples = 1;
			Assert::AreEqual(exp_wrongStaples, wrongStaples);
			for (int i = 0; i < exp_wrongStaples; i++)
			{
				Assert::AreEqual(exp_positions[i][0], positions[i][0]);
				Assert::AreEqual(exp_positions[i][1], positions[i][1]);
			}
		}

		TEST_METHOD(SkippedFigureStaple)
		{
			vector<string> code =  { "#include <iostream>",
			"",
			"using namespace std;",
			"",
			"int main(int argc, char* argv[])",
			"{",
			"    cout << \"Hello world\" << endl;",
			"",
			"    return 0;",
			""};

			vector<vector<int>> positions;
			vector<vector<int>> exp_positions{ {5, 0} };
			int wrongStaples = findWrongStaples(code, positions);
			int exp_wrongStaples = 1;
			Assert::AreEqual(exp_wrongStaples, wrongStaples);
			for (int i = 0; i < exp_wrongStaples; i++)
			{
				Assert::AreEqual(exp_positions[i][0], positions[i][0]);
				Assert::AreEqual(exp_positions[i][1], positions[i][1]);
			}
		}

		TEST_METHOD(OnelineComment)
		{
			vector<string> code = { "#include <iostream>",
			"",
			"using namespace std;",
			"",
			"int main(int argc, char* argv[])",
			"{",
			"    cout << \"Hello world\" << endl; // ;)",
			"",
			"    return 0;",
			"}" };

			vector<vector<int>> positions;
			int wrongStaples = findWrongStaples(code, positions);
			int exp_wrongStaples = 0;
			Assert::AreEqual(exp_wrongStaples, wrongStaples);
		}

		TEST_METHOD(MultilineComment)
		{
			vector<string> code = { "#include <iostream>",
			"",
			"using namespace std;",
			"",
			"int main(int argc, char* argv[])",
			"{",
			"    cout << \"Hello world\" << endl; /*",
			")",
			"*/",
			"",
			"    return 0;",
			"}" };

			vector<vector<int>> positions;
			int wrongStaples = findWrongStaples(code, positions);
			int exp_wrongStaples = 0;
			Assert::AreEqual(exp_wrongStaples, wrongStaples);
		}

		TEST_METHOD(Char)
		{
			vector<string> code = { "#include <iostream>",
			"",
			"using namespace std;",
			"",
			"int main(int argc, char* argv[])",
			"{",
			"    cout << ']' << endl;",
			"",
			"    return 0;",
			"}" };

			vector<vector<int>> positions;
			int wrongStaples = findWrongStaples(code, positions);
			int exp_wrongStaples = 0;
			Assert::AreEqual(exp_wrongStaples, wrongStaples);
		}

		TEST_METHOD(String)
		{
			vector<string> code = { "#include <iostream>",
			"",
			"using namespace std;",
			"",
			"int main(int argc, char* argv[])",
			"{",
			"    cout << \":}\" << endl; ",
			"",
			"    return 0;",
			"}" };

			vector<vector<int>> positions;
			int wrongStaples = findWrongStaples(code, positions);
			int exp_wrongStaples = 0;
			Assert::AreEqual(exp_wrongStaples, wrongStaples);
		}

		TEST_METHOD(SingleQuotationMarkInChar)
		{
			vector<string> code = { "#include <iostream>",
			"",
			"using namespace std;",
			"",
			"int main(int argc, char* argv[])",
			"{",
			"    cout << ('\\\'') << endl;", // cout << '\'' << endl;
			"",
			"    return 0;",
			"}" };

			vector<vector<int>> positions;
			int wrongStaples = findWrongStaples(code, positions);
			int exp_wrongStaples = 0;
			Assert::AreEqual(exp_wrongStaples, wrongStaples);
		}

		TEST_METHOD(DoubleQuotationMarkInString)
		{
			vector<string> code = { "#include <iostream>",
			"",
			"using namespace std;",
			"",
			"int main(int argc, char* argv[])",
			"{",
			"    cout << \"\\\" Hello world :) \" << endl;", // cout << "\" Hello world \"" << endl;
			"",
			"    return 0;",
			"}" };

			vector<vector<int>> positions;
			int wrongStaples = findWrongStaples(code, positions);
			int exp_wrongStaples = 0;
			Assert::AreEqual(exp_wrongStaples, wrongStaples);
		}
	};

	TEST_CLASS(DeleteBeginSpacesTest)
	{
	public:

		TEST_METHOD(NoSpaces)
		{
			string code = "int i = 0;";
			string exp_code = "int i = 0;";
			int spaces = deleteBeginSpaces(code);
			int exp_spaces = 0;
			Assert::AreEqual(exp_spaces, spaces);
			Assert::AreEqual(exp_code, code);
		}

		TEST_METHOD(OneSpace)
		{
			string code = " int i = 0;";
			string exp_code = "int i = 0;";
			int spaces = deleteBeginSpaces(code);
			int exp_spaces = 1;
			Assert::AreEqual(exp_spaces, spaces);
			Assert::AreEqual(exp_code, code);
		}

		TEST_METHOD(FourSpaces)
		{
			string code = "    int i = 0;";
			string exp_code = "int i = 0;";
			int spaces = deleteBeginSpaces(code);
			int exp_spaces = 4;
			Assert::AreEqual(exp_spaces, spaces);
			Assert::AreEqual(exp_code, code);
		}

		TEST_METHOD(OneTab)
		{
			string code = "\tint i = 0;";
			string exp_code = "int i = 0;";
			int spaces = deleteBeginSpaces(code);
			int exp_spaces = 1;
			Assert::AreEqual(exp_spaces, spaces);
			Assert::AreEqual(exp_code, code);
		}

		TEST_METHOD(OneSpaceAndOneTab)
		{
			string code = " \tint i = 0;";
			string exp_code = "int i = 0;";
			int spaces = deleteBeginSpaces(code);
			int exp_spaces = 2;
			Assert::AreEqual(exp_spaces, spaces);
			Assert::AreEqual(exp_code, code);
		}

	};
}
