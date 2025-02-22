#include "Header.h"

int main(int argc, char* argv[])
{
	// Русская локазлизация
	setlocale(LC_ALL, "rus");

	// Пути файлов
	string inputFile = argv[1];
	string outputFile = argv[2];

	// Открытие файлов
	ifstream input;
	input.open(inputFile);
	ofstream output;
	output.open(outputFile);

	vector<string> code;
	vector<vector<int>> positions;
	bool mayWork = true;

	// Проверка входного файла
	if (inputFile.substr(inputFile.size() - 4, 4) != ".cpp")
	{
		output << "Входной файл имеет неподдерживаемый формат" << endl;
		mayWork = false;
	}

	// Проверка выходного файла
	if (mayWork && outputFile.substr(outputFile.size() - 4, 4) != ".txt")
	{
		output << "Выходной файл имеет неподдерживаемый формат" << endl;
		mayWork = false;
	}

	// Записываем код с файла
	int lines = 0;
	if (mayWork)
	{
		string line;
		while (getline(input, line) && lines++ <= 255)
		{
			code.push_back(line);

			// Проверка количества символов в строке
			if (line.size() > 1000)
			{
				output << "Количество символов в строке(-ах) превышено" << endl;
				mayWork = false;
				break;
			}
		}
	}

	// Проверка количества строк
	if (mayWork && lines > 255)
	{
		output << "Количество строк превышено" << endl;
		mayWork = false;
	}

	if (mayWork)
	{
		// Поиск неправильных скобок
		int wrongStaples = findWrongStaples(code, positions);

		// Вывод результат поиска в выходной файл
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

	// Закрытие файлов
	input.close();
	output.close();

	// Открытие выходного файла в блокноте или другой программе по умолчанию
	system(outputFile.c_str());

	return 0;
}


int findWrongStaples(vector<string>& code, vector<vector<int>>& positions)
{
	positions.clear();
	vector<vector<int>> staples;
	
	findWordsInCode(code, { "(", "{", "[", ")", "}", "]" }, staples); // Находим позиции скобок
	  
	
	int innerLength = 0; // Принимаем длину проверки за 0

	// Пока длина проверки меньше количества скобок
	while (innerLength < staples.size())
	{
		auto iter{ staples.begin() }; // Ставим итератор на первую позицию

		// Пока количество скобок не равно нулю и итератор не достиг позиции последней скобки с вычетом длины проверки
		while (staples.size() != 0 && iter != staples.end() - 1 - innerLength)
		{
			char currentSymbol = code[(*iter)[0]][(*iter)[1]]; // Позиция левой скобки равна позиции итератора
			char nextSymbol = code[(*(iter + innerLength + 1))[0]][(*(iter + innerLength + 1))[1]]; // Позиция правой скобки равна сумме позиции итератора и длины проверки

			// Если скобки являются парными
			if (isPairedStaples(currentSymbol, nextSymbol))
			{
				// Если длина проверки не равна нулю
				if (innerLength != 0)
				{
					for (auto innerIter = iter + 1; innerIter < iter + innerLength + 1; innerIter++) // Для каждой внутренней скобки
						positions.push_back(*innerIter); // Записываем позицию неправильно расположенной скобки

					staples.erase(iter, iter + 2 + innerLength); // Удаляем проверяемые скобки и их содержимое
					innerLength = 0; // Приравниваем длину проверки к нулю
					iter = staples.begin(); //3.2.3.1.4	Ставим итератор на позицию первой скобки
				}
				else // Иначе
				{
					iter = staples.erase(iter, iter + 2); // Удаляем две скобки и ставим итератор на следующую после второй скобки позицию

					if (staples.size() != 0 && iter != staples.begin())// Если количество скобок равно нулю и итератор не стоит на первой скобке
						iter--; // Ставим итератор на предыдущую позицию
				}
			}
			else // Иначе
			{
				iter++; // Ставим итератор на следующую позицию
			}
		}

		innerLength++; // Увеличиваем длину проверки на 1
	}

	// Записываем оставшиеся скобки в массив неправильно расположенных скобок
	for (auto iter{ staples.begin() }; iter < staples.end(); iter++)
	{
		positions.push_back(*iter);
	}

	// Сортируем массив неправильных скобок по возрастанию их положения
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

	return positions.size(); // Вернуть количество неправильно расположенных скобок
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