#include "PlayScene.h"
#include "Axis.h"
#include "Stage.h"
#include "PLayer.h"

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
	Player* p = FindGameObject<Player>();
	if (p->IsAlive() == false) {
		SceneManager::ChangeScene("RESULT");
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
		return true;
	}
	return false;
}
