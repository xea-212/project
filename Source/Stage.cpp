#include "Stage.h"
#include <vector>
#include "CsvReader.h"
#include "Player.h"
#include "Coin.h"
using namespace std;

Stage::Stage()
{
	hModel = MV1LoadModel("data/models/RedBrickBlock.mv1");
	MV1SetupCollInfo(hModel);

	int st = 0;
	char filename[64];
	sprintf_s<64>(filename, "data/stage%02d.csv", st);
	maps.clear();
	CsvReader* csv = new CsvReader(filename);
	for (int z = 0; z < csv->GetLines(); z++)
	{
		vector<int> mapsLine;
		for (int x = 0; x < csv->GetColumns(z); x++)
		{
			mapsLine.push_back(csv->GetInt(z, x));
		}
		maps.push_back(mapsLine);
	}
	delete csv;

	for (int z = 0; z < maps.size(); z++)
	{
		for (int x = 0; x < maps[z].size(); x++)
		{
			int p = maps[z][x];
			if (p == 2)
			{
				new Player(VECTOR3(100.0f * x, -100.0f * z, 0));
			}
			else if (p == 3)
			{
				new Coin(VECTOR3(100.0f * x, -100.0f * z, 0));
			}
		}
	}
}

Stage::~Stage()
{
}

void Stage::Draw()
{
	for (int z = 0; z < maps.size(); z++)
	{
		for (int x = 0; x < maps[z].size(); x++)
		{
			if(maps[z][x] == 1)
			MV1SetPosition(hModel, VECTOR3(100.0f * x, -100.0f * z, 0));
			MV1DrawModel(hModel);
		}
	}
}

VECTOR3 Stage::CollideSphere(VECTOR3 center, float radius)
{
	VECTOR3 ret;
	for (int z = 0; z < maps.size(); z++)
	{
		for (int x = 0; x < maps[z].size(); x++)
		{
			if (maps[z][x] != 1)
				continue;
			
			MV1SetPosition(hModel, VECTOR3(x * 100, 0, z * -100));
			MV1RefreshCollInfo(hModel);
			MV1_COLL_RESULT_POLY_DIM result = MV1CollCheck_Sphere(hModel, -1, center, radius);
			for (int h = 0; h < result.HitNum; h++)
			{
				VECTOR3 hitPos = result.Dim[h].HitPosition; // �|���S���Ɠ��������ꏊ
				VECTOR3 hitNorm = result.Dim[h].Normal; // ���������|���S���̖@��

				int nx = x + hitNorm.x;
				int nz = z - hitNorm.z;
				if (maps[nz][nx] == 1)
				{
					continue;
				}

				// �����Ԃ������̃x�N�g���iA)�����E�E�E�����������W����A���̒��S�ւ̃x�N�g��
				VECTOR3 a = center - hitPos;
				// ����̒������A���a��菬�����Ȃ�͂�
				// �����Ԃ��ʁi�傫���j�́A���a����AA�̒��������������
				float vol = radius - a.Size();
				// �����Ԃ������́AA�̒���1�ɂ������
				VECTOR3 dir = a.Normalize();
				// �����Ƒ傫���������������̂��A�����Ԃ��x�N�g���������return����
				ret += dir * vol;
			}
			// �����������Ƃ̌v�Z
			MV1CollResultPolyDimTerminate(result);
		}
	}
	return ret;
}

