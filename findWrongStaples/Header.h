#pragma once
#pragma warning(disable:4096)
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

/*! Поиск неправильно расположенных скобок в коде c++
* \param[in] code - текст кода
* \param[out] positions - позиции (индексы строк и символов текста) найденных скобок
* \return положение неправильно расположенных скобок
*/
int findWrongStaples(vector<string> &code, vector<vector<int>> &positions);

/*! Поиск слов в коде c++
* \param[in] code - текст кода
* \param[in] words - искомые слова
* \param[out] positions - позиции (индексы строк и символов теста) найденных слов
* \return количество найденных слов
*/
int findWordsInCode(vector<string>& code, vector<string> words, vector<vector<int>>& positions);

/*! Проверка, являются ли скобки парными
* \param[in] first - первая скобка
* \param[in] second - вторая скобка
* \return true - если скобки парные, false - если скобки непарные
*/
bool isPairedStaples(char first, char second);

/*! Удаление начальных пробелов и знаков табуляции из строки
* param[in|out] str - обрабатываемый текст
* return количество удалённых пробелов и знаков табуляции
*/
int deleteBeginSpaces(string& str);