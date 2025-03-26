#include "pch.h"
#include "CppUnitTest.h"
#include "Header.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace findWrongStaplesTests
{
	TEST_CLASS(ArePairedBracketsTest)
	{
	public:

		TEST_METHOD(PairedRoundStaples)
		{
			char firstStaple = '(';
			char secondStaple = ')';
			bool pairedStaples = arePairedBrackets(firstStaple, secondStaple);
			bool exp_pairedStaples = true;
			Assert::AreEqual(exp_pairedStaples, pairedStaples);
		}

		TEST_METHOD(PairedSquareStaples)
		{
			char firstStaple = '[';
			char secondStaple = ']';
			bool pairedStaples = arePairedBrackets(firstStaple, secondStaple);
			bool exp_pairedStaples = true;
			Assert::AreEqual(exp_pairedStaples, pairedStaples);
		}

		TEST_METHOD(PairedFigureStaples)
		{
			char firstStaple = '{';
			char secondStaple = '}';
			bool pairedStaples = arePairedBrackets(firstStaple, secondStaple);
			bool exp_pairedStaples = true;
			Assert::AreEqual(exp_pairedStaples, pairedStaples);
		}

		TEST_METHOD(DifferentStaples)
		{
			char firstStaple = '(';
			char secondStaple = ']';
			bool pairedStaples = arePairedBrackets(firstStaple, secondStaple);
			bool exp_pairedStaples = false;
			Assert::AreEqual(exp_pairedStaples, pairedStaples);
		}

		TEST_METHOD(OneSidedStaples)
		{
			char firstStaple = ']';
			char secondStaple = ']';
			bool pairedStaples = arePairedBrackets(firstStaple, secondStaple);
			bool exp_pairedStaples = false;
			Assert::AreEqual(exp_pairedStaples, pairedStaples);
		}

		TEST_METHOD(ExpandetStaples)
		{
			char firstStaple = ']';
			char secondStaple = '[';
			bool pairedStaples = arePairedBrackets(firstStaple, secondStaple);
			bool exp_pairedStaples = false;
			Assert::AreEqual(exp_pairedStaples, pairedStaples);
		}
	};

	TEST_CLASS(FindWordsInCodeTest)
	{
	public:

		TEST_METHOD(SingleChar)
		{
			vector<wstring> code = { L"a" };
			vector<wstring> words = { L"a" };
			vector<vector<int>> positions;
			int wordsCount = findSubstringsInCode(code, words, positions);
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
			vector<wstring> code = { L"Code" };
			vector<wstring> words = { L"Code" };
			vector<vector<int>> positions;
			int wordsCount = findSubstringsInCode(code, words, positions);
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
			vector<wstring> code = { L"b a" };
			vector<wstring> words = { L"a", L"b"};
			vector<vector<int>> positions;
			int wordsCount = findSubstringsInCode(code, words, positions);
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
			vector<wstring> code = { L"Code cpp" };
			vector<wstring> words = { L"cpp", L"Code" };
			vector<vector<int>> positions;
			int wordsCount = findSubstringsInCode(code, words, positions);
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
			vector<wstring> code = { L"Expected" };
			vector<wstring> words = { L"ect" };
			vector<vector<int>> positions;
			int wordsCount = findSubstringsInCode(code, words, positions);
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
			vector<wstring> code = { L"codecode" };
			vector<wstring> words = { L"code" };
			vector<vector<int>> positions;
			int wordsCount = findSubstringsInCode(code, words, positions);
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
			vector<wstring> code = { L"code", L"code"};
			vector<wstring> words = { L"code" };
			vector<vector<int>> positions;
			int wordsCount = findSubstringsInCode(code, words, positions);
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
			vector<wstring> code = { L"corocoroco" };
			vector<wstring> words = { L"coroco" };
			vector<vector<int>> positions;
			int wordsCount = findSubstringsInCode(code, words, positions);
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
			vector<wstring> code = { L"coro", L"co" };
			vector<wstring> words = { L"coroco" };
			vector<vector<int>> positions;
			int wordsCount = findSubstringsInCode(code, words, positions);
			int exp_wordsCount = 0;
			Assert::AreEqual(exp_wordsCount, wordsCount);
		}
	};

	TEST_CLASS(FindWrongStaplesTest)
	{
	public:

		TEST_METHOD(VoidString)
		{
			vector<wstring> code = { L"" };
			vector<vector<int>> positions;
			int wrongStaples = findWrongStaples(code, positions);
			int exp_wrongStaples = 0;
			Assert::AreEqual(exp_wrongStaples, wrongStaples);
		}

		TEST_METHOD(SingleStaple)
		{
			vector<wstring> code = { L"(" };
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
			vector<wstring> code = { L"()" };
			vector<vector<int>> positions;
			int wrongStaples = findWrongStaples(code, positions);
			int exp_wrongStaples = 0;
			Assert::AreEqual(exp_wrongStaples, wrongStaples);
		}

		TEST_METHOD(ExpandedRoundStaples)
		{
			vector<wstring> code = { L")(" };
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
			vector<wstring> code = { L"()()" };
			vector<vector<int>> positions;
			int wrongStaples = findWrongStaples(code, positions);
			int exp_wrongStaples = 0;
			Assert::AreEqual(exp_wrongStaples, wrongStaples);
		}

		TEST_METHOD(TwoPaarsNestedRoundStaples)
		{
			vector<wstring> code = { L"(())" };
			vector<vector<int>> positions;
			int wrongStaples = findWrongStaples(code, positions);
			int exp_wrongStaples = 0;
			Assert::AreEqual(exp_wrongStaples, wrongStaples);
		}

		TEST_METHOD(RoundStaplesInFigureStaples)
		{
			vector<wstring> code = { L"{()}" };
			vector<vector<int>> positions;
			int wrongStaples = findWrongStaples(code, positions);
			int exp_wrongStaples = 0;
			Assert::AreEqual(exp_wrongStaples, wrongStaples);
		}

		TEST_METHOD(IntersectingStaples)
		{
			vector<wstring> code = { L"{(})" };
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
			vector<wstring> code = { L"{[()]}" };
			vector<vector<int>> positions;
			int wrongStaples = findWrongStaples(code, positions);
			int exp_wrongStaples = 0;
			Assert::AreEqual(exp_wrongStaples, wrongStaples);
		}

		TEST_METHOD(MultiTest)
		{
			vector<wstring> code = { L"{(})()([[]])([[)" };
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
			vector<wstring> code =  { L"#include <iostream>",
			L"",
			L"using namespace std;",
			L"",
			L"int main(int argc, char* argv[])",
			L"{",
			L"    cout << \"Hello world\" << endl;",
			L"",
			L"    return 0;",
			L"}"};

			vector<vector<int>> positions;
			int wrongStaples = findWrongStaples(code, positions);
			int exp_wrongStaples = 0;
			Assert::AreEqual(exp_wrongStaples, wrongStaples);
		}

		TEST_METHOD(SkippedSquareStaple)
		{
			vector<wstring> code =  { L"#include <iostream>",
			L"",
			L"using namespace std;",
			L"",
			L"int main(int argc, char* argv])",
			L"{",
			L"    cout << \"(\" << endl;",
			L"",
			L"    return 0;",
			L"}"};

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
			vector<wstring> code =  { L"#include <iostream>",
			L"",
			L"using namespace std;",
			L"",
			L"int main(int argc, char* argv[]",
			L"{",
			L"    cout << \"Hello world\" << endl;",
			L"",
			L"    return 0;",
			L"}"};

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
			vector<wstring> code =  { L"#include <iostream>",
			L"",
			L"using namespace std;",
			L"",
			L"int main(int argc, char* argv[])",
			L"{",
			L"    cout << \"Hello world\" << endl;",
			L"",
			L"    return 0;",
			L""};

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
			vector<wstring> code = { L"#include <iostream>",
			L"",
			L"using namespace std;",
			L"",
			L"int main(int argc, char* argv[])",
			L"{",
			L"    cout << \"Hello world\" << endl; // ;)",
			L"",
			L"    return 0;",
			L"}" };

			vector<vector<int>> positions;
			int wrongStaples = findWrongStaples(code, positions);
			int exp_wrongStaples = 0;
			Assert::AreEqual(exp_wrongStaples, wrongStaples);
		}

		TEST_METHOD(MultilineComment)
		{
			vector<wstring> code = { L"#include <iostream>",
			L"",
			L"using namespace std;",
			L"",
			L"int main(int argc, char* argv[])",
			L"{",
			L"    cout << \"Hello world\" << endl; /*",
			L")",
			L"*/",
			L"",
			L"    return 0;",
			L"}" };

			vector<vector<int>> positions;
			int wrongStaples = findWrongStaples(code, positions);
			int exp_wrongStaples = 0;
			Assert::AreEqual(exp_wrongStaples, wrongStaples);
		}

		TEST_METHOD(Char)
		{
			vector<wstring> code = { L"#include <iostream>",
			L"",
			L"using namespace std;",
			L"",
			L"int main(int argc, char* argv[])",
			L"{",
			L"    cout << \']\' << endl;",
			L"",
			L"    return 0;",
			L"}" };

			vector<vector<int>> positions;
			int wrongStaples = findWrongStaples(code, positions);
			int exp_wrongStaples = 0;
			Assert::AreEqual(exp_wrongStaples, wrongStaples);
		}

		TEST_METHOD(String)
		{
			vector<wstring> code = { L"#include <iostream>",
			L"",
			L"using namespace std;",
			L"",
			L"int main(int argc, char* argv[])",
			L"{",
			L"    cout << \":}\" << endl; ",
			L"",
			L"    return 0;",
			L"}" };

			vector<vector<int>> positions;
			int wrongStaples = findWrongStaples(code, positions);
			int exp_wrongStaples = 0;
			Assert::AreEqual(exp_wrongStaples, wrongStaples);
		}

		TEST_METHOD(SingleQuotationMarkInChar)
		{
			vector<wstring> code = { L"#include <iostream>",
			L"",
			L"using namespace std;",
			L"",
			L"int main(int argc, char* argv[])",
			L"{",
			L"    cout << ('\\\'') << endl;", // cout << '\'' << endl;
			L"",
			L"    return 0;",
			L"}" };

			vector<vector<int>> positions;
			int wrongStaples = findWrongStaples(code, positions);
			int exp_wrongStaples = 0;
			Assert::AreEqual(exp_wrongStaples, wrongStaples);
		}

		TEST_METHOD(DoubleQuotationMarkInString)
		{
			vector<wstring> code = { L"#include <iostream>",
			L"",
			L"using namespace std;",
			L"",
			L"int main(int argc, char* argv[])",
			L"{",
			L"    cout << \"\\\" Hello world :) \" << endl;", // cout << "\" Hello world \"" << endl;
			L"",
			L"    return 0;",
			L"}" };

			vector<vector<int>> positions;
			int wrongStaples = findWrongStaples(code, positions);
			int exp_wrongStaples = 0;
			Assert::AreEqual(exp_wrongStaples, wrongStaples);
		}


		TEST_METHOD(OnelineCommentInMultilineComment)
		{
			vector<wstring> code = { L"int main() { /*",
			L"    // return 0; { */",
			L"}"
			};

			vector<vector<int>> positions;
			int wrongStaples = findWrongStaples(code, positions);
			int exp_wrongStaples = 0;
			Assert::AreEqual(exp_wrongStaples, wrongStaples);
		}


		TEST_METHOD(MultilineCommentInOnelineComment)
		{
			vector<wstring> code = { L"int main() {",
			L"    // return 0; /*{ */",
			L"}"
			};

			vector<vector<int>> positions;
			int wrongStaples = findWrongStaples(code, positions);
			int exp_wrongStaples = 0;
			Assert::AreEqual(exp_wrongStaples, wrongStaples);
		}


		TEST_METHOD(StringInOnelineComment)
		{
			vector<wstring> code = { L"int main() {",
			L"    // return 0; \"{ \"",
			L"}"
			};

			vector<vector<int>> positions;
			int wrongStaples = findWrongStaples(code, positions);
			int exp_wrongStaples = 0;
			Assert::AreEqual(exp_wrongStaples, wrongStaples);
		}


		TEST_METHOD(StringInMultilineComment)
		{
			vector<wstring> code = { L"int main() { /*",
			L"    return 0; \"{ \" */",
			L"}"
			};

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
			wstring code = L"int i = 0;";
			wstring exp_code = L"int i = 0;";
			int spaces = deleteBeginSpaces(code);
			int exp_spaces = 0;
			Assert::AreEqual(exp_spaces, spaces);
			Assert::AreEqual(exp_code, code);
		}

		TEST_METHOD(OneSpace)
		{
			wstring code = L" int i = 0;";
			wstring exp_code = L"int i = 0;";
			int spaces = deleteBeginSpaces(code);
			int exp_spaces = 1;
			Assert::AreEqual(exp_spaces, spaces);
			Assert::AreEqual(exp_code, code);
		}

		TEST_METHOD(FourSpaces)
		{
			wstring code = L"    int i = 0;";
			wstring exp_code = L"int i = 0;";
			int spaces = deleteBeginSpaces(code);
			int exp_spaces = 4;
			Assert::AreEqual(exp_spaces, spaces);
			Assert::AreEqual(exp_code, code);
		}

		TEST_METHOD(OneTab)
		{
			wstring code = L"\tint i = 0;";
			wstring exp_code = L"int i = 0;";
			int spaces = deleteBeginSpaces(code);
			int exp_spaces = 1;
			Assert::AreEqual(exp_spaces, spaces);
			Assert::AreEqual(exp_code, code);
		}

		TEST_METHOD(OneSpaceAndOneTab)
		{
			wstring code = L" \tint i = 0;";
			wstring exp_code = L"int i = 0;";
			int spaces = deleteBeginSpaces(code);
			int exp_spaces = 2;
			Assert::AreEqual(exp_spaces, spaces);
			Assert::AreEqual(exp_code, code);
		}

	};
}