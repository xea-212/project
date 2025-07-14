#include "Bullet.h"
#include "Player.h"
#include "Enemy.h"
#include "Stage.h"

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
	

	if (isAlive_ == false)
	{
		life_--;
		Stage* st = FindGameObject<Stage>();
		if (st != nullptr)
		{
			VECTOR3 push = st->CollideSphere(transform.position + VECTOR3(0, 10, 0), 10.0f);
			//push.y = 0;
			
			if (VSize(push) > 0)
			{
				DestroyMe();
			}
			else
			{
				transform.position.x += speed_;
			}
		}
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

	/*Stage* s = FindGameObject<Stage>();
	Enemy* e = FindGameObject<Enemy>();
	if (s->CheckCircleCollisionXY(transform.position, 20, e->GetTransform().position, 40))
	{
		e->DestroyMe();
	}*/
	
}

void Bullet::Draw()
{
	Object3D::Draw();
	//DrawSphere3D(transform.position + VECTOR3(0,20,0), 20, 8, GetColor(255, 255, 255), GetColor(255, 255, 255), FALSE);
}

