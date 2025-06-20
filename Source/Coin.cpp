#include "Coin.h"
#include "Player.h"

Coin::Coin(VECTOR3 pos)
{
	transform.position = pos;

	hModel = MV1LoadModel("data/models/Coin.mv1");
	gotten = false;
	velocity = VECTOR3(0, 0, 0);
	rotTime = 0;
}

Coin::~Coin()
{
}

void Coin::Update()
{
	static const float JumpHeight = 200.0f; // 1ブロックの高さが100
	static const int JumpTime = 60.0f;
	static const float Gravity = JumpHeight * 2.0f / (JumpTime / 2) / (JumpTime / 2);

	if (gotten) 
	{
		Player* p = FindGameObject<Player>();
		Transform pTr = p->GetTransform();
		VECTOR3 v = pTr.position - transform. position;
		v.y = 0;
		v /= time;
		time--;
		transform.scale = VECTOR3(1, 1, 1) * time / JumpTime;
		transform.rotation.y += 30.0f * DegToRad;
		velocity = VECTOR3(v.x, velocity.y, v.z);
		transform.position += velocity;
		velocity.y -= Gravity;
		if (time == 0)
		{
			DestroyMe();
		}
	}
	else {
		Player* p = FindGameObject<Player>();
		Transform pTr = p->GetTransform();
		VECTOR3 pCenter = pTr.position + VECTOR3(0, 50, 0);
		VECTOR3 v = pCenter - transform.position;
		if (v.Size() < 100)
		{
			gotten = true;
			velocity.y = Gravity * JumpTime / 2;
			time = JumpTime;
		}
		rotTime += Time::DeltaTime();
		if (rotTime >= 1.0f)
		{
			rotTime -= 1.0f;
		}
		if (rotTime >= 0.8f)
		{
			//transform.rotation.y  = fmodf(rotTime * 30.0f, 360.0f);
			//手抜きで書く方法
			//transform.rotation.y += 15.0f * DegToRad;

			transform.rotation.y = (rotTime - 0.8f) * 5.0f * DX_PI_F * 1.0f;
		}
		else
		{
			transform.rotation.y = 0.0f;
		}
		
	}
}

void Coin::Draw()
{
	Object3D::Draw();
	//DrawSphere3D(transform.position, 50, 20, GetColor(255, 0, 0), GetColor(255, 0, 0), FALSE);
}
