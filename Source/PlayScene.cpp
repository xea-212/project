#include "PlayScene.h"
#include "Axis.h"
#include "Stage.h"
#include "Player.h"
#include "Enemy.h"

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
	Stage* st = FindGameObject<Stage>();
	Player* p = FindGameObject<Player>();
	std::list<Enemy*> enemies = FindGameObjects<Enemy>();
	if (p->IsAlive() == false ) {
		SceneManager::ChangeScene("GAMEOVER");
	}
	for (Enemy* e : enemies) {
		if (e->IsBoss() && e->IsClearCheck()) {
			e->DestroyMe();
			st->ScoreUp();
			SceneManager::ChangeScene("CLEAR");
		}
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
