#include "Player.h"
#include "Stage.h"

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
	if (anim != nullptr)
	{
		anim->Update();
	}

	if (CheckHitKey(KEY_INPUT_D))
	{
		transform.rotation.y += 3 * DegToRad;
	}
	if (CheckHitKey(KEY_INPUT_A))
	{
		transform.rotation.y -= 3 * DegToRad;
	}
	VECTOR3 velocity; // ˆÚ“®ƒxƒNƒgƒ‹
	if (CheckHitKey(KEY_INPUT_W))
	{
		velocity = VECTOR3(0, 0, 1) * 5.0f * MGetRotY(transform.rotation.y);
		anim->Play(ANIM_ID::aRUN);
	}
	else
	{
		anim->Play(ANIM_ID::aIDLE);
	}
	transform.position += velocity;
	Stage* st = FindGameObject<Stage>();
	if (st != nullptr)
	{
		VECTOR3 push = st->CollideSphere(transform.position + VECTOR3(0, 40, 0), 40.0f);
		transform.position += push;
	}

	VECTOR3 pos = VECTOR3(0, 1000, -300) * MGetRotY(transform.rotation.y) + transform.position;
	VECTOR3 look = transform.position + VECTOR3(0, 150, 0);
	SetCameraPositionAndTarget_UpVecY(pos, look);
}
