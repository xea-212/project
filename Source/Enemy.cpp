#include "Enemy.h"
#include <assert.h>
#include "EnemyBullet.h"
#include "Bullet.h"
#include "Player.h"
#include <cmath>
#include "Stage.h"

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
		hModel = MV1LoadModel("data/models/Eye.mv1");
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
	basePosition_ = pos;
	isBack_ = false;
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
	float dt = Time::DeltaTime();
	bulletTimer += dt;
	if (bulletTimer > 2.5f)
	{
		new EnemyBullet(transform.position, 0);
		bulletTimer = 0;
	}
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
			new EnemyBullet(transform.position, 1);
			bulletTimer = 0;
		}
	}
	Stage* st = FindGameObject<Stage>();
	Bullet* b = FindGameObject<Bullet>();
}

void Enemy::UpdateZako2()
{
	float dt = Time::DeltaTime();
	
	Player* p = FindGameObject<Player>();
	if (isBack_ == false)
	{
		float tgX = p->GetPosition().x;
		float tgY = p->GetPosition().y;

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
			direction_ = { 0.0f, 1.0f };
		}

		if (std::abs(transform.position.Size() - p->GetTransform().position.Size()) < 500)
		{
			transform.position.x += direction_.x * 300.0f * dt;
			transform.position.y += direction_.y * 300.0f * dt;
		}
		else
		{
			isBack_ = true;
		}
	}
	else
	{
		float tgX = basePosition_.x;
		float tgY = basePosition_.y;

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
			direction_ = { 0.0f, 1.0f };
		}

		if (std::abs(transform.position.Size() - basePosition_.Size()) > 10)
		{
			transform.position.x += direction_.x * 150.0f * dt;
			transform.position.y += direction_.y * 150.0f * dt;
			if (std::abs(transform.position.Size() - p->GetTransform().position.Size()) < 500)
			{
				isBack_ = false;
			}
		}
		else
		{
			isBack_ = false;
		}
	}
}

void Enemy::UpdateZako3()
{
}

void Enemy::UpdateBoss()
{
}
