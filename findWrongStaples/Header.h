#pragma once
#pragma warning(disable:4096)
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

/*! ����� ����������� ������������� ������ � ���� c++
* \param[in] code - ����� ����
* \param[out] positions - ������� (������ ������ � ������ �������) ��������� ������
* \return ���������� ����������� ������������� ������
*/
int findWrongStaples(vector<string> &code, vector<vector<int>> &positions);