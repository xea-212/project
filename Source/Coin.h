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
	bool gotten; // �擾��
	VECTOR3 velocity; // �ړ����x
	int time;
	float rotTime; // �ʏ�̉�]����
};