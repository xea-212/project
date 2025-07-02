#include "Bullet.h"
#include "Player.h"

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

