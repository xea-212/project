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
	DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));
	DrawString(100, 400, "Push [T]Key To Title", GetColor(255, 255, 255));
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
