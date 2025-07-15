#pragma once
#include "Object3D.h"

class Player : public Object3D
{
public:
	Player(VECTOR3(pos));
	~Player();
	void Update() override;
	void Draw() override;
	VECTOR3 GetPosition() const { return transform.position; }
	bool IsAlive() { return isAlive_; }
	void Damage() { life_ -= 1; }
	void ScoreUp() { score_ += 500; }
	void CoinScoreUP() { score_ += 100; }
	void ScoreDown() { score_ -= 100; }
	void PapperSride() { transform.position += VECTOR3(0,10.0f,0); }
	int GetScore() { return score_; }
private:
	bool isAlive_;
	int life_;
	int score_;
};