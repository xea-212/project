#include "CsvReader.h"
#include <fstream>
#include <Windows.h>
using namespace std;
#include <assert.h>

CsvReader::CsvReader(std::string filename)
{
	ifstream ifs(filename); // �t�@�C�����J��
	string str; // �����������ꏊ
	record.clear();
	while (getline(ifs, str))
	{
		vector<string> line;
		while (true)
		{
			int idx = str.find(','); // ,�̏ꏊ��T��(������Ȃ����npos)
			if (idx == string::npos)
				break;
			//str.substr(2, 5); // �������؂蔲��(2�����ڂ���5�������o��)
			//str.substr(2); // 2�����ڂ���Ō�܂ł����o��
			string s1 = str.substr(0, idx); // �J���}�̑O
			line.push_back(s1);
			str = str.substr(idx + 1); // �J���}�̌�
		}
		line.push_back(str);
		record.push_back(line);
	}
	ifs.close(); // ����
}

CsvReader::~CsvReader()
{
	record.clear();
}

int CsvReader::GetLines()
{
	return record.size();
}

int CsvReader::GetColumns(int line)
{
	assert(line >= 0 && line < GetLines());
	return record[line].size();
}

std::string CsvReader::GetString(int line, int col)
{
	assert(line >= 0 && line < GetLines());
	assert(col >= 0 && col < GetColumns(line));
	return record[line][col];
}

int CsvReader::GetInt(int line, int col)
{
	return stoi(GetString(line,col));
}

float CsvReader::GetFloat(float line, float col)
{
	return stof(GetString(line, col));
}
