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

	hModel = MV1LoadModel("data/models/WhiteChara.mv1");
	MV1SetFrameUserLocalMatrix(hModel, 6, MGetRotY(DX_PI_F));

	anim = new Animator(hModel);
	anim->AddFile(ANIM_ID::aIDLE, "data/models/Anim_Idle.mv1", true);
	anim->AddFile(ANIM_ID::aRUN, "data/models/Anim_Run.mv1", true);
	anim->Play(ANIM_ID::aIDLE);

	VECTOR3 campos = VECTOR3(0, 300, -300) + transform.position;
	VECTOR3 camlook = transform.position + VECTOR3(0, 150, 0);
	SetCameraPositionAndTarget_UpVecY(campos, camlook);

	transform.rotation.y = 90 * DegToRad;

	isPushKey = false;
}

Player::~Player()
{
	if (anim != nullptr)
	{
		delete anim;
		anim = nullptr;
	}
}

void Player::Update()
{
	int key = GetJoypadInputState(DX_INPUT_PAD1);

	if (anim != nullptr)
	{
		anim->Update();
	}

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
		velocity = VECTOR3(0, 0, 1) * 5.0f * MGetRotY(transform.rotation.y);
		anim->Play(ANIM_ID::aRUN);
		isPushKey = true;
	}
    if(CheckHitKey(KEY_INPUT_A) || key & PAD_INPUT_LEFT)
	{
		velocity = VECTOR3(0, 0, -1) * 5.0f * MGetRotY(transform.rotation.y);
		anim->Play(ANIM_ID::aRUN);
		isPushKey = true;
	}
	if (CheckHitKey(KEY_INPUT_W) || key & PAD_INPUT_UP)
	{
		velocity = VECTOR3(0, 1, 0) * 5.0f * MGetRotY(transform.rotation.y);
		isPushKey = true;
	}
	if (CheckHitKey(KEY_INPUT_S) || key & PAD_INPUT_DOWN)
	{
		velocity = VECTOR3(0, -1, 0) * 5.0f * MGetRotY(transform.rotation.y);
		isPushKey = true;
	}
	if(isPushKey == false)
	{
		anim->Play(ANIM_ID::aIDLE);
	}
	/*transform.position += velocity;*/
	isPushKey = false;

	if (CheckHitKey(KEY_INPUT_SPACE) || key & PAD_INPUT_B)
	{
		if (FindGameObject<Bullet>() == nullptr)
		new Bullet(transform.position + VECTOR3(0,40,0));
	}

	Stage* st = FindGameObject<Stage>();
	if (st != nullptr)
	{
		VECTOR3 push = st->CollideSphere(transform.position + VECTOR3(0, 40, 0), 40.0f);
		push.y = 0;
		if (VDot(velocity, push) < 0)
		{
			transform.position += push;
		}
		else
		{
			transform.position += velocity;
		}
	}

	VECTOR3 pos = VECTOR3( 0 + transform.position.x, -500, -900);
	VECTOR3 look = VECTOR3(transform.position.x, -500, transform.position.z);
	SetCameraPositionAndTarget_UpVecY(pos, look);


}
