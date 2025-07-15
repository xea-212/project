#include "TitleScene.h"
#include <fstream>
#include "../Source/Screen.h"
using namespace std;

TitleScene::TitleScene()
{

	hImage_ = LoadGraph("data/images/background.jpg");
	tImage_ = LoadGraph("data/images/sweetsavoid.png");
	isDisplay_ = true;
	titleTimer_ = 0.0f;
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{
	titleTimer_ += Time::DeltaTime();
	if (titleTimer_ > 1.0f) {
		isDisplay_ = false;
		if (titleTimer_ > 1.5f)
		{
			isDisplay_ = true;
			titleTimer_ = 0.0f;
		}
	}

	if (CheckHitKey(KEY_INPUT_P)) {
		SceneManager::ChangeScene("PLAY");
	}
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}
}


void TitleScene::Draw()
{
	
	DrawGraph(0, 0, hImage_, TRUE);
	DrawGraph(310, 250, tImage_, TRUE);
	extern const char* Version();
	SetFontSize(40);
	if(isDisplay_ == true)
	{
		DrawFormatString(450, 500, GetColor(255, 255, 255), "Push [P]Key To Play");
	}
	
}
