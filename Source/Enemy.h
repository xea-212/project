#pragma once
#include "Object3D.h"
#include "Animator.h"

class Enemy : public Object3D
{
public:
	Enemy(VECTOR3(pos), int enemyName);
	~Enemy();
	void Update() override;
	
private:
	float bulletTimer;
	VECTOR3 direction_;

	enum ENEMY
	{
		ZAKO0,
		ZAKO1,
		ZAKO2,
		ZAKO3,
		BOSS,
		ENEMY_MAX
	};
	ENEMY type;
	void UpdateZako0();
	void UpdateZako1();
	void UpdateZako2();
	void UpdateZako3();
	void UpdateBoss();

	VECTOR3 basePosition_;
	bool isBack_;
};