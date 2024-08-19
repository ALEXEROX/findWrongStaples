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
	};

	TEST_CLASS(FindWrongStaplesHardTests)
	{

	public:

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
	};

	TEST_CLASS(FindWrongStaplesUnverifedZonesTests)
	{

	public:

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
			"    cout << \"Hello world\" << endl; // ;)",
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
}
