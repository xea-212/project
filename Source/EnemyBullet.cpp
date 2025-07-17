#include "EnemyBullet.h"
#include "Player.h"
#include "Enemy.h"
#include <cmath>
#include "Stage.h"
#include <map>

std::map<int, int> BulletModel;

EnemyBullet::EnemyBullet(VECTOR3(pos), int bulletName)
{
	transform.position = pos;
	enemyId = bulletName;
	switch (enemyId)
	{
	case BULLET::YOGURT:
		hModel = MV1LoadModel("data/models/Ybullet.mv1");
		break;
	case BULLET::CHOKOCOOKIE:
		hModel = MV1LoadModel("data/models/chococookie.mv1");
		break;
	}
	
	//BulletModel[enemyID] = MV1LoadModel("data/models/Ybullet.mv1");
	//BulletModel[enemyID] = MV1LoadModel("data/models/chococookie.mv1");

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

	life_ = 300;
	
	//printfDx("%d\n", enemyId);
}

EnemyBullet::~EnemyBullet()
{
	if (hModel != -1)
	{
		MV1DeleteModel(hModel);
		hModel = -1;
	}
}

void EnemyBullet::Update()
{
	Stage* st = FindGameObject<Stage>();
	Player* p = FindGameObject<Player>();
	float dt = Time::DeltaTime();
	life_--;
	if (st != nullptr)
	{

		if (st->CheckHitTile(transform.position + VECTOR3( 0, 10, 0)))
		{
			DestroyMe();
		}
		else
		{
			switch (enemyId)
			{
			case 0:
				transform.position += VECTOR3(0, speed_, 0);
				break;
			case 1:
				transform.position.x += direction_.x * 500.0f * dt;
				transform.position.y += direction_.y * 500.0f * dt;
				break;
			}
		}
	}
	
	if (st->CheckCircleCollisionXY(transform.position, 10.0f, p->GetPosition(), 40.0f))
	{
		DestroyMe();
		p->Damage();
		st->ScoreDown();
	}

	if (life_ < 0)
	{
		DestroyMe();
	}
}

void EnemyBullet::Draw()
{
	Object3D::Draw();
	//DrawSphere3D(transform.position + VECTOR3(0, 20, 0), 20, 4, GetColor(255, 0, 0), GetColor(255, 0, 0), FALSE);
}
