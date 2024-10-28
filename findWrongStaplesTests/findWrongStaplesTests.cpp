#include "pch.h"
#include "CppUnitTest.h"
#include "Header.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace findWrongStaplesTests
{
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

		TEST_METHOD(TestOnOwnCode)
		{
			vector<string> code = {
				"#include \"Header.h\"",
				"",
				"int main(int argc, char* argv[])",
				"{",
				"	// Russioan localization",
				"	setlocale(LC_ALL, \"rus\");",
				"",
				"	// File names",
				"	/*string inputFile = argv[1];",
				"	string outputFile = argv[2];*/",
				"	string inputFile = \"code.cpp\";",
				"	string outputFile = \"output.txt\";",
				"",
				"	// File streams",
				"	ifstream input;",
				"	input.open(inputFile);",
				"	ofstream output;",
				"	output.open(outputFile);",
				"",
				"	vector<string> code;",
				"	vector<vector<int>> positions;",
				"	bool mayWork = true;",
				"",
				"	// Check input file",
				"	if (inputFile.substr(inputFile.size() - 4, 4) != \".cpp\")",
				"	{",
				"		output << \"Входной файл имеет неподдерживаемый формат\" << endl;",
				"		mayWork = false;",
				"	}",
				"",
				"	// Check output file",
				"	if (mayWork && outputFile.substr(outputFile.size() - 4, 4) != \".txt\")",
				"	{",
				"		output << \"Выходной файл имеет неподдерживаемый формат\" << endl;",
				"		mayWork = false;",
				"	}",
				"",
				"	// Input",
				"	int lines = 0;",
				"	if (mayWork)",
				"	{",
				"		string line;",
				"		while (getline(input, line) && lines++ <= 255)",
				"		{",
				"			code.push_back(line);",
				"			if (line.size() > 1000)",
				"			{",
				"				output << \"Количество символов в строке(-ах) превышено\" << endl;",
				"				mayWork = false;",
				"				break;",
				"			}",
				"		}",
				"	}",
				"",
				"	// Check for strings count",
				"	if (mayWork && lines > 255)",
				"	{",
				"		output << \"Количество строк превышено\" << endl;",
				"		mayWork = false;",
				"	}",
				"",
				"	if (mayWork)",
				"	{",
				"		// Execution",
				"		int wrongStaples = findWrongStaples(code, positions);",
				"",
				"		// Output",
				"		if (!wrongStaples)",
				"		{",
				"			output << \"Проверка прошла успешно\" << endl;",
				"		}",
				"		else",
				"		{",
				"			output << \"Обнаружено \" << wrongStaples << \" ошиб\" << ((wrongStaples % 10 == 1 && wrongStaples % 100 / 10 != 1) ? \"ка\" : ((wrongStaples % 10 >= 2 && wrongStaples % 10 <= 4 && wrongStaples % 100 / 10 != 1) ? \"ки\" : \"ок\")) << endl;",
				"",
				"			output << positions[0][0] + 1 << \" строка:\" << endl;",
				"			int clearedBegin = deleteBeginSpaces(code[positions[0][0]]);",
				"			output << code[positions[0][0]] << endl;",
				"			for (int i = 0; i < positions[0][1] - clearedBegin; i++)",
				"				output << \" \";",
				"			output << \"^\";",
				"",
				"			for (int i = 1; i < wrongStaples; i++)",
				"			{",
				"				if (positions[i][0] == positions[i - 1][0])",
				"				{",
				"					for (int j = positions[i - 1][1] + 1; j < positions[i][1]; j++)",
				"						output << \" \";",
				"					output << \"^\";",
				"				}",
				"				else",
				"				{",
				"					output << endl << positions[i][0] + 1 << \" строка:\" << endl;",
				"					clearedBegin = deleteBeginSpaces(code[positions[i][0]]);",
				"					output << code[positions[i][0]] << endl;",
				"					for (int j = 0; j < positions[i][1] - clearedBegin; j++)",
				"						output << \" \";",
				"					output << \"^\";",
				"				}",
				"			}",
				"		}",
				"	}",
				"",
				"	// Close files",
				"	input.close();",
				"	output.close();",
				"",
				"	// Open output file in Notepad or other default programm",
				"	system(outputFile.c_str());",
				"",
				"	return 0;",
				"}",
				"",
				"",
				"int findWrongStaples(vector<string>& code, vector<vector<int>>& positions)",
				"{",
				"	positions.clear();",
				"	vector<vector<int>> staples;",
				"	bool inMultyLineComment = false,",
				"		inString = false;",
				"	",
				"	for (int line = 0; line < code.size(); line++)",
				"	{",
				"		inString = false;",
				"",
				"		for (int symbol = 0; symbol < code[line].size(); symbol++)",
				"		{",
				"			// Checking for unverified zone",
				"			if (symbol != code[line].size() - 1)",
				"			{",
				"				if (code[line][symbol] == \'/\')",
				"				{",
				"					if (code[line][symbol + 1] == \'/\')",
				"						break;",
				"					else if (code[line][symbol + 1] == \'*\')",
				"					{",
				"						inMultyLineComment = true;",
				"						symbol++;",
				"						continue;",
				"					}",
				"				}",
				"				else if (code[line][symbol] == \'\\\'\')",
				"				{",
				"					symbol += code[line][symbol + 1] == \'\\\'\' ? 1 : (code[line][symbol + 1] != \'\\\\\' ? 2 : 3);",
				"					continue;",
				"				}",
				"				else if (code[line][symbol] == \'\\\"\')",
				"				{",
				"					inString = !inString;",
				"					continue;",
				"				}",
				"				else if (code[line][symbol] == \'\\\\\' && code[line][symbol + 1] == \'\\\"\')",
				"				{",
				"					symbol++;",
				"					continue;",
				"				}",
				"				else if (code[line][symbol] == \'*\' && code[line][symbol + 1] == \'/\')",
				"				{",
				"					inMultyLineComment = false;",
				"					symbol++;",
				"					continue;",
				"				}",
				"			}",
				"",
				"			// Search staples",
				"			if (!inMultyLineComment && !inString)",
				"			{",
				"				if(isStaple(code[line][symbol]))",
				"				{",
				"					staples.push_back({ line, symbol });",
				"				}",
				"			}",
				"		}",
				"	}",
				"	  ",
				"	// Delete paired staples and add inner unpaired staples",
				"	int innerLength = 0;",
				"	while (innerLength < staples.size())",
				"	{",
				"		auto iter{ staples.begin() };",
				"",
				"		while (staples.size() != 0 && iter != staples.end() - 1 - innerLength)",
				"		{",
				"			char currentSymbol = code[(*iter)[0]][(*iter)[1]];",
				"			char nextSymbol = code[(*(iter + innerLength + 1))[0]][(*(iter + innerLength + 1))[1]];",
				"",
				"			if (isPairedStaples(currentSymbol, nextSymbol))",
				"			{",
				"				if (innerLength != 0)",
				"				{",
				"					for (auto innerIter = iter + 1; innerIter < iter + innerLength + 1; innerIter++)",
				"						positions.push_back(*innerIter);",
				"",
				"					staples.erase(iter, iter + 2 + innerLength);",
				"					innerLength = 0;",
				"					iter = staples.begin();",
				"				}",
				"				else",
				"				{",
				"					iter = staples.erase(iter, iter + 2);",
				"",
				"					if (staples.size() != 0 && iter != staples.begin())",
				"						iter--;",
				"				}",
				"			}",
				"			else",
				"			{",
				"				iter++;",
				"			}",
				"		}",
				"",
				"		innerLength++;",
				"	}",
				"",
				"	// Add remaining staples",
				"	for (auto iter{ staples.begin() }; iter < staples.end(); iter++)",
				"	{",
				"		positions.push_back(*iter);",
				"	}",
				"",
				"	// Sorting",
				"	for (int i = positions.size() - 1; i >= 2; i--)",
				"	{",
				"		for (int j = 0; j < i; j++)",
				"		{",
				"			if (positions[j][0] > positions[j + 1][0] || positions[j][0] == positions[j + 1][0] && positions[j][1] > positions[j + 1][1])",
				"			{",
				"				vector<int> pref = positions[j];",
				"				positions[j] = positions[j + 1];",
				"				positions[j + 1] = pref;",
				"			}",
				"		}",
				"	}",
				"",
				"	return positions.size();",
				"}",
				"",
				"bool isStaple(char symbol)",
				"{",
				"	return symbol == \'(\' || symbol == \'[\' || symbol == \'{\' || symbol == \')\' || symbol == \']\' || symbol == \'}\';",
				"}",
				"",
				"bool isPairedStaples(char first, char second)",
				"{",
				"	return first == \'(\' && second == \')\' || first == \'[\' && second == \']\' || first == \'{\' && second == \'}\';",
				"}",
				"",
				"int deleteBeginSpaces(string& str)",
				"{",
				"	int begin = 0;",
				"	while (str[begin] == \' \' || str[begin] == \'\\t\')",
				"		begin++;",
				"	str = str.substr(begin);",
				"",
				"	return begin;",
				"}"
			};

			vector<vector<int>> positions;
			int wrongStaples = findWrongStaples(code, positions);
			int exp_wrongStaples = 0;
			Assert::AreEqual(exp_wrongStaples, wrongStaples);
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
