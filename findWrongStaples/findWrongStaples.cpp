#include "Header.h"

int main(int argc, char* argv[])
{
	// Russioan localization
	setlocale(LC_ALL, "rus");

	// File names
	string inputFile = argv[1];
	string outputFile = argv[2];

	// File streams
	ifstream input;
	input.open(inputFile);
	ofstream output;
	output.open(outputFile);

	vector<string> code;
	vector<vector<int>> positions;
	bool mayWork = true;

	// Check input file
	if (inputFile.substr(inputFile.size() - 4, 4) != ".cpp")
	{
		output << "Входной файл имеет неподдерживаемый формат" << endl;
		mayWork = false;
	}

	// Check output file
	if (mayWork && outputFile.substr(outputFile.size() - 4, 4) != ".txt")
	{
		output << "Выходной файл имеет неподдерживаемый формат" << endl;
		mayWork = false;
	}

	// Input
	int lines = 0;
	if (mayWork)
	{
		string line;
		while (getline(input, line) && lines++ <= 255)
		{
			code.push_back(line);
			if (line.size() > 1000)
			{
				output << "Количество символов в строке(-ах) превышено" << endl;
				mayWork = false;
				break;
			}
		}
	}

	// Check for strings count
	if (mayWork && lines > 255)
	{
		output << "Количество строк превышено" << endl;
		mayWork = false;
	}

	if (mayWork)
	{
		// Execution
		int wrongStaples = findWrongStaples(code, positions);

		// Output
		if (!wrongStaples)
		{
			output << "Проверка прошла успешно" << endl;
		}
		else
		{
			output << "Обнаружено " << wrongStaples << " ошиб" << ((wrongStaples % 10 == 1 && wrongStaples % 100 / 10 != 1) ? "ка" : ((wrongStaples % 10 >= 2 && wrongStaples % 10 <= 4 && wrongStaples % 100 / 10 != 1) ? "ки" : "ок")) << endl;

			output << positions[0][0] + 1 << " строка:" << endl;
			int clearedBegin = deleteBeginSpaces(code[positions[0][0]]);
			output << code[positions[0][0]] << endl;
			for (int i = 0; i < positions[0][1] - clearedBegin; i++)
				output << " ";
			output << "^";

			for (int i = 1; i < wrongStaples; i++)
			{
				if (positions[i][0] == positions[i - 1][0])
				{
					for (int j = positions[i - 1][1] + 1; j < positions[i][1]; j++)
						output << " ";
					output << "^";
				}
				else
				{
					output << endl << positions[i][0] + 1 << " строка:" << endl;
					clearedBegin = deleteBeginSpaces(code[positions[i][0]]);
					output << code[positions[i][0]] << endl;
					for (int j = 0; j < positions[i][1] - clearedBegin; j++)
						output << " ";
					output << "^";
				}
			}
		}
	}

	// Close files
	input.close();
	output.close();

	// Open output file in Notepad or other default programm
	system(outputFile.c_str());

	return 0;
}


int findWrongStaples(vector<string>& code, vector<vector<int>>& positions)
{
	// Now staples not found
	positions.clear();
	vector<vector<int>> staples;
	
	findWordsInCode(code, { "(", "{", "[", ")", "}", "]" }, staples);
	  
	// Delete paired staples and add inner unpaired staples
	int innerLength = 0;
	while (innerLength < staples.size())
	{
		auto iter{ staples.begin() };

		while (staples.size() != 0 && iter != staples.end() - 1 - innerLength)
		{
			char currentSymbol = code[(*iter)[0]][(*iter)[1]];
			char nextSymbol = code[(*(iter + innerLength + 1))[0]][(*(iter + innerLength + 1))[1]];

			if (isPairedStaples(currentSymbol, nextSymbol))
			{
				if (innerLength != 0)
				{
					for (auto innerIter = iter + 1; innerIter < iter + innerLength + 1; innerIter++)
						positions.push_back(*innerIter);

					staples.erase(iter, iter + 2 + innerLength);
					innerLength = 0;
					iter = staples.begin();
				}
				else
				{
					iter = staples.erase(iter, iter + 2);

					if (staples.size() != 0 && iter != staples.begin())
						iter--;
				}
			}
			else
			{
				iter++;
			}
		}

		innerLength++;
	}

	// Add remaining staples
	for (auto iter{ staples.begin() }; iter < staples.end(); iter++)
	{
		positions.push_back(*iter);
	}

	// Sorting
	for (int i = positions.size() - 1; i >= 2; i--)
	{
		for (int j = 0; j < i; j++)
		{
			if (positions[j][0] > positions[j + 1][0] || positions[j][0] == positions[j + 1][0] && positions[j][1] > positions[j + 1][1])
			{
				vector<int> pref = positions[j];
				positions[j] = positions[j + 1];
				positions[j + 1] = pref;
			}
		}
	}

	return positions.size();
}

int findWordsInCode(vector<string>& code, vector<string> words, vector<vector<int>>& positions)
{
	bool inMultyLineComment = false,
		inString = false;

	for (int line = 0; line < code.size(); line++)
	{
		for (int symbol = 0; symbol < code[line].size(); symbol++)
		{
			// Checking for unverified zone
			if (symbol != code[line].size() - 1)
			{
				if (code[line][symbol] == '/')
				{
					if (code[line][symbol + 1] == '/')
						break;
					else if (code[line][symbol + 1] == '*')
					{
						inMultyLineComment = true;
						symbol++;
						continue;
					}
				}
				else if (code[line][symbol] == '\'')
				{
					symbol += code[line][symbol + 1] == '\'' ? 1 : (code[line][symbol + 1] != '\\' ? 2 : 3);
					continue;
				}
				else if (code[line][symbol] == '\"')
				{
					inString = !inString;
					continue;
				}
				else if (code[line][symbol] == '\\' && code[line][symbol + 1] == '\"')
				{
					symbol++;
					continue;
				}
				else if (code[line][symbol] == '*' && code[line][symbol + 1] == '/')
				{
					inMultyLineComment = false;
					symbol++;
					continue;
				}
			}

			// Search staples
			if (!inMultyLineComment && !inString)
			{
				for (int i = 0; i < words.size(); i++)
				{
					if (code[line].substr(symbol, words[i].size()) == words[i])
					{
						positions.push_back({ line, symbol });
						break;
					}
				}
			}
		}
	}

	return positions.size();
}

bool isPairedStaples(char first, char second)
{
	return first == '(' && second == ')' || first == '[' && second == ']' || first == '{' && second == '}';
}

int deleteBeginSpaces(string& str)
{
	int begin = 0;
	while (str[begin] == ' ' || str[begin] == '\t')
		begin++;
	str = str.substr(begin);

	return begin;
}