#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

/*! Поиск неправильно расположенных скобок в коде c++
* \param[in] code - текст кода
* \param[out] positions - позиции (индексы строк и символов текста) найденных скобок
* \return количество неправильно расположенных скобок
*/
int findWrongStaples(vector<wstring> &code, vector<vector<int>> &positions);

/*! Поиск подстрок в коде c++, игнорируя комментарии, символьные и строковые константы
* \param[in] code - текст кода
* \param[in] words - искомые слова
* \param[out] positions - позиции (индексы строк и символов теста) найденных слов
* \return количество найденных слов
*/
int findSubstringsInCode(vector<wstring>& code, vector<wstring> words, vector<vector<int>>& positions);

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
int deleteBeginSpaces(wstring& str);