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

/*! ����� ��� ��������� �������� � ���� c++
* \param[in] code - ����� ����
* \param[in] words - ������� ���������
* \param[out] positions - ������� (������ ������ � ������ �������) ��������� ���������
*/
int findWordsInCode(vector<string>& code, vector<string> words, vector<vector<int>>& positions);

/*! ����������, �������� �� ������� ����� ������
* \param[in] first - ������ ������
* \param[in] second - ������ ������
* \return �������� �� ������� ����� ������
*/
bool isPairedStaples(char first, char second);

/*! ������� ��������� ������� � ����� ���������
* param[in|out] str - �������������� ������
* return ���������� �������� ������
*/
int deleteBeginSpaces(string& str);