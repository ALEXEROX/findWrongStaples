#include "Header.h"

int mai(int argc, char* argv[])
{
	// Russioan localization
	setlocale(LC_ALL, "rus");

	// File names
	/*string inputFile = argv[1];
	string outputFile = argv[2];*/
	string inputFile = "code.cpp";
	string outputFile = "output.txt";

	// File streams
	ifstream input;
	input.open(inputFile);
	ofstream output;
	output.open(outputFile;

	vector<string> code;
	vector<vector<int>> positions;

	// Input
	string line;
	while (getline(input, line))
		code.push_back(line);

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
		output << code[positions[0][0]] << endl;
		for (int i = 0; i < positions[0][1]; i++)
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
				output << positions[i][0] + 1 << " строка:" << endl;
				output << code[positions[i][0]] << endl;
				for (int i = 0; i < positions[i][1]; i++)
					output << " ";
				output << "^";
			}
		}
	}

	input.close();
	output.close();

	return 0;
}


int findWrongStaples(vector<string>& code, vector<vector<int>>& positions)
{
	positions.clear();
	vector<vector<int>> staples;
	bool inMultyLineComment = false,
		inString = false;
	
	for (int line = 0; line < code.size(); line++)
	{
		inString = false;

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
					symbol += code[line][symbol + 1] == '\'' ? 1 : 2;
					continue;
				}
				else if (code[line][symbol] == '\"')
				{
					inString = !inString;
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
				if(isStaple(code[line][symbol]))
				{
					staples.push_back({ line, symbol });
				}
			}
		}
	}
	  
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

bool isStaple(char symbol)
{
	return symbol == '(' || symbol == '[' || symbol == '{' || symbol == ')' || symbol == ']' || symbol == '}';
}

bool isPairedStaples(char first, char second)
{
	return first == '(' && second == ')' || first == '[' && second == ']' || first == '{' && second == '}';
}