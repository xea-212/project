#pragma once
#include <string>
#include <vector>

class CsvReader
{
public:
	CsvReader(std::string filename);
	~CsvReader();
	int GetLines(); // �s��
	int GetColumns(int line); // ��̐�
	std::string GetString(int line, int col); // �f�[�^��Ԃ�
	int GetInt(int line, int col); // �f�[�^��int�ŕԂ�
	float GetFloat(float line, float col); // �f�[�^��float�ŕԂ�
private:
	std::vector<std::vector<std::string>> record;
};
