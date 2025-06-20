#pragma once
#include "Object3D.h"
#include "Animator.h"

class Coin : public Object3D
{
public:
	Coin(VECTOR3 pos);
	~Coin();
	void Update() override;
	void Draw() override;
private:
	bool gotten; // æ“¾Ï
	VECTOR3 velocity; // ˆÚ“®‘¬“x
	int time;
	float rotTime; // ’Êí‚Ì‰ñ“]ŠÔ
};