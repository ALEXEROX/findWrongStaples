#pragma once
#pragma warning(disable:4096)
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

/*! Найти неправильно расположенные скобки в коде c++
* \param[in] code - текст кода
* \param[out] positions - позиции (индекс строки и индекс символа) найденных скобок
* \return количество неправильно расположенных скобок
*/
int findWrongStaples(vector<string> &code, vector<vector<int>> &positions);