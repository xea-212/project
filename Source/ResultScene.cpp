#include "ResultScene.h"
#include "Player.h"

ResultScene::ResultScene()
{
	hImage_ = LoadGraph("data/images/background.jpg");
	goImage_ = LoadGraph("data/images/gameover.png");

	isDisplay_ = true;
	goTimer_ = 0.0f;
	timer_ = 10.0f;
}


ResultScene::~ResultScene()
{
}

void ResultScene::Update()
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

void ResultScene::Draw()
{
	Player* p = FindGameObject<Player>();
	
	DrawGraph(0, 0, hImage_, TRUE);
	DrawGraph(250, 250, goImage_, TRUE);
	

	if (p != nullptr)
	{
		int score = p->GetScore();
		DrawFormatString(400, 400, GetColor(255, 255, 255), "%d", score);
	}
	if (isDisplay_ == true)
	{
		DrawFormatString(450, 500, GetColor(255, 255, 255), "Push [T]Key To Play");
	}
}
