#pragma once
#include "Object3D.h"

class EnemyBullet : public Object3D
{
public:
	EnemyBullet(VECTOR3(pos));
	~EnemyBullet();
	void Update() override;
private:
	VECTOR3 direction_;
	int life_;
};
