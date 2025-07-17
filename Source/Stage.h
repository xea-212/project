#pragma once
#include "Object3D.h"
#include <vector>

class Stage : public Object3D
{
public:
	Stage();
	~Stage();
	void Update() override;
	void Draw() override;
	VECTOR3 CollideSphere(VECTOR3 center, float radius);
	bool CheckCircleCollisionXY(const VECTOR3& pos1, float r1, const VECTOR3& pos2, float r2);
	bool CheckHitTile(VECTOR3 center);
	bool CheckHitItem(VECTOR3 center);
	void ScoreUp() { score_ += 500; }
	void CoinScoreUP() { score_ += 100; }
	void ScoreDown() { score_ -= 100; }
	
	int GetScore() { return score_; }
	bool IsInBossArea() { return isInBossArea_; }
private:
	std::vector<std::vector<int>> maps;
	int hImage_;
	bool isDraw;
	bool isInBossArea_;
	float timer_;
	int score_;
};


