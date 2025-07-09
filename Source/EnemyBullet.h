#pragma once
#include "Object3D.h"

class EnemyBullet : public Object3D
{
public:
	EnemyBullet(VECTOR3(pos), int bulletName);
	~EnemyBullet();
	void Update() override;
	void Draw() override;
private:
	VECTOR3 direction_;
	int life_;
	float speed_ = 5.0f;
	enum BULLET
	{
		YOGURT,
		CHOKOCOOKIE,
	};
	BULLET bullet;
};
