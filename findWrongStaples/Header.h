#pragma once
#pragma warning(disable:4096)
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

/*! Ќайти неправильно расположенные скобки в коде c++
* \param[in] code - текст кода
* \param[out] positions - позиции (индекс строки и индекс символа) найденных скобок
* \return количество неправильно расположенных скобок
*/
int findWrongStaples(vector<string> &code, vector<vector<int>> &positions);

/*! Ќайти все вхождени€ подстрок в коде c++
* \param[in] code - текст кода
* \param[in] words - искомые подстроки
* \param[out] positions - позиции (индекс строки и индекс символа) найденных вхождений
*/
int findWordsInCode(vector<string>& code, vector<string> words, vector<vector<int>>& positions);

/*! ќпределить, €вл€ютс€ ли символы парой скобок
* \param[in] first - первый символ
* \param[in] second - второй символ
* \return €вл€ютс€ ли символы парой скобок
*/
bool isPairedStaples(char first, char second);

/*! ”далить начальные пробелы и знаки табул€ции
* param[in|out] str - обрабатываема€ строка
* return количество удалЄнных знаков
*/
int deleteBeginSpaces(string& str);