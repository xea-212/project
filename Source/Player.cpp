#include "Player.h"
#include "Stage.h"
#include "PlayScene.h"
#include "Bullet.h"

enum ANIM_ID
{
	aIDLE = 0,
	aRUN,
};

Player::Player(VECTOR3(pos))
{
	transform.position = pos;

	hModel = MV1LoadModel("data/models/ashley.mv1");
	MV1SetFrameUserLocalMatrix(hModel, 6, MGetRotY(DX_PI_F));


	VECTOR3 campos = VECTOR3(0, 300, -300) + transform.position;
	VECTOR3 camlook = transform.position + VECTOR3(0, 150, 0);
	SetCameraPositionAndTarget_UpVecY(campos, camlook);

	isAlive_ = true;
	life_ = 3;
	score_ = 0;
}

Player::~Player()
{
	
}

void Player::Update()
{
	int key = GetJoypadInputState(DX_INPUT_PAD1);

	if (GetScene<PlayScene>()->CantMove())
		return;

	/*if (CheckHitKey(KEY_INPUT_D))
	{
		transform.rotation.y += 3 * DegToRad;
	}
	if (CheckHitKey(KEY_INPUT_A))
	{
		transform.rotation.y -= 3 * DegToRad;
	}*/
	VECTOR3 velocity; // ˆÚ“®ƒxƒNƒgƒ‹ 
	if (CheckHitKey(KEY_INPUT_D) || key & PAD_INPUT_RIGHT)
	{
		velocity = VECTOR3(1, 0, 0) * 5.0f;
		
	}
    if(CheckHitKey(KEY_INPUT_A) || key & PAD_INPUT_LEFT)
	{
		velocity = VECTOR3(-1, 0, 0) * 5.0f;
		
	}
	if (CheckHitKey(KEY_INPUT_W) || key & PAD_INPUT_UP)
	{
		velocity = VECTOR3(0, 1, 0) * 5.0f;
		
	}
	if (CheckHitKey(KEY_INPUT_S) || key & PAD_INPUT_DOWN)
	{
		velocity = VECTOR3(0, -1, 0) * 5.0f;
		
	}

	/*transform.position += velocity;*/
	
	if (CheckHitKey(KEY_INPUT_SPACE) || key & PAD_INPUT_B)
	{
		if (FindGameObject<Bullet>() == nullptr)
		new Bullet(transform.position + VECTOR3(0,40,0));
	}

#if true
	Stage* st = FindGameObject<Stage>();
	if (st != nullptr)
	{
		VECTOR3 push = st->CollideSphere(transform.position + VECTOR3(0, 40, 0), 40.0f);
		//push.y = 0;
		if (VDot(velocity, push) < 0)
		{
			transform.position += push;
		}
		else
		{
			transform.position += velocity;
		}
	}

	if (life_ <= 0)
	{
		isAlive_ = false;
	}

	if (score_ < 0)
	{
		score_ = 0;
	}


#else 
	Stage* st = FindGameObject<Stage>();
	if (st != nullptr) {
		VECTOR3 push = st->CollideSphere(transform.position + VECTOR3(0, 40, 0), 40.0f);
		transform.position += push;
	}
#endif
	VECTOR3 pos = VECTOR3( 0 + transform.position.x, -500, -900);
	VECTOR3 look = VECTOR3(transform.position.x, -500, transform.position.z);
	SetCameraPositionAndTarget_UpVecY(pos, look);


}

void Player::Draw()
{
	Object3D::Draw();
	//DrawSphere3D(transform.position + VECTOR3(0, 50, 0), 40, 4, GetColor(255, 0, 0), GetColor(255, 0, 0), FALSE);
	DrawFormatString(0,0,GetColor(255,255,255),"%d",life_);
	DrawFormatString(500, 0, GetColor(255, 255, 255), "%d", score_);
}