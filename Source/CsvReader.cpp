#include "CsvReader.h"
#include <fstream>
#include <Windows.h>
using namespace std;
#include <assert.h>

CsvReader::CsvReader(std::string filename)
{
	ifstream ifs(filename); // ファイルを開く
	string str; // 文字列を入れる場所
	record.clear();
	while (getline(ifs, str))
	{
		vector<string> line;
		while (true)
		{
			int idx = str.find(','); // ,の場所を探す(見つからなければnpos)
			if (idx == string::npos)
				break;
			//str.substr(2, 5); // 文字列を切り抜く(2文字目から5文字取り出す)
			//str.substr(2); // 2文字目から最後までを取り出す
			string s1 = str.substr(0, idx); // カンマの前
			line.push_back(s1);
			str = str.substr(idx + 1); // カンマの後
		}
		line.push_back(str);
		record.push_back(line);
	}
	ifs.close(); // 閉じる
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
