#pragma once
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
int findWrongStaples(vector<string> code, vector<int[2]> positions);