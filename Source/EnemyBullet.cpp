#include "EnemyBullet.h"
#include "Player.h"
#include <cmath>

EnemyBullet::EnemyBullet(VECTOR3(pos))
{
	transform.position = pos;

	hModel = MV1LoadModel("data/models/Cookie.mv1");

	Player* e = FindGameObject<Player>();
	float tgX = e->GetPosition().x;
	float tgY = e->GetPosition().y;

	float dx = tgX - transform.position.x;
	float dy = tgY - transform.position.y;

	float length = std::sqrt(dx * dx + dy * dy);

	if (length > 0)
	{
		direction_.x = dx / length;
		direction_.y = dy / length;
	}
	else
	{
		direction_ = { 0.0f, 1.0f }; // Default to down if start and target are same
	}

	life_ = 600;

}

EnemyBullet::~EnemyBullet()
{
}

void EnemyBullet::Update()
{
	life_--;

	float dt = Time::DeltaTime();

	transform.position.x += direction_.x * 500.0f * dt;
	transform.position.y += direction_.y * 500.0f * dt;

	if (life_ < 0)
	{
		DestroyMe();
	}
}
