#include "GameOverScene.h"
#include "Player.h"
#include "Stage.h"

GameOverScene::GameOverScene()
{
	hImage_ = LoadGraph("data/images/background.jpg");
	goImage_ = LoadGraph("data/images/gameover.png");

	isDisplay_ = true;
	goTimer_ = 0.0f;
	timer_ = 10.0f;
}


GameOverScene::~GameOverScene()
{
}

void GameOverScene::Update()
{
	goTimer_ += Time::DeltaTime();
	if (goTimer_ > 1.0f) {
		isDisplay_ = false;
		if (goTimer_ > 1.5f)
		{
			isDisplay_ = true;
			goTimer_ = 0.0f;
		}
	}

	timer_ -= Time::DeltaTime();
	if (CheckHitKey(KEY_INPUT_T) || timer_ < 0 ) {
		SceneManager::ChangeScene("TITLE");
	}
}

void GameOverScene::Draw()
{
	Stage* st = FindGameObject<Stage>();
	
	DrawGraph(0, 0, hImage_, TRUE);
	DrawGraph(250, 250, goImage_, TRUE);
	

	if (st != nullptr)
	{
		int score = st->GetScore();
		DrawFormatString(400, 400, GetColor(255, 255, 255), "%d", score);
	}
	if (isDisplay_ == true)
	{
		DrawFormatString(450, 500, GetColor(255, 255, 255), "Push [T]Key To Play");
	}
}
