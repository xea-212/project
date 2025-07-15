#include "Bullet.h"
#include "Player.h"
#include "Stage.h"
#include "Enemy.h"

Bullet::Bullet(VECTOR3 pos)
{
	transform.position = pos;

	hModel = MV1LoadModel("data/models/chococookie.mv1");

	isAlive_ = false;
	life_ = 120;
	speed_ = 10.0f;
}

Bullet::~Bullet()
{
	if (hModel != -1)
	{
		MV1DeleteModel(hModel);
		hModel = -1;
	}
}

void Bullet::Update()
{
	Stage* st = FindGameObject<Stage>();
	Enemy* e = FindGameObject<Enemy>();
	if (st->CheckCircleCollisionXY(transform.position, 20, e->GetTransform().position, 40))
	{
		e->DestroyMe();
		DestroyMe();
	}
	
	if (isAlive_ == false)
	{
		life_--;
		transform.position.x += speed_;
		if (life_ <= 0)
		{
			isAlive_ = true;
		}
	}
	else 
	{
		DestroyMe();
		isAlive_ = false;
	}
}

void Bullet::Draw()
{
	Object3D::Draw();
	DrawSphere3D(transform.position + VECTOR3(0,20,0), 20, 8, GetColor(255, 255, 255), GetColor(255, 255, 255), FALSE);
}

