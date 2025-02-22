#include "Header.h"

int main(int argc, char* argv[])
{

	// Пути файлов
	string inputFile = "code.cpp";//argv[1];
	string outputFile = "output.txt";//argv[2];

	// Открытие файлов
	wifstream input(inputFile, ios::in);
	wofstream output(outputFile, ios::out);

	input.imbue(locale("en_US.UTF-8"));
	output.imbue(locale("en_US.UTF-8"));

	vector<wstring> code;
	vector<vector<int>> positions;
	bool mayWork = true;

	// Проверка входного файла
	if (inputFile.substr(inputFile.size() - 4, 4) != ".cpp")
	{
		output << L"Входной файл имеет неподдерживаемый формат" << endl;
		mayWork = false;
	}

	// Проверка выходного файла
	if (mayWork && outputFile.substr(outputFile.size() - 4, 4) != ".txt")
	{
		output << L"Выходной файл имеет неподдерживаемый формат" << endl;
		mayWork = false;
	}

	// Записываем код с файла
	int lines = 0;
	if (mayWork)
	{
		wstring line;
		while (getline(input, line) && lines++ <= 255)
		{
			code.push_back(line);

			// Проверка количества симво"ов в строке
 			if (line.size() > 1000)
			{
				output << L"Количество символов в строке(-ах) превышено" << endl;
				mayWork = false;
				break;
			}
		}
	}

	// Проверка количества строк
	if (mayWork && lines > 255)
	{
		output << L"Количество строк превышено" << endl;
		mayWork = false;
	}

	if (mayWork)
	{
		// Поиск неправильных скобок
		int wrongStaples = findWrongStaples(code, positions);

		// Вывод результат поиска в выходной файл
		if (!wrongStaples)
		{
			output << L"Проврка прошла успешно" << endl;
		}
		else
		{
			output << L"Обнаружено " << wrongStaples << L" ошиб" << ((wrongStaples % 10 == 1 && wrongStaples % 100 / 10 != 1) ? L"ка" : ((wrongStaples % 10 >= 2 && wrongStaples % 10 <= 4 && wrongStaples % 100 / 10 != 1) ? L"ки" : L"ок")) << endl;

			output << positions[0][0] + 1 << L" строка:" << endl;
			int clearedBegin = deleteBeginSpaces(code[positions[0][0]]);
			output << code[positions[0][0]] << endl;
			for (int i = 0; i < positions[0][1] - clearedBegin; i++)
				output << L" ";
			output << L"^";

			for (int i = 1; i < wrongStaples; i++)
			{
				if (positions[i][0] == positions[i - 1][0])
				{
					for (int j = positions[i - 1][1] + 1; j < positions[i][1]; j++)
						output << L" ";
					output << L"^";
				}
				else
				{
					output << endl << positions[i][0] + 1 << L" строка:" << endl;
					clearedBegin = deleteBeginSpaces(code[positions[i][0]]);
					output << code[positions[i][0]] << endl;
					for (int j = 0; j < positions[i][1] - clearedBegin; j++)
						output << L" ";
					output << L"^";
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


int findWrongStaples(vector<wstring>& code, vector<vector<int>>& positions)
{
	positions.clear();
	vector<vector<int>> staples;
	
	findWordsInCode(code, { L"(", L"{", L"[", L")", L"}", L"]" }, staples); // Находим позиции скобок
	  
	
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

int findWordsInCode(vector<wstring>& code, vector<wstring> words, vector<vector<int>>& positions)
{
	bool inMultyLineComment = false;

	// Для каждой строки
	for (int line = 0; line < code.size(); line++)
	{
		bool inString = false;
		// Для каждого символа, кроме последнего
		for (int symbol = 0; symbol < code[line].size(); symbol++)
		{
			// Если символ не последний в строке
			if (symbol != code[line].size() - 1)
			{
				// Если символ является косой чертой
				if (code[line][symbol] == '/')
				{
					if (code[line][symbol + 1] == '/') // Если следующий символ является косой чертой
						break; // Перейти на следующую строку
					else if (code[line][symbol + 1] == '*') // Иначе если следующий символ является звёздочкой
					{
						inMultyLineComment = true; // Мы в многострочном комментарии
						symbol++; // Переходим на два символа вперёд
						continue;
					}
				}
				else if (code[line][symbol] == '\'') // Иначе если символ является единичкой кавычкой
				{
					// Если символ является кавычкой, переходим на два символа вперёд, нначе если следующий символ является обратной косой чертой, переходим на три символа вперёд, переходим на четыре символа вперёд
					symbol += code[line][symbol + 1] == '\'' ? 1 : (code[line][symbol + 1] != '\\' ? 2 : 3);
					continue;
				}
				else if (code[line][symbol] == '\"') // Иначе если символ является двойной кавычкой
				{
					inString = !inString; // Статус нахождения в строке меняется на противоположный
					continue; // Переходим на следующий символ
				}
				else if (code[line][symbol] == '\\' && code[line][symbol + 1] == '\"') // Иначе если символ является обратной косой чертой и следующий символ является двойной кавычкой
				{
					symbol++; // Переходим на два символа вперёд
					continue;
				}
				else if (code[line][symbol] == '*' && code[line][symbol + 1] == '/') // Иначе если символ является звёздочкой и следующий символ является косой чертой
				{
					inMultyLineComment = false; // Мы не в многострочном комментарии
					symbol++; // Переходим на два символа вперёд
					continue;
				}
			}

			// Если мы не в многострочном комментарии и не в строке
			if (!inMultyLineComment && !inString)
			{
				// Для каждой искомой подстроки
				for (int i = 0; i < words.size(); i++)
				{
					// Если подстрока кода длиной искомой подстроки равна искомой подстроке
					if (code[line].substr(symbol, words[i].size()) == words[i])
					{
						positions.push_back({ line, symbol }); // Записываем позицию
						symbol += words[i].size() - 1; // Перескакиваем через слово
						break; // Прерываем процесс поиска подстроки
					}
				}
			}
		}
	}

	return positions.size(); // Возвращаем количество вхождений
}

bool isPairedStaples(char first, char second)
{
	return first == '(' && second == ')' || first == '[' && second == ']' || first == '{' && second == '}';
}

int deleteBeginSpaces(wstring& str)
{
	int begin = 0;
	while (str[begin] == ' ' || str[begin] == '\t')
		begin++;
	str = str.substr(begin);

	return begin;
}