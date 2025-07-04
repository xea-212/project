#include "Enemy.h"
#include <assert.h>
#include "EnemyBullet.h"
#include "Player.h"

Enemy::Enemy(VECTOR3(pos), int enemyName)
{
	transform.position = pos;
	type = static_cast<ENEMY>(enemyName);

	switch (type)
	{
	case ENEMY::ZAKO0:
		hModel = MV1LoadModel("data/models/Yogurt.mv1");
		break;
	case ENEMY::ZAKO1:
		hModel = MV1LoadModel("data/models/Cookie.mv1");
		break;
	case ENEMY::ZAKO2:
		
		break;
	case ENEMY::ZAKO3:
		
		break;
	case ENEMY::BOSS:
		
		break;
	default:
		break;
	}
	
	assert(hModel > 0);

	bulletTimer = 0;
	
}

Enemy::~Enemy()
{
	if (hModel != -1)
	{
		MV1DeleteModel(hModel);
		hModel = -1;
	}
}

void Enemy::Update()
{
	switch (type)
	{
	case ENEMY::ZAKO0:
		UpdateZako0();
		break;
	case ENEMY::ZAKO1:
		UpdateZako1();
		break;
	case ENEMY::ZAKO2:
		UpdateZako2();
		break;
	case ENEMY::ZAKO3:
		UpdateZako3();
		break;
	case ENEMY::BOSS:
		UpdateBoss();
		break;
	default:
		break;
	}
}

void Enemy::UpdateZako0()
{
}

void Enemy::UpdateZako1()
{
	float dt = Time::DeltaTime();
	bulletTimer += dt;
	Player* p = FindGameObject<Player>();
	if (transform.position.Size() - p->GetTransform().position.Size() < 700)
	{
		if (bulletTimer > 5)
		{
			new EnemyBullet(transform.position);
			bulletTimer = 0;
		}
	}
}

void Enemy::UpdateZako2()
{
}

void Enemy::UpdateZako3()
{
}

void Enemy::UpdateBoss()
{
}
