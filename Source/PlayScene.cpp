#include "PlayScene.h"
#include "Axis.h"
#include "Stage.h"

PlayScene::PlayScene()
{
	SetCameraPositionAndTarget_UpVecY(VECTOR3(50, 100, -300), VECTOR3(0, 0, 0));
	new Axis();
	new Stage();
	//new ReadyGo();
	state = State::S_READY;
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	if (CheckHitKey(KEY_INPUT_T)) {
		SceneManager::ChangeScene("TITLE");
	}
}

void PlayScene::Draw()
{
}

void PlayScene::PlayStart()
{
	state = S_INPLAY;
}

bool PlayScene::CantMove()
{
	switch (state)
	{
	//case S_READY:
	//case S_TIMEUP:
		return true;
		
	}
	return false;
}
