#include "Stage.h"
#include <vector>
#include "CsvReader.h"
#include "Player.h"
#include "Coin.h"
#include "Enemy.h"
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

//VECTOR3 Stage::CollideSphere(VECTOR3 center, float radius)
//{
//	VECTOR3 ret;
//	for (int z = 0; z < maps.size(); z++)
//	{
//		for (int x = 0; x < maps[z].size(); x++)
//		{
//			if (maps[z][x] != 1)
//				continue;
//			
//			MV1SetPosition(hModel, VECTOR3(x * 100.0f, z * -100.0f, 0));
//			MV1RefreshCollInfo(hModel);
//			MV1_COLL_RESULT_POLY_DIM result = MV1CollCheck_Sphere(hModel, -1, center, radius);
//			for (int h = 0; h < result.HitNum; h++)
//			{
//				VECTOR3 hitPos = result.Dim[h].HitPosition; // ポリゴンと当たった場所
//				VECTOR3 hitNorm = result.Dim[h].Normal; // 当たったポリゴンの法線
//
//				int nx = x + hitNorm.x;
//				int nz = z - hitNorm.z;
//				if (maps[nz][nx] == 1)
//				{
//					continue;
//				}
//
//				// 押し返す向きのベクトル（A)を作る・・・当たった座標から、球の中心へのベクトル
//				VECTOR3 a = center - hitPos;
//				// これの長さが、半径より小さくなるはず
//				// 押し返す量（大きさ）は、半径から、Aの長さを引いたやつ
//				float vol = radius - a.Size();
//				// 押し返す向きは、Aの長さ1にしたやつ
//				VECTOR3 dir = a.Normalize();
//				// 向きと大きさを合成したものが、押し返すベクトル→これをreturnする
//				ret += dir * vol;
//			}
//			// 当たったあとの計算
//			MV1CollResultPolyDimTerminate(result);
//		}
//	}
//	return ret;
//}
//

VECTOR3 Stage::CollideSphere(VECTOR3 center, float radius)
{
	VECTOR3 ret = VGet(0.0f, 0.0f, 0.0f); // retをゼロベクトルで初期化
	for (int y = 0; y < maps.size(); y++) {
		for (int x = 0; x < maps[y].size(); x++) {
			// maps[z][x] == 1 が衝突判定を行う
			
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

			MV1SetPosition(hModel, VGet(x * 100.0f, y * -100.0f, 0)); // << ここを調整

			MV1RefreshCollInfo(hModel); // モデルの位置が変更されたので衝突情報を更新

			MV1_COLL_RESULT_POLY_DIM result = MV1CollCheck_Sphere(hModel, -1, center, radius);

			for (int h = 0; h < result.HitNum; h++) {
				VECTOR3 hitPos = result.Dim[h].HitPosition; // ポリゴンと当たった場所
				VECTOR3 hitNorm = result.Dim[h].Normal;     // 当たったポリゴンの法線

				// 当たった場所から球の中心へのベクトル
				VECTOR3 vecToCenter = VSub(center, hitPos);

				// 重なっている量（半径からベクトル長さを引いたもの）
				float overlap = radius - VSize(vecToCenter);

				// 実際に重なっている場合のみ押し戻しを計算
				if (overlap > 0) {
					// 押し戻す方向は、当たったポリゴンの法線方向
					VECTOR3 pushBackDir = VNorm(hitNorm); // 法線を正規化

					// 押し戻すベクトルをretに加算
					ret = VAdd(ret, VScale(pushBackDir, overlap));
				}
			}
			MV1CollResultPolyDimTerminate(result); // 衝突結果を解放
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
	float distSq = dx * dx + dy * dy;
	float radiusSum = r1 + r2;

	return distSq <= radiusSum * radiusSum;
}