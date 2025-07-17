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
		life_ = 50;
		isBoss_ = false;
		break;
	case ENEMY::ZAKO1:
		hModel = MV1LoadModel("data/models/Cookie.mv1");
		life_ = 10;
		isBoss_ = false;
		break;
	case ENEMY::ZAKO2:
		hModel = MV1LoadModel("data/models/Eye.mv1");
		life_ = 10;
		isBoss_ = false;
		break;
	case ENEMY::ZAKO3:
		
		break;
	case ENEMY::BOSS:
		hModel = MV1LoadModel("data/models/Box.mv1");
		life_ = 100;
		isBoss_ = true;
		break;
	default:
		break;
	}
	
	assert(hModel > 0);

	bulletTimer = 0;
	basePosition_ = pos;
	isBack_ = false;
	isClear_ = false;
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

	Stage* st = FindGameObject<Stage>();
	if (isBoss_ && life_ <= 0)
	{
		isClear_ = true;
		life_ = -1;
	}
	else if(isBoss_ == false && life_ <= 0)
	{
		DestroyMe();
		st->ScoreUp();
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
	if (std::abs(transform.position.Size() - p->GetTransform().position.Size()) < 700)
	{
		if (bulletTimer > 5)
		{
			new EnemyBullet(transform.position, 1);
			bulletTimer = 0;
		}
	}
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
	Player* p = FindGameObject<Player>();
	Stage* st = FindGameObject<Stage>();

	if(life_ <= 0)
	{
		isClear_ = true;
	}

	if (st->IsInBossArea() == true)
	{
		float dt = Time::DeltaTime();
		bulletTimer += dt;

		if (bulletTimer > 2.5f)
		{
			new EnemyBullet(transform.position, 1);
			bulletTimer = 0;
		}

		if (std::abs(transform.position.Size() - p->GetTransform().position.Size()) < 1000)
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

			transform.position.x += direction_.x * 50.0f * dt;
			transform.position.y += direction_.y * 50.0f * dt;
		}
	}
}
