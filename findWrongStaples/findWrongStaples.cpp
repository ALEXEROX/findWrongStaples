#include "Header.h"

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "RU");

	// Пути файлов
	string inputFile = argv[1];
	string outputFile = argv[2];

	wifstream input;
	wofstream output;

	// Проверка входного файла
	if (inputFile.substr(inputFile.size() - 4, 4) != ".cpp")
	{
		cout << "Входной файл должен иметь расширение .cpp" << endl;
		return 0;
	}

	// Проверка выходного файла
	if (outputFile.substr(outputFile.size() - 4, 4) != ".txt")
	{
		cout << "Выходной файл должен иметь расширение .txt" << endl;
		return 0;
	}

	// Открытие файлов
	input.open(inputFile, ios::in);
	if(input.fail())
	{ 
		cout << "Неверно указан входной файл. Возможно файл не существует" << endl;
		return 0;
	}

	output.open(outputFile, ios::out);
	if (output.fail()) {
		cout << "Неверно указан выходной файл. Возможно, файл имеет ограниченые права доступа." << endl;
		return 0;
	}

	//Локалзация
	input.imbue(locale("en_US.UTF-8"));
	output.imbue(locale("en_US.UTF-8"));

	vector<wstring> code;
	vector<vector<int>> positions;

	// Записываем код с файла
	int lines = 0;
	wstring line;
	while (getline(input, line) && lines++ <= 1000)
	{
		// Проверка количества символов в строке
		if (line.size() > 255)
		{
			cout << "Количество символов в строке(-ах) превышает максимальное значение в 255" << endl;
			return 0;
		}

		code.push_back(line);
	}

	// Проверка количества строк
	if (lines > 1000)
	{
		cout << "Количество строк превышает максимальное количество в 1000" << endl;

		return 0;
	}

	// Поиск неправильных скобок
	int wrongStaples = findWrongStaples(code, positions);

	// Вывод результат поиска в выходной файл
	if (!wrongStaples)
	{
		output << L"Проверка прошла успешно" << endl;
	}
	else
	{
		vector<wstring> tempCode = code;
		output << L"Обнаружено " << wrongStaples << L" ошиб" << ((wrongStaples % 10 == 1 && wrongStaples % 100 / 10 != 1) ? L"ка" : ((wrongStaples % 10 >= 2 && wrongStaples % 10 <= 4 && wrongStaples % 100 / 10 != 1) ? L"ки" : L"ок")) << endl;

		output << positions[0][0] + 1 << L" строка:" << endl;
		int clearedBegin = deleteBeginSpaces(tempCode[positions[0][0]]);
		output << tempCode[positions[0][0]] << endl;
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
				clearedBegin = deleteBeginSpaces(tempCode[positions[i][0]]);
				output << tempCode[positions[i][0]] << endl;
				for (int j = 0; j < positions[i][1] - clearedBegin; j++)
					output << L" ";
				output << L"^";
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
	
	findSubstringsInCode(code, { L"(", L"{", L"[", L")", L"}", L"]" }, staples); // Находим позиции скобок
	  
	
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
			if (arePairedBrackets(currentSymbol, nextSymbol))
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

int findSubstringsInCode(vector<wstring>& code, vector<wstring> words, vector<vector<int>>& positions)
{
	bool inMultyLineComment = false;

	// Для каждой строки
	for (int line = 0; line < code.size(); line++)
	{
		bool inString = false;
		bool inOnelineComment = false;

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
					{
						inOnelineComment = true; // Мы находимся в однострочном комментарии
						symbol++; // Перейти на два символа вперед
						continue; 
					}
					else if (code[line][symbol + 1] == '*') // Иначе если следующий символ является звёздочкой
					{
						inMultyLineComment = true; // Мы в многострочном комментарии
						symbol++; // Переходим на два символа вперёд
						continue;
					}
				}
				if (code[line][symbol] == '\'') // Если символ является единичкой кавычкой
				{
					// Если символ является кавычкой, переходим на два символа вперёд, нначе если следующий символ является обратной косой чертой, переходим на три символа вперёд, переходим на четыре символа вперёд
					symbol += code[line][symbol + 1] == '\'' ? 1 : (code[line][symbol + 1] != '\\' ? 2 : 3);
					continue;
				}
				if (code[line][symbol] == '\"') // Если символ является двойной кавычкой
				{
					inString = !inString; // Статус нахождения в строке меняется на противоположный
					continue; // Переходим на следующий символ
				}
				if (code[line][symbol] == '\\' && code[line][symbol + 1] == '\"') // Если символ является обратной косой чертой и следующий символ является двойной кавычкой
				{
					symbol++; // Переходим на два символа вперёд
					continue;
				}
				if (code[line][symbol] == '*' && code[line][symbol + 1] == '/') // Если символ является звёздочкой и следующий символ является косой чертой
				{
					inMultyLineComment = false; // Мы не в многострочном комментарии
					symbol++; // Переходим на два символа вперёд
					continue;
				}
			}

			// Если мы не в комментарии и не в строке
			if (!inOnelineComment && !inMultyLineComment && !inString)
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

bool arePairedBrackets(char first, char second)
{
	return first == '(' && second == ')' || first == '[' && second == ']' || first == '{' && second == '}';
}

int deleteBeginSpaces(wstring& str)
{
	int begin = 0; // Считаем, что пробелв и знаков табуляции нет

	// Пока в начале есть проблы и знаки табуляции
	while (str[begin] == ' ' || str[begin] == '\t')
		begin++; // Считаем их количество

	str = str.substr(begin); // Удаляем пробела и знаки табуляции

	return begin; // Возвращаем количество удалённых пробелов и знаков табуляции
}