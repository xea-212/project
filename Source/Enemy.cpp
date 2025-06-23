#include "Enemy.h"
#include <assert.h>
#include "EnemyBullet.h"

Enemy::Enemy(VECTOR3(pos))
{
	transform.position = pos;

	hModel = MV1LoadModel("data/models/Cookie.mv1");
	assert(hModel > 0);

	bulletTimer = 0;
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	float dt = Time::DeltaTime();
	bulletTimer += dt;
	if (bulletTimer > 5)
	{
		new EnemyBullet(transform.position);
		bulletTimer = 0;
	}
}
