#include "Stage.h"
#include <vector>
#include "CsvReader.h"
#include "Player.h"
#include "Coin.h"
#include "Enemy.h"
#include "Bullet.h"
#include "EnemyBullet.h"
#include <cmath>
using namespace std;

Stage::Stage()
{
	hModel = MV1LoadModel("data/models/RedBrickBlock.mv1");
	MV1SetupCollInfo(hModel);

	hImage_ = LoadGraph("data/images/background.jpg");

	isDraw = false;

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
				new Coin(VECTOR3(100.0f * x, -100.0f * z + 50.0f, 0));
			}
			else if (p == 4)
			{
				new Enemy(VECTOR3(100.0f * x, -100.0f * z, 0), 0);
			}
			else if (p == 5)
			{
				new Enemy(VECTOR3(100.0f * x, -100.0f * z, 0), 1);
			}
			else if (p == 6)
			{
				new Enemy(VECTOR3(100.0f * x, -100.0f * z, 0), 2);
			}
		}
	}
}

Stage::~Stage()
{
}

void Stage::Update()
{
	std::list<Enemy*> e = FindGameObjects<Enemy>();
	EnemyBullet* eb = FindGameObject<EnemyBullet>();
	Player* p = FindGameObject<Player>();
	Bullet* b = FindGameObject<Bullet>();
	for (auto& enemy : e)
	{
		if (b != nullptr && enemy != nullptr)
		{
			if (CheckCircleCollisionXY(b->GetTransform().position, 20, enemy->GetTransform().position, 40))
			{
				enemy->DestroyMe();
			}
		}
	}
	
}

void Stage::Draw()
{
	DrawGraph(0, 0, hImage_, TRUE);
	for (int z = 0; z < maps.size(); z++)
	{
		for (int x = 0; x < maps[z].size(); x++)
		{
			if (maps[z][x] == 1)
			{
				MV1SetPosition(hModel, VECTOR3(100.0f * x, -100.0f * z, 0));
			}
			if (maps[z][x] == 7)
			{
				Player* p = FindGameObject<Player>();
				VECTOR3 pPos = p->GetPosition();
				if (pPos.x > x * 100.0f + 50.0f)
				{
					isDraw = true;
					MV1SetPosition(hModel, VECTOR3(100.0f * x, -100.0f * z, 0));
				}
			}
			MV1DrawModel(hModel);
		}
	}
	
	
}


VECTOR3 Stage::CollideSphere(VECTOR3 center, float radius)
{
	VECTOR3 ret = VGet(0.0f, 0.0f, 0.0f); // ret���[���x�N�g���ŏ�����
	for (int y = 0; y < maps.size(); y++) {
		for (int x = 0; x < maps[y].size(); x++) {
			// maps[z][x] == 1 ���Փ˔�����s��
			
			if (isDraw == true)
			{
				if (maps[y][x] != 1 && maps[y][x] != 7)
					continue;
			}
			else
			{
				if (maps[y][x] != 1)
					continue;
			}

			MV1SetPosition(hModel, VGet(x * 100.0f, y * -100.0f, 0)); // << �����𒲐�

			MV1RefreshCollInfo(hModel); // ���f���̈ʒu���ύX���ꂽ�̂ŏՓˏ����X�V

			MV1_COLL_RESULT_POLY_DIM result = MV1CollCheck_Sphere(hModel, -1, center, radius);

			for (int h = 0; h < result.HitNum; h++) {
				VECTOR3 hitPos = result.Dim[h].HitPosition; // �|���S���Ɠ��������ꏊ
				VECTOR3 hitNorm = result.Dim[h].Normal;     // ���������|���S���̖@��

				// ���������ꏊ���狅�̒��S�ւ̃x�N�g��
				VECTOR3 vecToCenter = VSub(center, hitPos);

				// �d�Ȃ��Ă���ʁi���a����x�N�g�����������������́j
				float overlap = radius - VSize(vecToCenter);

				// ���ۂɏd�Ȃ��Ă���ꍇ�̂݉����߂����v�Z
				if (overlap > 0) {
					// �����߂������́A���������|���S���̖@������
					VECTOR3 pushBackDir = VNorm(hitNorm); // �@���𐳋K��

					// �����߂��x�N�g����ret�ɉ��Z
					ret = VAdd(ret, VScale(pushBackDir, overlap));
				}
			}
			MV1CollResultPolyDimTerminate(result); // �Փˌ��ʂ����
		}
	}
	return ret;
}

bool Stage::HitTile(VECTOR3 center)
{
			int tileX = center.x / 100;
			int tileY = center.y / -100.0f;
			if (maps[tileY + 1][tileX] == 1)
			{
				VECTOR3 tileCenter = VECTOR3(tileX * 100.0f, tileY * -100.0f, 0);
				VECTOR3 distance = tileCenter - center;
				if(std::abs(distance.Size()) < 50.0f)
				return true;
			}
			else
			{
				return false;
			}
}

//bool Stage::HitTile(const VECTOR3& center)
//{
//	int tileX = center.x / 100.0f;
//	int tileY = center.y / -100.0f;
//	if (maps[tileY][tileX] == 1)
//	{
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}

bool Stage::CheckCircleCollisionXY(const VECTOR3& pos1, float r1, const VECTOR3& pos2, float r2)
{
	float dx = pos1.x - pos2.x;
	float dy = pos1.y - pos2.y;
	float distSq = std::sqrtf(dx * dx + dy * dy);
	float radiusSum = r1 + r2;

	return distSq <= radiusSum;
}

bool Stage::CheckHitTile(const VECTOR3& center, float radius)
{
	for (int y = 0; y < maps.size(); y++) {
		for (int x = 0; x < maps[y].size(); x++) {
			// maps[y][x] == 1 ���Փ˔�����s��
			if (maps[y][x] != 1)
				continue;
			VECTOR3 up = center + VECTOR3(0, radius, 0);
			int tilex = up.x / -100.0f;
			int tiley = up.y / -100.0f;
			if (maps[tiley][tilex] == 1)
			{
				return true;
			}
		}
	}

	return false;
}
